#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

//CMD 0���� 1����
//ioΪ0��LED����������
//ioΪ1��LED������������

int main(int argc, char* argv[]){
	int fd;
	char *leds="/dev/leds";
	
	printf("argv1 is cmd; argv2 is io\n");
	if(atoi(argv[1])>1){
		printf("argv1 is 0 or 1\n");
		exit(1);
	}
	if(atoi(argv[2])>1){
		printf("argv2 is 0 or 1\n");
		exit(1);
	}
	
	if((fd = open(leds, O_RDWR|O_NOCTTY|O_NDELAY))<0){
		printf("open %s failed\n", leds);
	}
	else{
		ioctl(fd, atoi(argv[1]), atoi(argv[2]));
		printf("ioctl %s success\n", leds);
	}
	close(fd);
	return 1;
}
