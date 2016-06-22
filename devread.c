#include"headers.h"
#include"declarations.h"

ssize_t dev_read(struct file *fileptr, char __user *ubuff, size_t size, loff_t *pos)
{
	struct Dev *ldev;
	char *kbuff;
	int ret;
	int nocsc;
	int nocsr;
	int i;
	unsigned char ch;
	unsigned char status;

	kbuff=NULL;
	ret=0;
	nocsc=0;
	nocsr=0;
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

	#ifdef DEBUG
		printk(KERN_ALERT"Read Operation Begins!! \n");
	#endif

	outb(32,CONTROL);

	for(i=0;i<size;i++)
	{
		if( i%2 == 0 )
		{
			#ifdef DEBUG
				printk(KERN_ALERT"Even Case \n");
			#endif

			outb(32,CONTROL);

			do
			{
				status ^= status;
				status = inb(STATUS);
				status = status >> 7;
				status = status & 1;
			}while( status != 0x01);

			if( i == size - 1 )
			{
				outb(33,CONTROL);
			}
		}

		else
		{
			#ifdef DEBUG
				printk(KERN_ALERT"Odd Case \n");
			#endif

			outb(33,CONTROL);

			do
			{
				status ^= status;
				status = inb(STATUS);
				status = status >> 7;
				status = status & 1;
			}while( status != 0x00);
			
			if( i == size - 1 )
			{
				outb(32,CONTROL);
			}
		}

		ch = inb(DATA);

		#ifdef DEBUG
			printk(KERN_ALERT"Character Read : %c \n",ch);
		#endif
			
		*(kbuff+i) = ch;

		nocsr++;
	}

	#ifdef DEBUG
		printk(KERN_ALERT"Data Read : %s \n",kbuff);
	#endif

	ret = copy_to_user(ubuff,kbuff,size);

	nocsc = size - ret;

	#ifdef DEBUG
		printk(KERN_ALERT"Writing Done Successfully!! \n");
	#endif

	return nocsc;
OUT:
	return -1;	
}
