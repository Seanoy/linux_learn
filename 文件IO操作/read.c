#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define MAX_LENGTH 1000
void main()
{
	int fd;
	ssize_t length_wr,ret,length_rd=MAX_LENGTH;
	char *path = "./readtest";
	char data_wr[] = "Hello, seanOY!";
	char data_rd[MAX_LENGTH];
	
	if((fd=open(path, O_RDWR|O_CREAT,0777))<0)
	{
		printf("open %s failed!\n", path);
	}
	else
		printf("open success!\n");
	
	length_wr = write(fd,data_wr,strlen(data_wr));
	if(length_wr == -1)
	{
		printf("write error!\n");
	}
	else
		printf("write success!\n");
	
	close(fd);
	
	if((fd=open(path, O_RDWR|O_CREAT, 0777))<0)
	{
		printf("open %s failed!\n", path);
	}
	else
		printf("open success!\n");
	
	if((ret=read(fd,data_rd,length_rd))<0){
		printf("read error!\n");
	}
	else
		printf("read data: %s\n",data_rd);
	close(fd);
}


