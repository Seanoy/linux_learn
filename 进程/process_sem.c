#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>  

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   // struct seminfo  *__buf;  /* Buffer for IPC_INFO
							   // (Linux-specific) */
};

static int sem_id = 0;

//�����ź�����ֵ
static int set_semvalue();
//ɾ���ź�����ֵ
static void del_semvalue();
//�ȴ��ź�
static int semaphore_p();
//�����ź�
static int semaphore_v();

int main(int argc, char* argv[])
{
	char message = 'X';
	int i = 0;
	
	//�����ź���
	sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);
	
	if(argc > 1)
	{
		//�����һ�α����ã���ʼ���ź���
		if(!set_semvalue())
        {  
            fprintf(stderr, "Failed to initialize semaphore\n");  
            exit(EXIT_FAILURE);  
        }
		//����Ҫ�������Ϣ���������ĵ�һ���ַ�
		message = argv[1][0];
		sleep(2);//����2s
	}
	
	for(i = 0; i < 10; i++)
	{
		//�����ٽ���
		if(!semaphore_p())
			exit(EXIT_FAILURE);
		//����Ļ�������
		printf("%c", message);
		//����������Ȼ���������ʱ��
		fflush(stdout);
		sleep(rand() % 3);
		//�뿪�ٽ���ǰ�����һ������
		printf(".%c", message);
		fflush(stdout);
        //�뿪�ٽ������������ʱ������ѭ��  
        if(!semaphore_v())  
            exit(EXIT_FAILURE);  
        sleep(rand() % 2);  
	}
	
	sleep(10);
    printf("\n%d - finished\n", getpid());
	
    if(argc > 1)
    {
        //��������ǵ�һ�α����ã������˳�ǰɾ���ź���  
        sleep(3);  
        del_semvalue();  
    }
    exit(EXIT_SUCCESS);
	
	return 0;
}

static int set_semvalue(void)
{
	//��ʼ���ź���
	union semun sem_union;
    sem_union.val = 1;  

	if(semctl(sem_id, 0, SETVAL, sem_union) == -1)
		return 0;
	return 1;
}

static void del_semvalue(void)
{
	//ɾ���ź���
	union semun sem_union;
	
	if(semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
		fprintf(stderr, "Failed to delete semaphore\n");
}

static int semaphore_p(void)
{
	//���ź������м�1���������ȴ��ź�
	struct sembuf sem_b;
	sem_b.sem_num = 0;//������0���ź���
	sem_b.sem_op = -1;//�ȴ��ź�
	sem_b.sem_flg = SEM_UNDO;
	
    if(semop(sem_id, &sem_b, 1) == -1)  
    {  
        fprintf(stderr, "semaphore_p failed\n");  
        return 0;  
    }  
    return 1;  
}

static int semaphore_v(void)
{
	//���ź������м�1�������ͷ��źţ�ʹ�ź�����Ϊ���ã��������ź�
	struct sembuf sem_b;
	sem_b.sem_num = 0;//������0���ź���
	sem_b.sem_op = 1;//�����ź�
	sem_b.sem_flg = SEM_UNDO;
	
    if(semop(sem_id, &sem_b, 1) == -1)  
    {  
        fprintf(stderr, "semaphore_v failed\n");  
        return 0;  
    }  
    return 1;  
}
