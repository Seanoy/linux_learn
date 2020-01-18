#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define LENGTH 255

int main(int argc, char* argv[])
{
	int ret;
	char pwd[LENGTH];
	
	if(argc<3)
	{
		printf("Please input correct path\n");
		return 1;
	}
	
	if(!getcwd(pwd, LENGTH))
	{
		perror("getcwd error");
		return 1;
	}
	else
	{
		printf("getcwd is %s\n", pwd);
	}
	//转入其他目录
	ret = chdir(argv[1]);
	if(ret)
	{
		printf("Pleast input correct path\n");
		return 1;
	}
	else
	{
		printf("chdir %s succeed\n",argv[1]);
	}
	
	//删除目录
	ret = rmdir(argv[2]);
	if(ret)
	{
		printf("Pleast input correct path\n");
		return 1;
	}
	
	//回到初始目录
	ret = chdir(pwd);
	if(ret)
	{
		printf("Pleast input correct path\n");
		return 1;
	}
	else
	{
		printf("chdir %s succeed\n",pwd);
	}
	
	return 0;
}

