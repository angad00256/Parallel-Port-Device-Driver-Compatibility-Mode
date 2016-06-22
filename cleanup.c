#include"headers.h"
#include"declarations.h"

static void __exit cleanup(void)
{
	#ifdef DEBUG
		printk(KERN_ALERT"Bye Kernel \n");
	#endif

	release_region(BASE,3);

	cdev_del(&dev->c_dev);

	kfree(dev);

	unregister_chrdev_region(devid,1);

	#ifdef DEBUG
		printk(KERN_ALERT"Unregisteration Successful!! \n");
	#endif
}

module_exit(cleanup);
