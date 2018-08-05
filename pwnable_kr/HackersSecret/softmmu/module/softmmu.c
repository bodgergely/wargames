#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/syscalls.h>
#include <linux/proc_fs.h>


/*

   CONFIG_HIGHMEM64G should be enabled in kernel config!
   That will enable PAE.

   */


typedef unsigned long long u64;
//typedef unsigned int u32;

const char* module_name = "softmmu";

u32 virt_addr = 0x08048000;

static ssize_t mmu_read(struct file *file, char __user *buf, size_t count, 
                        loff_t *ppos);

static ssize_t mmu_write(struct file *file, const char __user *buf,
						size_t count, loff_t *ppos);


struct proc_dir_entry* proc_entry = NULL;

static const struct file_operations mmu_fops = {
	.read		= mmu_read,
	.write		= mmu_write,
};

static int pte_callback(pte_t* pte, u32 addr, u32 end, struct mmu_walk* walk)
{
    printk("[softmmu] - pte callback for virt addr: %p: pte entry: %p, contains: %p\n", addr, pte, *pte);
}

static int page_walk(u32 vaddr)
{
    struct mm_struct* mm = current->mm;
    struct mm_walk memwalk;  // mm_walk in include/linux/mm.h
    memset(&memwalk, 0, sizeof(memwalk));
    memwalk.mm = mm;
    memwalk.pte_entry = &pte_callback;
    return walk_page_range(vaddr, vaddr+4096, &memwalk);
} 

/*
static u32 mmu_walk_ass(u32 vaddr)
{
    char* pgdp = (char*)(current->mm->pgd);
    
    u32 pgd = *(u32*)(pgdp + ((vaddr >> 0x1e)*8));
    if(!((*(char*)&pgd) & 0x1)) {
        printk("PAE entry not present.\n");
        return NULL;
    }

    u32 idx = (vaddr & 0x3fe00000) >> 0x12;
    u32 pmd = *((u32*)(idx + (pgd & 0xfffff000) - 0x40000000));
    if(!((*(char*)&pmd) & 0x1)) {
        printk("PD64 entry not present.\n");
        return NULL;
    }
    if(*(char*)&pmd == 0x80) {
        printk("2MB page.\n");
        return NULL;
    }

    u32 pve = (pmd & 0xfffff000);
    pve = pve + 0xc0000000;
    
    // get_pte_entry
    u32 bla = vaddr & 0x1ff0000;
    bla = bla >> 0xc;
    u32 pte = *(u32*)(pve + bla*8);
    if(!((*(char*)&pte) & 0x1)) {
        printk("PTE entry not present.\n");
    }
    printk("Virt: %p is phys: %p\n", vaddr, pte);
    return pte;

}
*/

/**
  Based on the Intel Software Developer Manual, 
  Volume 3: Systems Programming,
  Chapter 4 Paging - 4.4 PAE Paging
  Section 4.4.2
  */

static u32* get_pde_addr(u32 pdpte, u32 vaddr)
{
    // PDE location = bits 51:12 are from PDPTEi, bits 11:3 are bits 29:21 of the linear address
    u32 virt_part = ((vaddr & 0x3fe00000) >> 21) << 3;
    u32 entry_part = pdpte & 0xfffff000; 
    return entry_part + virt_part - 0x40000000;
}


static u64 mmu_walk_pae(u32 vaddr)
{
    struct task_struct* proc = current;
    struct mm_struct* mm = proc->mm;
    pgd_t* pdpte_table = mm->pgd;
    
    // PDPTE selection
    // virt addr bits 31:30 select the PDPTEi
    u32 pdpte_index = (vaddr & 0xC0000000) >> 30;
    u32 pdpte = *(u32*)(pdpte_table + pdpte_index*8);
    // inspect the P flag (bit 0)
    if(!(pdpte & 0x1)) {
        printk("PDPTE%u not a mapping\n", pdpte_index);
        return NULL;
    }
    u32* pde_addr = get_pde_addr(pdpte, vaddr);
    u32  pde = *pde_addr;
    if(!(pde & 0x1)) {
        printk("PDE: %p contains: %x is not a mapping.\n", pde_addr, pde);
    }
    if(pde & 0x80) {
        printk("PDE: %p contain : %x is mapping a 2MB page.\n", pde_addr, pde);
        return (pde & 0x000fffffffe00000) | (vaddr & 0x001fffff);
    }

    u32 pte_table_addr = (pde & 0xfffff000) + 0xc0000000;
    u32 pte_index = ((vaddr & 0x1ff000) >> 12);
    u64* pte_addr = (u64*)(pte_table_addr + (pte_index * 8));
    u64  pte = *pte_addr;
    if(!(pte & 0x1)) {
        printk("PTE not a mapping, PTE table start: %x, index: %x, pte_addr: %p, pte: %llx", 
                                    pte_table_addr, pte_index, pte_addr, pte);
        return NULL;
    }

    char* ptable = (char*)pte_table_addr;
    printk("[Debug] PTE(%p) Dump\n", ptable);
    printk("[task:%s] %p:%02x %p:%02x %p:%02x %p:%02x\n", proc->comm, ptable,
                *(ptable + 0), ptable+1, *(ptable+1), ptable+2, *(ptable+2),
                ptable+3, *(ptable+3));
    printk("[Debug] Dump Virtual Address\n");
    printk("===============================");
    printk((char*)vaddr);
    printk("===============================");

    // final physical
    return (pte & 0x000ffffffffff000) | (vaddr & 0xfff);

}



static u32 mmu_walk(u32 vaddr)
{
    struct task_struct* proc = current;
    struct mm_struct* mm = proc->mm;
    pgd_t* pgd;
    pud_t* pud;
    pmd_t* pmd;
    pte_t* ptep;
    pte_t  pte;

    pgd = pgd_offset(mm, vaddr);
    printk("pgd: %llx\n", pgd);
    if (pgd_none_or_clear_bad(pgd)) {
        printk("[softmmu] - PGD not present of addr: %p\n", vaddr);
        goto out;
    }
    pud = pud_offset(pgd, vaddr);
    printk("pud: %llx\n", pud);
    if (pud_none(*pud)) {
        printk("[softmmu] - PUD not present of addr: %p\n", vaddr);
        goto out;
    }
    pmd = pmd_offset(pud, vaddr);
    printk("pmd: %llx\n", pmd);
    if (pmd_none(*pmd)) {
        printk("[softmmu] - PMD not present of addr: %p\n", vaddr);
        goto out;
    }
    ptep = pte_offset_map(pmd, vaddr);
    printk("ptep: %llx\n", ptep);
    if(pte_none(*ptep)) {
        printk("[softmmu] - PTE not present of addr: %p\n", vaddr);
        goto out;
    }

    pte = *ptep;

    printk("Phys page of virt: %p is  at %p\n", (void*)vaddr, pte.pte);

    return pte.pte;
out:
   return NULL; 

}


static ssize_t mmu_read(struct file *file, char __user *buf, size_t count, 
                        loff_t *ppos)
{
   u32 virt_page = virt_addr & 0xfffff000;
   //u64 phys_page = mmu_walk(virt_page);
   //u32 offset = virt_addr & 0xfff;
   //u64 phys_addr = phys_page + offset;
   //printk("[softmmu] - Virt addr: (%p) ---> Phys address (%p)\n", virt_addr, phys_addr);
   //if( (phys_addr & 0xfff) != offset) {
   //    printk("[softmmu] - Phys offset not equal to virt offset(%x) - BUG\n", offset);
//   }
// mmu_walk_ass(virt_page);
   u64 phys_addr = mmu_walk_pae(virt_addr);
   phys_addr = page_walk(virt_page);
   return 4;
}

static ssize_t mmu_write(struct file *file, const char __user *buf,
						size_t count, loff_t *ppos)
{
    virt_addr = *(u32*)buf;
    printk("[softmmu] - Virtual address has been set to: %p\n", virt_addr);
    return count;
}


static int mmuinit(void)
{
    
    printk("Loading x86 PAE MMU emulator\n");
    printk("Write the virtual address to /proc/softmmu\n");
    printk("You can obtain it's physical address by reading /proc/%s\n", module_name);
    printk("[+] i.e. echo -ne \\x00\\x80\\x04\\x08' > /proc/softmmu;\n");
    printk("hexdump -C /proc/softmmu\n");
    printk("[+] Let the kernel exploit begin :)\n");

    proc_entry = create_proc_entry(module_name, 0x1b6, (struct proc_dir_entry*)NULL);
    if(!proc_entry) {
        printk("Failed to create_proc_entry for softmmu!\n");
        return -1;
    }
    proc_entry->proc_fops = &mmu_fops;

    printk("[softmmu] - mmu_read at: %p\n", mmu_read);
    printk("[softmmu] - mmu_write at: %p\n", mmu_write);

    return 0;
}



static int __init initmodule(void ){
    return mmuinit();
}

static void __exit exitmodule(void ){
	return;
}

module_init( initmodule );
module_exit( exitmodule );

