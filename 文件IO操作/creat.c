//标准输入输出头文件
#include <stdio.h>

//文件操作函数头文件
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main()
{
	int fd;
	//需要新建的文件/bin/test3
	char *test3 = "/bin/test3";
	
	fd = creat(test3,0777);//路径test3下创建文件并将其权限设为777。
	if(fd = -1){
		printf("%s fd is %d\n",test3,fd);
	}
	else{
		printf("create %s is succeed\n",test3);
	}
}