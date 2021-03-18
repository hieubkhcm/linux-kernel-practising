#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "dummydevice"
#define DEVICE_CLASS "dm"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Henry Le");
MODULE_DESCRIPTION("A very simple LKM");
MODULE_VERSION("0.1");



static struct file_operations fops = {
	.open = dm_device_open,
	.release = dm_device_close,
	.read = dm_device_read,
	.write = dm_device_write,
};


struct int __init char_dev_init(void)
{

}


struct void __exit char_dev_exit(void)
{

}




module_init(char_dev_init);
module_exit(char_dev_exit);
