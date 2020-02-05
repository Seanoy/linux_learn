#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "process_shmdata.h"  

int main(int argc, char* argv[])
{
	//用于结束程序
	int running = 1;
	void *shm = NULL;
	struct shared_use_st *shared;
	//共享内存id
	int shmid;
	//创建共享内存
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	
	if(shmid == -1)
	{
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}
	
	//将共享内存连接到当前进程的地址空间
	shm = shmat(shmid, (void*)0, 0);
    if(shm == (void*)-1)  
    {  
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);  
    }  
    printf("Memory attached at %p\n", shm);
	
	//设置共享内存
    shared = (struct shared_use_st*)shm;
    shared->written = 0;
	
	//向共享内存中写数据 
    while(running)//读取共享内存中的数据  
    {  
        //没有进程向共享内存定数据有数据可读取  
        if(shared->written != 0)  
        {  
            printf("You wrote: %s", shared->text);  
            sleep(rand() % 3);  
            //读取完数据，设置written使共享内存段可写  
            shared->written = 0;  
            //输入了end，退出循环（程序）  
            if(strncmp(shared->text, "end", 3) == 0)  
                running = 0;  
        }  
        else//有其他进程在写数据，不能读取数据  
            sleep(1);  
    }
    //把共享内存从当前进程中分离  
    if(shmdt(shm) == -1)  
    {  
        fprintf(stderr, "shmdt failed\n");  
        exit(EXIT_FAILURE);  
    }  
    //删除共享内存  
    if(shmctl(shmid, IPC_RMID, 0) == -1)  
    {  
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);  
    }      exit(EXIT_SUCCESS);  
}
