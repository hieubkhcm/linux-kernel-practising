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

MODULE_LICENSE("GPL");            ///< The license type -- 4 dòng này không có cũng dc
MODULE_AUTHOR("Ghi gì cũng được");    ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("Ghi gì cũng được");  ///< The description -- see modinfo
MODULE_VERSION("Ghi gì cũng được");            ///< A version number to inform users

static dev_t first; // Global variable for the first device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class
static int    ret; //để debug là chủ yếu - viết theo phong cách Amarisoft

//khai báo hàm() và code hàm luôn
static int my_open(struct inode *i, struct file *f) // my_open -> Ghi gì cũng được -> match là được
{
    printk(KERN_INFO "Driver: open() logging ra để debug\n\n");
    return 0;
}
static int my_close(struct inode *i, struct file *f) // my_close -> Ghi gì cũng được -> match là được
{
    printk(KERN_INFO "Driver: close() logging ra để debug\n\n");
    return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off) // my_read -> Ghi gì cũng được -> match là được
{
    printk(KERN_INFO "Driver: read()logging ra để debug\n\n");
    return 0;
}
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, // my_write -> Ghi gì cũng được -> match là được
    loff_t *off)
{
    printk(KERN_INFO "Driver: write()logging ra để debug\n\n");
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
// mở sách. đọc sách, viết vô sách, đọc xong đóng lại, không lẽ để mở chình ình ra đó.


static int __init ofcd_init(void) /* Constructor */
{
    int ret;
    struct device *dev_ret;

    printk(KERN_INFO "Namaskar: ofcd registered");
    if ((ret = alloc_chrdev_region(&first, 0, 1, "Shweta")) < 0)
    {
        return ret;
    }
    if (IS_ERR(cl = class_create(THIS_MODULE, "chardrv")))
    {
        unregister_chrdev_region(first, 1);
        return PTR_ERR(cl);
    }
    if (IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "mynull")))
    {
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return PTR_ERR(dev_ret);
    }

    cdev_init(&c_dev, &pugs_fops);
    if ((ret = cdev_add(&c_dev, first, 1)) < 0)
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
    printk(KERN_INFO "Alvida: ofcd unregistered");
}

module_init(ofcd_init);
module_exit(ofcd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anil Kumar Pugalia <email@sarika-pugs.com>");
MODULE_DESCRIPTION("Our First Character Driver");

