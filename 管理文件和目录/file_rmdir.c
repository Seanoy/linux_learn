#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int ret;
	if(argc<2){
		printf("Please input correct path\n");
		return 1;
	}
	
	ret = rmdir(argv[1]);
	if(ret<0){
		printf("rmdir %s failed\n", argv[1]);
		return 1;
	}
	else{
		printf("rmdir %s succeed\n", argv[1]);
	}
	
	return 0;
}
