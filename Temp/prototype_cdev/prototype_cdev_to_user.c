#include <linux/init.h>           // cần thiết cho hai hàm __init __exit <=> (insmod và rmmod)
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <linux/uaccess.h>          // user access <- cần cho mấy hàm copy to user (kernel space -> user space)
#include <linux/version.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");            ///< The license type -- 4 dòng này không có cũng dc 
MODULE_AUTHOR("Ghi gì cũng được");    ///< The author -- visible when you use modinfo dùng modinfo để coi
MODULE_DESCRIPTION("Ghi gì cũng được");  ///< The description  dùng modinfo để coi
MODULE_VERSION("Ghi gì cũng được");            ///< A version number to inform users

static dev_t first; // Global variable for the first device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class - phục vụ cho tạo class_create() với device_create()
//static int    ret; //để debug là chủ yếu - viết theo phong cách Amarisoft

static char c;

//khai báo hàm() và code hàm luôn
static int my_open(struct inode *i, struct file *f) // my_open -> Ghi gì cũng được -> match là được
{
    printk(KERN_INFO "Henry_Driver: open() logging to debug\n");
    return 0;
}
static int my_close(struct inode *i, struct file *f) // my_close -> Ghi gì cũng được -> match là được
{
    printk(KERN_INFO "Henry_Driver: close() logging to debug\n\n");
    return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Henry_Driver: read() logging to debug\n");
    if (*off == 0)
    {
        if (copy_to_user(buf, &c, 1) != 0)
            return -EFAULT;
        else
        {
            (*off)++;
            return 1;
        }
    }
    else
        return 0;
}
// my_write -> Ghi gì cũng được -> match là được
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Henry_Driver: write() logging to debug\n");
    if (copy_from_user(&c, buf + len - 1, 1) != 0)
        return -EFAULT;
    else
        return len;
}

static struct file_operations pugs_fops = //fops -> chỉ là tên - Ghi gì cũng được, match với lúc gán là được 
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write
};// file_operations liệt kê mấy cái chức năng là cái FILE đó có, file thì thường có 4 chức năng cơ bản như quyển sách vậy
// mở sách. đọc sách, viết vô sách, đọc xong đóng lại


static int __init ofcd_init(void) /* Constructor */ //__init là để gắn module .ko vào, phía dưới có 1 đống code là để tạo ra file trong /dev cho user thao tác
{
    int ret;
    struct device *dev_ret;

    printk(KERN_INFO "Henry_log: device registered\n");
    if ((ret = alloc_chrdev_region(&first, 0, 1, "henry_ko")) < 0)
    {
        return ret;
    }// xong bước này là lấy được cặp số major minor nằm trong dev_t first
    if (IS_ERR(cl = class_create(THIS_MODULE, "henry_class"))) // chardrv có thể đổi thoải mái, chạy thành công thì trong sys/class sẽ có file chardrv
    {
        unregister_chrdev_region(first, 1);
        return PTR_ERR(cl);
    }// xong bước này thì struct class mới gán trị xong để parse tiêp vào hàm dưới device_create
    if (IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "henry_dev")))
    {
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return PTR_ERR(dev_ret);
    }//thành công thì vào /dev thấy driver mynull nhé

    cdev_init(&c_dev, &pugs_fops); //cdev_init — initialize a cdev structure
	// void cdev_init (	struct cdev * cdev,	const struct file_operations * fops);//xong bước này cdev mới hoàn thiện 
	// để gán trong hàm dưới

    if ((ret = cdev_add(&c_dev, first, 1)) < 0)//cdev_add — add a char device to the system
//int cdev_add (struct cdev * p, dev_t dev, unsigned count); //count the number of consecutive minor numbers corresponding to this device
    {
        device_destroy(cl, first);
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return ret;
    }
    return 0;
}

static void __exit ofcd_exit(void) /* Destructor */
{
    cdev_del(&c_dev);
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    printk(KERN_INFO "Henry_log: device unregistered\n");
}

module_init(ofcd_init);//api to attach the .ko to kernel - henry's commnent
module_exit(ofcd_exit);//api to detach the .ko from kernel - henry's comment


