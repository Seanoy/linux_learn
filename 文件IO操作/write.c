#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void main()
{
	int fd;
	ssize_t length;
	char *path = "./writefile";
	char data[]="Hello,world!";
	
	if((fd = open(path, O_RDWR|O_CREAT,0777))<0){
		printf("open %s failed!\n", path);
	}
	
	length = write(fd, data, strlen(data));
	if(length==-1){
		perror("write error\n");
	}
	else{
		printf("write correct!\n");
	}
	close(fd);
}