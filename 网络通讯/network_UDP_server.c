#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[])
{	
	//socket�ļ�������
	int sfd;
	//socket��ַ�ṹ��
	struct sockaddr_in s_add;
	//�˿ں�
	int portnum = 0x1234;
	//���ݻ�����
	char rxbuff[1024] = {0};
	
	//����һ������UDP���ӵ�socket
	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(sfd == -1)
	{
		printf("create socket failed\n");
		return 1;
	}
	printf("create socket succeed\n");
	
	//���õ�ַ����
	bzero(&s_add, sizeof(s_add));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = htonl(INADDR_ANY);
	s_add.sin_port = htons(portnum);
	
	//��s_add��socket��
	if(-1 == bind(sfd, (struct sockaddr *)&s_add, sizeof(s_add)))
	{
		printf("bind failed\n");
		return 1;
	}
	printf("bind succeed\n");
	
	while(1)
	{
		//���տͻ��˷��͵�����
		if(-1 == read(sfd, rxbuff, sizeof(rxbuff)))
		{
			printf("recv from client failed\n");
			return 1;
		}
		printf("receive data from client:%s\n", rxbuff);
	}

	//�ر�socket����
	close(sfd);
	return 0;
}
