#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int sig)
{
	printf("\nsignal trigged %d\n", sig);
}

int main(int argc, char* argv[])
{
	sigset_t sigset;//��¼������ mask
    sigset_t ign;//���ڼ�¼���������źż�  blocked
	
	struct sigaction act;//�źŶ���
	
	//����źż�  
    sigemptyset(&sigset);  //��ʼ���źż�
    sigemptyset(&ign); 

    //���źż�������ź�SIGINT  
    sigaddset(&sigset, SIGINT);

	//���ô��������źż�
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, 0);
	
    printf("Wait the signal SIGINT...\n");  
    pause();//������̣��ȴ��ź�  

    //���ý��������֣��ڱ�����Ϊ����SIGINT
	sigprocmask(SIG_SETMASK, &sigset, 0);
    printf("Please press Ctrl+c within 10 seconds...\n");  
    sleep(10); 
	
    //����SIGINT�Ƿ�����  
    sigpending(&ign);  
	
    if(sigismember(&ign, SIGINT))  
        printf("The SIGINT signal has ignored\n"); 
	
    //���źż���ɾ���ź�SIGINT  
    sigdelset(&sigset, SIGINT);  
    printf("Wait the signal SIGINT...\n"); 
	
    //�����̵��������������ã���ȡ����SIGINT������  
    //���������  
    sigsuspend(&sigset);  
  
    printf("The app will exit in 5 seconds!\n");  
    sleep(5);  
    exit(0);  
}
