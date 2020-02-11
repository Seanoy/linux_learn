#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>          //See NOTES
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[])
{
	//�û��˵��׽����ļ�������
	int cfd;
	
	//�ӿͻ��˽��յ��ֽ���
	int rxbyte;
	
	//�洢���յ�����
	char buffer[1024] = {0};
	
	//����˵�ַ�ṹ��
	struct sockaddr_in s_add;
	
	//�˿ں�
	unsigned short portnum = 0x1234;
	
	printf("This is client\n");
	
	if(argc < 2)
	{
		printf("please input server ip\n");
		return 1;
	}
	
	//�����׽���
	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if(cfd == -1)
	{
		printf("create socket failed!\n");
		return 1;
	}
	printf("create socket succeed!\n");
	
	//�����׽���Ҫ���ӵķ���˵ĵ�ַ����
	bzero(&s_add, sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_port = htons(portnum);
	s_add.sin_addr.s_addr = inet_addr(argv[1]);
	printf("s_addr = %#x, port : %#x\r\n", s_add.sin_addr.s_addr, s_add.sin_port);
	
	
	//ʹ���׽��ֽ�������
	if(-1 == connect(cfd, (struct sockaddr *) (&s_add), sizeof(struct sockaddr)))
	{
		printf("connect failed\n");
		return 1;
	}	
	printf("connect succeed\n");
	
	while(1)
	{
		//ͨ���׽��ֽ�������
		if(-1 == (rxbyte = read(cfd, buffer, sizeof(buffer))))
		{
			printf("read data failed\n");
			return 1;
		}
		printf("read succeed\n");
		buffer[rxbyte] = '\0';
		printf("read data: %s \n", buffer);
	}
	
	//�ر���������
	close(cfd);
	
	return 0;
}
