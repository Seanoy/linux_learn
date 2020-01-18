#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int fd, ret;
	
	if(argc<3){
		printf("Please input file path\n");
		return 1;
	}
	
//chmod test
	ret = chmod(argv[1], 0777);
	if(ret<0){
		printf("Please make sure path is correct\n");
		return 1;
	}
	else{
		printf("chmod 0777 %s succeed!\n", argv[1]);
	}

//fchmod test	
	fd = open(argv[2], O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd<0){
		printf("Please make sure path is correct\n");
		return 1;
	}
	ret = fchmod(fd, 0555);
	if(ret<0){
		printf("Please make sure path is correct\n");
	}
	else{
		printf("fchmod 0555 %s succeed!\n", argv[2]);
	}
	
	return 0;
}
