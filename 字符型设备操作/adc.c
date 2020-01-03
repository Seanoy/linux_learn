#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
//4412 ADC采样电压范围为0~1.8V 采样值为0~0xFFF，12位精度
int main(int argc, char* argv[]){
	int fd;
	char *adc = "/dev/adc";
	char buffer[512];
	int len = 0, r = 0;
	memset(buffer,0,sizeof(buffer));
	printf("adc ready!\n");
	
	if((fd = open(adc, O_RDWR|O_NOCTTY|O_NDELAY))<0){
		printf("open %s failed\n", adc);
		exit(1);
	}
	else
	{
		printf("open %s success\n", adc);
		
		len = read(fd, buffer, 10);
		
		if(len == 0)
			printf("return null\n");
		else
		{
			r = atoi(buffer);
			r = (int)(r*10000/4095);
			printf("adc value is %d\n", r);
		}
	}
	
	return 0;
}

