#include <stdio.h>
#define __USE_GNU//为了get_current_dir_name能够正常使用
#include <unistd.h>

#define LENGTH 255
int main(void)
{
	char pwd[LENGTH];
	char *wd;
	
//getcwd test
	if(!getcwd(pwd, LENGTH)){
		perror("getcwd error");
		return 1;
	}
	else{
		printf("getcwd test\ndir:%s\n", pwd);
	}
	
//getwd test
	wd = getwd(pwd);
	if(!wd){
		perror("getwd error");
		return 1;
	}
	else{
		printf("getwd test\ndir:%s\n",pwd);
	}
	
//get_current_dir_name test
	wd = get_current_dir_name();
	if(!wd){
		perror("get_current_dir_name error\n");
		return 1;
	}
	else{
		printf("get_current_dir_name test\ndir:%s\n",pwd);
	}
	
	return 0;
}
