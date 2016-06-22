extern dev_t devid;
extern struct Dev *dev;

struct Dev
{
	struct cdev c_dev;
};

int device_initialization(void);

int dev_open(struct inode*,struct file*); 

ssize_t dev_write(struct file *,const char __user *,size_t,loff_t *);

ssize_t dev_read(struct file *,char __user *,size_t,loff_t *);
/*
int dev_release(struct inode*,struct file*); 
loff_t dev_seek(struct file *,loff_t,int);
*/
