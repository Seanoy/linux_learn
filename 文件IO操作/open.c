#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main()
{
	int fd;
	char *leds = "/dev/leds";
	char *test1 = "/bin/test1";
	char *test2 = "/bin/test2";
	
	if((fd = open(leds,O_RDWR|O_NOCTTY|O_NDELAY))<0)
		printf("open %s failed\n", leds);
	else
		printf("%s fd is %d", leds, fd);
	
	if((fd = open(test1, O_RDWR,0777))<0)
		printf("open %s failed\n", test1);
	else
		printf("%s fd is %d", test1, fd);
	
	if((fd = open(test2, O_RDWR|O_CREAT,0777))<0)
		printf("open %s failed\n", test2);
	else
		printf("%s fd is %d", test2, fd);
}
