#include"headers.h"
#include"declarations.h"

int dev_open(struct inode *inodeptr,struct file *fileptr) 
{
	struct Dev *ldev;

	#ifdef DEBUG
		printk(KERN_ALERT"Device Opening Begins!! \n");
	#endif

	ldev = container_of(inodeptr->i_cdev,struct Dev,c_dev);

	if(!ldev)
	{
		#ifdef DEBUG
			printk(KERN_ERR"container_of failed!! \n");
		#endif
	}	

	fileptr->private_data = ldev;
		
	#ifdef DEBUG
		printk(KERN_ALERT"Device Opened Successfully!! \n");
	#endif

	return 0;
}
