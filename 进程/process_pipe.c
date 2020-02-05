#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

//���̶�����
void read_data(int *);
//����д���� 
void write_data(int *);

//�����ܵ�ֻ�����ڸ����̺��ӽ��̼��ͨѶ�������ǰ�˫��ͨѶ��ʽ��
int main(int argc, char* argv[])
{
	int pipes[2], ret;
	pid_t pid;
	
	ret = pipe(pipes);//�����ܵ�
	if(ret == -1)
	{
		perror("pipe error\n");
		exit(1);
	}
	
	pid = fork();//��������
	
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

//���̶�����
void read_data(int pipes[])
{
	int ch, ret;
	
	close(pipes[1]);//�ر�д����
	
	while( (ret = read(pipes[0], &ch, 1)) > 0 )
	{
		putchar(ch);
	}
	exit(0);
}

//����д���� 
void write_data(int pipes[])
{
	int ch, ret;
	
	close(pipes[0]);//�رն�����
	
	while( (ch = getchar()) > 0 )
	{
		ret = write( pipes[1], &ch, 1);//д��ܵ�
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
