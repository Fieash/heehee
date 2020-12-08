/*
 * test3.c replaces the vfs_read file with the heehee.jpg file
 */


#include "khook/engine.c"

#include <linux/fs.h>
#include <linux/unistd.h>
#include <linux/module.h>
#include <linux/version.h>

#include <stdio.h>
#include <stdlib.h>

atomic_t read_on;

KHOOK_EXT(ssize_t, vfs_read, struct file *, char __user *, size_t, loff_t *);
static ssize_t khook_vfs_read(struct file *file, char __user *buf,
			      size_t count, loff_t *pos){
    ssize_t ret;

    atomic_set(&read_on, 1);
    printk(KERN_INFO "i am hooking you \n");
    FILE * fptr;


    ret = KHOOK_ORIGIN(vfs_read, file1, buf, count, pos);

    atomic_set(&read_on, 0);
    return ret;
}

static int __init test2_init(void){
    
    int ret;
    ret = khook_init();
    if (ret < 0)
        return ret;
    
    printk(KERN_INFO "init test2\n");

    return ret;
}

static void __exit test2_exit(void){
    printk(KERN_INFO "exiting test2\n");
    khook_cleanup();
}


MODULE_LICENSE("GPL");
module_init(test2_init);
module_exit(test2_exit);