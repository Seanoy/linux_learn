#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENCE();
MODULE_AUTHOR("SEANOY");

static init hello_init(void)
{
	printk(KERN_EMERG "HELLO WORLD enter!\n");
	return 0;	
}

static void hello_exit(void)
{
	printk(KERN_EMERG "HELLO WORLD exit!\n");
}

module_init(hello_init);
module_exit(hello_exit); 