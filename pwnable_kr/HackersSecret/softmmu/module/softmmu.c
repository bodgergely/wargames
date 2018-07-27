#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/syscalls.h>
#include <linux/proc_fs.h>

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
    printk("[softmmu] - pte callback for virt addr: %p: pte entry: %p, contains: %p, at virt addr: %p\n", addr, pte, *pte);
}

static int page_walk(u32 vaddr)
{
    struct mm_struct* mm = current->mm;
    struct mm_walk memwalk;
    memwalk.mm = mm;
    memwalk.pte_entry = &pte_callback;
    return walk_page_range(vaddr, vaddr+4096, &memwalk);
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
    if (pgd_none_or_clear_bad(pgd)) {
        printk("[softmmu] - PGD not present of addr: %p\n", vaddr);
        goto out;
    }
	pud = pud_offset(pgd, vaddr);
    if (pud_none_or_clear_bad(pud)) {
        printk("[softmmu] - PUD not present of addr: %p\n", vaddr);
        goto out;
    }
    pmd = pmd_offset(pud, vaddr);
    if (pmd_none(*pmd)) {
        printk("[softmmu] - PMD not present of addr: %p\n", vaddr);
        goto out;
    }
    ptep = pte_offset_map(pmd, vaddr);
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
   u32 phys_page = mmu_walk(virt_page);
   u32 offset = virt_addr & 0xfff;
   u32 phys_addr = phys_page + offset;
   printk("[softmmu] - Virt addr: (%p) ---> Phys address (%p)\n", virt_addr, phys_addr);
   if( (phys_addr & 0xfff) != offset) {
       printk("[softmmu] - Phys offset not equal to virt offset(%x) - BUG\n", offset);
   }
   page_walk(virt_page);
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

