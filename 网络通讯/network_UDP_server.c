#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[])
{	
	//socket文件描述符
	int sfd;
	//socket地址结构体
	struct sockaddr_in s_add;
	//端口号
	int portnum = 0x1234;
	//数据缓存区
	char rxbuff[1024] = {0};
	
	//创建一个用于UDP连接的socket
	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(sfd == -1)
	{
		printf("create socket failed\n");
		return 1;
	}
	printf("create socket succeed\n");
	
	//设置地址变量
	bzero(&s_add, sizeof(s_add));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = htonl(INADDR_ANY);
	s_add.sin_port = htons(portnum);
	
	//绑定s_add到socket上
	if(-1 == bind(sfd, (struct sockaddr *)&s_add, sizeof(s_add)))
	{
		printf("bind failed\n");
		return 1;
	}
	printf("bind succeed\n");
	
	while(1)
	{
		//接收客户端发送的数据
		if(-1 == read(sfd, rxbuff, sizeof(rxbuff)))
		{
			printf("recv from client failed\n");
			return 1;
		}
		printf("receive data from client:%s\n", rxbuff);
	}

	//关闭socket连接
	close(sfd);
	return 0;
}
