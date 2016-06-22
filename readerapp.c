#include"appheaders.h"

int readerapp(char *filename)
{
	int rfd;
	int count=0;
	int len;
	char *buff;
	char ch;
	int i;
//	int origin;
	
	rfd = open(filename,O_RDONLY);

	if(rfd<0)
	{
		perror("open");
		goto OUT;
	}

	printf("Enter the number of bytes to be read : ");
	scanf("%d",&len);

	buff=(char*)malloc(sizeof(char)*(len+1));

	
//	origin = app_origin();

//	lseek(rfd,18,origin);

	count = read(rfd,buff,len);

	*(buff + len) = '\0';

	printf("Number of bytes read : %d \n",count);

	printf("Data read from the device : %s \n",buff);

	close(rfd);

	return 0;
OUT:
	return -1;
}
