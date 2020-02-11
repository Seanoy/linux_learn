#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[])
{
	//socket�ļ��������������� �� ��������������
	int sfd, nfd;
	
	//���ʹ���ͳ��
	int count = 0;
	
	//����˵�ַ �ͻ��˵�ַ
	struct sockaddr_in s_add, c_add;
	
	//�ṹ���С
	int sin_size;
	
	//�˿�
	unsigned short portnum = 0x1234;
	
	//���ͻ�����
	char buffer[1024] = {0};
	
	printf("This is server\n");
	
	//�����׽���
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
	{
		printf("create socket failed!\n");
		return 1;
	}
	printf("create socket succeed!\n");
	
	//���÷�����׽��ֵĵ�ַ����
	bzero(&s_add, sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = htonl(INADDR_ANY);
	s_add.sin_port = htons(portnum);
	
	//���׽���
	if(-1 == bind(sfd, (struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
		printf("bind failed\n");
		return 1;
	}
	printf("bind succeed\n");
	
	//�����׽���
	if(-1 == listen(sfd, 5))
	{
		printf("listen failed\n");
		return 1;
	}
	printf("listen succeed\n");
	
	//��ȡ�ͻ����׽���
	sin_size = sizeof(struct sockaddr_in);
	nfd = accept(sfd, (struct sockaddr *)(&c_add), &sin_size);
	if(-1 == nfd)
	{
		printf("accept failed\n");
		return 1;
	}
	
	//��ӡ������Ϣ
	printf("accept succeed\n");
	printf("server connect from %#x : %#x", ntohl(c_add.sin_addr.s_addr), ntohs(c_add.sin_port));
	
	while(1)
	{
		//ͨ���׽��ַ�������
		memset(buffer, 0, sizeof(buffer));
		sprintf(buffer, "Hello, seanOY! count = %d\n", count++);
		send(nfd, buffer, strlen(buffer), 0);
		sleep(1);
	}
	
    //�ر���������
	close(nfd);
    //�رռ���
	clock(sfd);
	
	return 0;
}
