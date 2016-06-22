#include"headers.h"
#include"declarations.h"

ssize_t dev_write(struct file *fileptr, const char __user *ubuff, size_t size, loff_t *pos)
{
	struct Dev *ldev;
	char *kbuff;
	int ret;
	int nocsc;
	int nocsw;
	int i;
	char ch;
	unsigned char status;

	kbuff=NULL;
	ret=0;
	nocsc=0;
	nocsw=0;
	i=0;

	ldev = fileptr->private_data; 

	if(!ldev)
	{
		#ifdef DEBUG
			printk(KERN_ERR"Device Not Found!! \n");
		#endif
		goto OUT;
	}

	kbuff = kmalloc(sizeof(char)*(size+1),GFP_KERNEL);

	if(!kbuff)
	{
		#ifdef DEBUG
			printk(KERN_ERR"kmalloc failed!! \n");
		#endif
		goto OUT;
	}
	
	memset(kbuff,'\0',sizeof(char)*(size+1));
	
	ret = copy_from_user(kbuff,ubuff,size);

	nocsc = size - ret;

	#ifdef DEBUG
		printk(KERN_ALERT"Write Operation Begins!! \n");
		printk(KERN_ALERT"Data To Be Written : %s \n",kbuff);
	#endif

	outb(0,CONTROL);

	for(i=0;i<size;i++)
	{
		ch = *(kbuff+i);

		#ifdef DEBUG
			printk(KERN_ALERT"Character Written : %c \n",ch);
		#endif

		outb(ch,DATA);

		if( i%2 == 0 )
		{
			#ifdef DEBUG
				printk(KERN_ALERT"Even Case \n");
			#endif

			outb(1,CONTROL);

			do
			{
				status ^= status;
				status = inb(STATUS);
				status = status >> 7;
				status = status & 1;
			}while( status != 0x01);
		}

		else
		{
			#ifdef DEBUG
				printk(KERN_ALERT"Odd Case \n");
			#endif

			outb(0,CONTROL);

			do
			{
				status ^= status;
				status = inb(STATUS);
				status = status >> 7;
				status = status & 1;
			}while( status != 0x00);
		}

		nocsw++;
	}

	#ifdef DEBUG
		printk(KERN_ALERT"Writing Done Successfully!! \n");
	#endif

	return nocsw;
OUT:
	return -1;	
}
