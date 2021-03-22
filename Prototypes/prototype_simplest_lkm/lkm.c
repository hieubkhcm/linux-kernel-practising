#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A practise module");
MODULE_AUTHOR("Me - Henry");
MODULE_VERSION("0.1");

static char *name = "Henry";
module_param(name, charp, S_IRUGO); 

static int __init attach_the_module(void)
{
	printk(KERN_INFO "Hello %s from the Kernel \n", name);
	return 0;
}

static void __exit detach_the_module(void)
{
	printk(KERN_INFO "Goodbye %s from the Kernel \n", name);
}

module_init(attach_the_module);
module_exit(detach_the_module);
