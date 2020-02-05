#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	pid_t pid;
	int i=100;
	
	pid = fork();
	if(pid == -1)//出错
	{
		printf("fork failed\n");
		return 1;
	}
	else if(pid)//返回父进程子进程号，返回值大于0
	{
		i++;
		printf("parent i is %d\n", i);
		printf("parent return value is %d\n", pid);
		printf("parent pid is %d\n", getpid());
		printf("parent ppid is %d\n", getppid());
		while(1);
	}
	else//返回子进程，返回值等于0
	{
		i++;
		printf("child i is %d\n", i);
		printf("child return value is %d\n", pid);
		printf("child pid is %d\n", getpid());
		printf("child ppid is %d\n", getppid());
	}
	
	return 0;
}
