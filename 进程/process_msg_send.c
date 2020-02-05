#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_LENGTH 512

struct msg_st
{
	long int msg_type;
	char text[MAX_LENGTH];
};

int main(int argc, char* argv[])
{
	int running = 1;
	struct msg_st msg_queue;
	char buffer[MAX_LENGTH];
	int msgid = -1;
	
	//创建消息队列
	msgid = msgget((key_t)1234, IPC_CREAT | 0666);
	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error code : %d\n", errno);
		exit(EXIT_FAILURE);
	}
	
	//向消息队列写消息
	while(running)
	{
		printf("Enter some message:");
		fgets(buffer, MAX_LENGTH, stdin);
		msg_queue.msg_type = 1;
		strcpy(msg_queue.text, buffer);
		//向消息队列发消息
		if(msgsnd(msgid, (void*)&msg_queue, MAX_LENGTH, 0) == -1)
		{
			fprintf(stderr, "msgsnd failed with error code : %d\n", errno);  
            exit(EXIT_FAILURE);  
		}
		if(strncmp(buffer, "end", 3) == 0)
			running = 0;//stop
		//sleep(1);
	}
	exit(EXIT_SUCCESS);  
}
