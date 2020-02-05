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
	int msgid = -1;
    long int msgtype = 0; //注意1

	//创建消息队列
	msgid = msgget((key_t)1234, IPC_CREAT |0666);
	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error code : %d\n", errno);
		exit(EXIT_FAILURE);
	}
	
	//从消息队列获取消息
	while(running)
	{
		if(msgrcv(msgid, (void*)&msg_queue, MAX_LENGTH, msgtype, 0) == -1)
		{
			fprintf(stderr, "msgrcv failed with error code : %d\n", errno);  
            exit(EXIT_FAILURE);  
		}
		if(strncmp(msg_queue.text, "end", 3) == 0)
			running = 0;//stop
		printf("receive message : %s\n", msg_queue.text);
	}
	
    //删除消息队列  
    if(msgctl(msgid, IPC_RMID, 0) == -1)  
    {  
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);  
    }
	
	exit(EXIT_SUCCESS);  

	return 0;
}
