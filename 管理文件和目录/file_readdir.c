#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
	int ret;
	DIR *dir;
	struct dirent *catlog;
	
	if(argc<2)
	{
		printf("Please input correct path\n");
		return 1;
	}
	
	//使用opendir打开目录
	dir = opendir(argv[1]);
	if(dir==NULL)
	{
		printf("open dir %s failed\n", argv[1]);
		return 1;
	}
	else
	{
		printf("opendir %s succeed\n", argv[1]);
	}
	
	//使用readdir查看目录
	catlog = readdir(dir);
	if(catlog==NULL)
	{
		printf("readdir %s failed\n", argv[1]);
		return 1;
	}
	else
	{
		printf("the d_ino of %s is %ld\n", argv[1], catlog->d_ino);
		printf("the file_name of %s is %s\n", argv[1], catlog->d_name);
		printf("readdir %s succeed\n", argv[1]);
	}
	
	ret = closedir(dir);
	if(ret)
	{
		printf("close dir %s failed\n", argv[1]);
		return 1;
	}
	else
	{
		printf("closedir %s succeed\n", argv[1]);
	}
	
	return 0;
}

