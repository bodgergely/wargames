#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
//#include <asm-generic/pgtable.h>
//#include <linux/slab.h>
//#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <linux/highmem.h>
//#include <asm-generic/unistd.h>
//#include <asm-generic/page.h>
#include <linux/syscalls.h>
#include <linux/proc_fs.h>

typedef unsigned long long u64;
typedef unsigned int u32;

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


static u64 mmu_walk(u32 vaddr)
{
    struct task_struct* proc = current;
    struct mm_struct* mm = proc->mm;
    pgd_t* pgd;
    pmd_t* pmd;
    pte_t* ptep;
    pte_t  pte;

    pgd = pgd_offset(mm, vaddr);
    if (pgd_none(*pgd) || pgd_bad(*pgd)) {
        printk("[softmmu] - PGD not present of addr: %p", vaddr);
        goto out;
    }
    pmd = pmd_offset(pgd, vaddr);
    if (pmd_none(*pmd) || pmd_bad(*pmd)) {
        printk("[softmmu] - PMD not present of addr: %p", vaddr);
        goto out;
    }
    ptep = pte_offset_map(pmd, vaddr);
    if(!ptep) {
        printk("[softmmu] - PTE not present of addr: %p", vaddr);
        goto out;
    }

    pte = *ptep;

    printk("Phys address of virt: %p is %llx", (void*)vaddr, pte.pte);
    return pte.pte;
out:
   return NULL; 

}


static ssize_t mmu_read(struct file *file, char __user *buf, size_t count, 
                        loff_t *ppos)
{
   mmu_walk(virt_addr);
   return count;
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
    
    printk("Loading x86 PAE MMU emulator");
    printk("Write the virtual address to /proc/softmmu");
    printk("You can obtain it',27h,'s physical address by reading /proc/%s", module_name);
    printk("[+] i.e. echo -ne \\x00\\x80\\x04\\x08' > /proc/softmmu;");
    printk("hexdump -C /proc/softmmu");
    printk("[+] Let the kernel exploit begin :)");

    proc_entry = create_proc_entry(module_name, 0x1b6, (struct proc_dir_entry*)NULL);
    if(!proc_entry) {
        printk("Failed to create_proc_entry for softmmu!");
        return -1;
    }
    proc_entry->proc_fops = &mmu_fops;

    printk("[softmmu] - mmu_read at: %p", mmu_read);
    printk("[softmmu] - mmu_write at: %p", mmu_write);

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

