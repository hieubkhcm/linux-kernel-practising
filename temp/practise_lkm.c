#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/device>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Henry Le");
MODULE_DESCRIPTION("A very simple LKM");
MODULE_VERSION("0.1");




struct int __init char_dev_init(   ) 
{
	





}


struct void __exit char_dev_exit(  )
{




}


static struct file_operations fops = {
	.open = ;
	.release = ;
	.read = ;
	.write = ;


	return ;
}


module_init();
module_exit();
