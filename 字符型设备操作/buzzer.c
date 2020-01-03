#include <stdio.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int fd, ret;
	char *buzzer = "/dev/buzzer_ctl";
	
	if(atoi(argv[1])>1){
		printf("arg1 is 0 or 1\n");
		exit(1);
	}
		
	if((fd = open(buzzer, O_RDWR|O_NOCTTY|O_NDELAY))<0){
		printf("open %s failed\n", buzzer);
		exit(1);
	}
	else{
		ret = ioctl(fd, atoi(argv[1]), atoi(argv[2]));
		printf("ioctl %s success", buzzer);
	}
	close(fd);
	return 0;
}
