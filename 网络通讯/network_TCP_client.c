#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>          //See NOTES
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[])
{
	//用户端的套接字文件描述符
	int cfd;
	
	//从客户端接收的字节数
	int rxbyte;
	
	//存储接收的数据
	char buffer[1024] = {0};
	
	//服务端地址结构体
	struct sockaddr_in s_add;
	
	//端口号
	unsigned short portnum = 0x1234;
	
	printf("This is client\n");
	
	if(argc < 2)
	{
		printf("please input server ip\n");
		return 1;
	}
	
	//创建套接字
	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if(cfd == -1)
	{
		printf("create socket failed!\n");
		return 1;
	}
	printf("create socket succeed!\n");
	
	//设置套接字要连接的服务端的地址属性
	bzero(&s_add, sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_port = htons(portnum);
	s_add.sin_addr.s_addr = inet_addr(argv[1]);
	printf("s_addr = %#x, port : %#x\r\n", s_add.sin_addr.s_addr, s_add.sin_port);
	
	
	//使用套接字进行连接
	if(-1 == connect(cfd, (struct sockaddr *) (&s_add), sizeof(struct sockaddr)))
	{
		printf("connect failed\n");
		return 1;
	}	
	printf("connect succeed\n");
	
	while(1)
	{
		//通过套接字接收数据
		if(-1 == (rxbyte = read(cfd, buffer, sizeof(buffer))))
		{
			printf("read data failed\n");
			return 1;
		}
		printf("read succeed\n");
		buffer[rxbyte] = '\0';
		printf("read data: %s \n", buffer);
	}
	
	//关闭网络连接
	close(cfd);
	
	return 0;
}
