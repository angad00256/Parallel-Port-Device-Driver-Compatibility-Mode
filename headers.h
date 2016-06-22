#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/ioport.h>
#include<asm/io.h>
#include<linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Angad");

#ifndef DEBUG
	#define DEBUG
#endif

#ifndef DEVNAME
	#define DEVNAME "mydriver"
#endif

#ifndef BASE
	#define BASE 0x378
#endif

#ifndef DATA
	#define DATA 0x378
#endif

#ifndef STATUS
	#define STATUS 0x379
#endif

#ifndef CONTROL
	#define CONTROL 0x37A
#endif

#ifndef MAJORNO 
	#define MAJORNO 0
#endif

#ifndef MINORNO
	#define MINORNO 0
#endif

