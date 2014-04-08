#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/cdev.h>

 /* For now, we can just have this as a standalone variable */
 static struct cdev gamepad_cdev;

 static struct file_operations gamepad_fops =
 {
    .owner = THIS_MODULE,
    .open = gamepad_open,
    .read = gamepad_read,
    .write = gamepad_write,
    .release = gamepad_release,
 }
 
 /* The allocated device number, mayor and minor */
 dev_t dev_num;
 
static int __init gamepad_init(void)
{
   /* TODO magne err handling */

   /* Allocate device region w/number */
   alloc_chrdev_region(&dev_num, 0, 1, "gamepad");
    
   /* Register device in the system (NOTE: do last)*/
   cdev_init(&gamepad_cdev, &gamepad_fops);
   gamepad_cdev.owner = THIS_MODULE;
   gamepad_cdev.ops = &gamepad_fops;
   cdev_add(&gamepad_cdev, dev_num, 1);
    
   printk(KERN_INFO "Gamepad kernel module initialized\n");
   return 0;
}

static void __exit gamepad_cleanup(void)
{
    cdev_del(&gamepad_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk("Gamepad kernel module cleaned up\n");
}

/* FOPS */
static int gamepad_open(struct inode *inode, struct file *filp) {return 0;}
static int gamepad_release(struct inode *inode, struct file *filp) {return 0;}

static int gamepad_read(
    struct file *filp, char __user *buff, 
    size_t count, loff_t *offp
) {
    return 1;
}

static int gamepad_write(
    struct file *filp, char __user *buff, 
    size_t count, loff_t *offp
) {
    return 1;
}

module_init(gamepad_init);
module_exit(gamepad_cleanup);

MODULE_DESCRIPTION("Kernel module for the gamepad used in TDT4258 fall 2014.");
MODULE_LICENSE("GPL");

