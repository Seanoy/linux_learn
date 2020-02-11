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
	char txbuff[1024] = {0};
	//发送计数
	int count = 0;
	//判断输入参数是否正确
	if(argc < 1)
	{
		printf("please input ip address");
		return 1;
	}
	
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
	s_add.sin_addr.s_addr = inet_addr(argv[1]);
	s_add.sin_port = htons(portnum);
	
	while(1)
	{
		sprintf(txbuff, "Hello seanOY! count = %d", ++count);

		//发送数据到客户端
		if(-1 == sendto(sfd, txbuff, sizeof(txbuff), 0, (struct sockaddr *)&s_add, sizeof(s_add)))
		{
			printf("send data to server failed\n");
			return 1;
		}
		printf("send data to server succeed\n");
		sleep(1);
	}

	//关闭socket连接
	close(sfd);
	return 0;
}
