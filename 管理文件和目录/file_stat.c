#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	struct stat groupstat1,groupstat2,groupstat3;
	int fd, ret;
	
	if(argc<2){
		printf("Please input file path\n");
		return 1;
	}
	
//stat test
	ret = stat(argv[1], &groupstat1);
	if(ret){
		printf("Please make sure path is correct\n");
		return 1;
	}
	else{
		printf("stat function test, %s indoe is %ld\n", argv[1], groupstat1.st_ino);
	}

//fstat test	
	fd = open(argv[1], O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd<0){
		printf("Please make sure path is correct\n");
		return 1;
	}
	ret = fstat(fd, &groupstat2);
	if(ret){
		printf("Please make sure path is correct\n");
	}
	else{
		printf("fstat function test, %s indoe is %ld\n", argv[1], groupstat2.st_ino);
	}
	
//lstat test
	ret = lstat(argv[1], &groupstat3);
	if(ret){
		printf("Please make sure path is correct\n");
		return 1;
	}
	else{
		printf("lstat function test, %s indoe is %ld\n", argv[1], groupstat3.st_ino);
	}
	
	return 0;
}



