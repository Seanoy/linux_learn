#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

extern char **environ;

int main(int argc, char *argv[])
{
	if(execl("/home/topeet/Desktop/linuxsystemcode/process_exec_hello", "process_exec_hello", "execl", NULL) == -1)
	{
		perror("execl error\n");
		exit(1);
	}
	printf("execl error\n");//��������ʱ��Ӧ����ת������������
	return 0;
}
