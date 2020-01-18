#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int ret;
	if(argc<2){
		printf("Please input correct path\n");
		return 1;
	}
	
	ret = mkdir(argv[1], 0777);
	if(ret<0){
		printf("mkdir %s failed\n", argv[1]);
		return 1;
	}
	else{
		printf("mkdir %s succeed\n", argv[1]);
	}
	
	return 0;
}
