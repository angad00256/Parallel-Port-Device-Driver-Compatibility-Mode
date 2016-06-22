#include"headers.h"
#include"declarations.h"
#include"operations.h"

dev_t devid;
struct Dev *dev;

static int __init initfunc(void)
{
	int ret1;
	int minorno;	
	dev_t devno;
	int ret2;

	minorno=MINORNO;

	#ifdef DEBUG 
		printk(KERN_ALERT"Hello Kernel \n");
	#endif

	ret1=alloc_chrdev_region(&devid,minorno,1,DEVNAME);

	if(ret1<0)
	{
		#ifdef DEBUG
			printk(KERN_ERR"Error : alloc_chrdev_region failed!! \n");
			goto OUT;
		#endif
	}

	#ifdef DEBUG 
		printk(KERN_ALERT"Registration Successful!! \n");
	#endif

	dev=kmalloc(sizeof(struct Dev),GFP_KERNEL);
	
	if(!dev)
	{
		#ifdef DEBUG
			printk(KERN_ERR"Error : kmalloc failed!! \n");
			goto OUT;
		#endif
	}

	memset(dev,'\0',sizeof(struct Dev));

	#ifdef DEBUG
		printk(KERN_ALERT"Memory Allocation Successful!! \n");
	#endif

	device_initialization();

	devno = MKDEV(MAJOR(devid),0);

	cdev_init(&dev->c_dev,&fops);

	dev->c_dev.owner = THIS_MODULE;
	dev->c_dev.ops = &fops;

	ret2=cdev_add(&dev->c_dev,devno,1);
	
	if(ret2<0)
	{
		#ifdef DEBUG
			printk(KERN_ERR"Error : cdev_add failed!! \n");
			goto OUT;
		#endif
	}

	#ifdef DEBUG
		printk(KERN_ALERT"(Major = %d,Minor = %d)",MAJOR(devno),MINOR(devno));
	#endif

	if( check_region(BASE,3) < 3 )
	{
		#ifdef DEBUG
			printk(KERN_ALERT"Releasing resources!! \n");
		#endif

		release_region(BASE,3);
	}	

	if( !request_region(BASE,3,DEVNAME) )
	{
		#ifdef DEBUG
			printk(KERN_ERR"Error : request_region failed!! \n");
			goto OUT;
		#endif
	}

	return 0;
OUT:
	return -1;
}

module_init(initfunc);

int device_initialization(void)
{
	#ifdef DEBUG
		printk(KERN_ALERT"Device Initialization Begins!! \n");
	#endif

	outb(0,DATA);
	outb(0,CONTROL);
	
	#ifdef DEBUG
		printk(KERN_ALERT"Device Initialization Successful!! \n");
	#endif

	return 0;
}
