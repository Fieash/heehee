/*
 * test4.c hooking on load elf bin
 */


#include "khook/engine.c"

#include <linux/fs.h>
#include <linux/unistd.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/kmod.h>

#include <linux/binfmts.h>
static int umh_test(void);
KHOOK_EXT(int, load_elf_binary, struct linux_binprm *);
static int khook_load_elf_binary(struct linux_binprm *bprm)
{
    int ret;
    printk(KERN_INFO "hooked load_elf_binary (test4.c)\n");
	ret = KHOOK_ORIGIN(load_elf_binary, bprm);
    umh_test();
    
	return ret;
}

static int umh_test(void){
    char *argv[] = {"/bin/echo heehee > /tmp/heehee", NULL};
    static char *envp[] = {"HOME=/", "TERM=linux", "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL};
    
    printk(KERN_INFO "executing umh_test\n");

    return call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC); 
}

static int __init test2_init(void){
    
    int ret;
    ret = khook_init();
    if (ret < 0)
        return ret;
    
    printk(KERN_INFO "init test4\n");

    return ret;
}

static void __exit test2_exit(void){
    printk(KERN_INFO "exiting test4\n");
    khook_cleanup();
}


MODULE_LICENSE("GPL");
module_init(test2_init);
module_exit(test2_exit);