#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	char *arg[] = {"ls", "-a", NULL};//exec簇函数传入参数要以NULL为结尾
	
	if(fork() == 0)//子线程1
	{
		printf("fork1 succeed.\nexecl test\n");
		
		if(execl("/bin/ls", "ls", "-a", NULL) == -1)//发生错误
		{
			perror("execl error.\n");
			exit(1);
		}
	}
	
	usleep(20000);
	if(fork() == 0)//子线程2
	{
		printf("\n\nfork2 succeed.\nexecv test\n");
		
		if(execv("/bin/ls", arg) == -1)
		{
			perror("execv error.\n");
			exit(1);
		}
	}
	
	usleep(20000);
	if(fork() == 0)//子线程3
	{
		printf("\n\nfork3 succeed.\nexeclp test\n");
		
		if(execlp("ls", "ls", "-a", NULL) == -1)
		{
			perror("execp error.\n");
			exit(1);
		}
	}
	
	usleep(20000);
	if(fork() == 0)//子线程4
	{
		printf("\n\nfork4 succeed.\nexecvp test\n");
		
		if(execvp("ls", arg) == -1)
		{
			perror("execvp error.\n");
			exit(1);
		}
	}
	
	usleep(20000);
	if(fork() == 0)//子线程5
	{
		printf("\n\nfork5 succeed.\nexecle test\n");
		
		if(execle("/bin/ls", "ls", "-a", NULL, NULL) == -1)
		{
			perror("execle error.\n");
			exit(1);
		}
	}
	
	usleep(20000);
	if(fork() == 0)//子线程6
	{
		printf("\n\nfork6 succeed.\nexecve test\n");
		
		if(execve("/bin/ls", arg, NULL) == -1)
		{
			perror("execve error.\n");
			exit(1);
		}
	}
	
	usleep(20000);
	return 0;
}
