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
	char txbuff[1024] = {0};
	//���ͼ���
	int count = 0;
	//�ж���������Ƿ���ȷ
	if(argc < 1)
	{
		printf("please input ip address");
		return 1;
	}
	
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
	s_add.sin_addr.s_addr = inet_addr(argv[1]);
	s_add.sin_port = htons(portnum);
	
	while(1)
	{
		sprintf(txbuff, "Hello seanOY! count = %d", ++count);

		//�������ݵ��ͻ���
		if(-1 == sendto(sfd, txbuff, sizeof(txbuff), 0, (struct sockaddr *)&s_add, sizeof(s_add)))
		{
			printf("send data to server failed\n");
			return 1;
		}
		printf("send data to server succeed\n");
		sleep(1);
	}

	//�ر�socket����
	close(sfd);
	return 0;
}
