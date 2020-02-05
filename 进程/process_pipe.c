#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

//进程读函数
void read_data(int *);
//进程写函数 
void write_data(int *);

//无名管道只能用于父进程和子进程间的通讯，而且是半双工通讯方式。
int main(int argc, char* argv[])
{
	int pipes[2], ret;
	pid_t pid;
	
	ret = pipe(pipes);//创建管道
	if(ret == -1)
	{
		perror("pipe error\n");
		exit(1);
	}
	
	pid = fork();//创建进程
	
	switch(pid)
	{
		case -1:
			perror("fork error\n");
			exit(1);
		case 0:
			read_data(pipes);
		default:
			write_data(pipes);
	}
	
	return 0;
}

//进程读函数
void read_data(int pipes[])
{
	int ch, ret;
	
	close(pipes[1]);//关闭写描述
	
	while( (ret = read(pipes[0], &ch, 1)) > 0 )
	{
		putchar(ch);
	}
	exit(0);
}

//进程写函数 
void write_data(int pipes[])
{
	int ch, ret;
	
	close(pipes[0]);//关闭读描述
	
	while( (ch = getchar()) > 0 )
	{
		ret = write( pipes[1], &ch, 1);//写入管道
		if(ret == -1)
		{
			perror("parent write");
			close(pipes[1]);
			exit(1);
		}
	}
	close(pipes[1]);
	exit(0);
}
