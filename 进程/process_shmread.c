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
	//���ڽ�������
	int running = 1;
	void *shm = NULL;
	struct shared_use_st *shared;
	//�����ڴ�id
	int shmid;
	//���������ڴ�
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	
	if(shmid == -1)
	{
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}
	
	//�������ڴ����ӵ���ǰ���̵ĵ�ַ�ռ�
	shm = shmat(shmid, (void*)0, 0);
    if(shm == (void*)-1)  
    {  
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);  
    }  
    printf("Memory attached at %p\n", shm);
	
	//���ù����ڴ�
    shared = (struct shared_use_st*)shm;
    shared->written = 0;
	
	//�����ڴ���д���� 
    while(running)//��ȡ�����ڴ��е�����  
    {  
        //û�н��������ڴ涨���������ݿɶ�ȡ  
        if(shared->written != 0)  
        {  
            printf("You wrote: %s", shared->text);  
            sleep(rand() % 3);  
            //��ȡ�����ݣ�����writtenʹ�����ڴ�ο�д  
            shared->written = 0;  
            //������end���˳�ѭ��������  
            if(strncmp(shared->text, "end", 3) == 0)  
                running = 0;  
        }  
        else//������������д���ݣ����ܶ�ȡ����  
            sleep(1);  
    }
    //�ѹ����ڴ�ӵ�ǰ�����з���  
    if(shmdt(shm) == -1)  
    {  
        fprintf(stderr, "shmdt failed\n");  
        exit(EXIT_FAILURE);  
    }  
    //ɾ�������ڴ�  
    if(shmctl(shmid, IPC_RMID, 0) == -1)  
    {  
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);  
    }      exit(EXIT_SUCCESS);  
}
