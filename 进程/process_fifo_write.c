#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char* argv[])
{
	const char *fifo_name = "my_fifo";
	char *file1 = "data.txt";
	int pipe_fd = -1;
	int data_fd = -1;
	int res = 0;
	const int open_mode = O_WRONLY;
	int bytes_send = 0;
	char buffer[PIPE_BUF + 1];
	
	if(access(fifo_name, F_OK) == -1)
	{
		res = mkfifo(fifo_name, 0777);
		if(res != 0)
		{
			fprintf(stderr, "Couldn't create fifo %s\n", fifo_name);
			exit(EXIT_FAILURE);
		}
	}
	
	printf("process %d opening FIFO O_WRONLY\n", getpid());
	pipe_fd = open(fifo_name, open_mode);
	data_fd = open(file1, O_RDONLY);
    printf("process %d result %d\n", getpid(), pipe_fd);  
	
	if(pipe_fd != -1)
	{
		int bytes_read = 0;
		//���ļ���ȡ����
		bytes_read = read(data_fd, buffer, PIPE_BUF);
		buffer[bytes_read] = '\0';
		while(bytes_read > 0)
		{
			//��FIFOд����
			res = write(pipe_fd, buffer, bytes_read);
			if(res == -1)
			{
				fprintf(stderr, "write pipe error\n");
				exit(EXIT_FAILURE);
			}
			//�ۼ�д���ֽ�������������ȡ����
			bytes_send += res;
			bytes_read = read(data_fd, buffer, PIPE_BUF);
			buffer[bytes_read] = '\0';
		}
        close(pipe_fd);  
        close(data_fd);  
	}
	else
        exit(EXIT_FAILURE);  

    printf("process %d finished\n", getpid());  
	
	return 0;
}
