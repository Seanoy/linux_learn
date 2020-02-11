#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[])
{
	//socket文件描述符（监听） 和 网络连接描述符
	int sfd, nfd;
	
	//发送次数统计
	int count = 0;
	
	//服务端地址 客户端地址
	struct sockaddr_in s_add, c_add;
	
	//结构体大小
	int sin_size;
	
	//端口
	unsigned short portnum = 0x1234;
	
	//发送缓冲区
	char buffer[1024] = {0};
	
	printf("This is server\n");
	
	//创建套接字
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
	{
		printf("create socket failed!\n");
		return 1;
	}
	printf("create socket succeed!\n");
	
	//设置服务端套接字的地址属性
	bzero(&s_add, sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = htonl(INADDR_ANY);
	s_add.sin_port = htons(portnum);
	
	//绑定套接字
	if(-1 == bind(sfd, (struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
		printf("bind failed\n");
		return 1;
	}
	printf("bind succeed\n");
	
	//监听套接字
	if(-1 == listen(sfd, 5))
	{
		printf("listen failed\n");
		return 1;
	}
	printf("listen succeed\n");
	
	//获取客户端套接字
	sin_size = sizeof(struct sockaddr_in);
	nfd = accept(sfd, (struct sockaddr *)(&c_add), &sin_size);
	if(-1 == nfd)
	{
		printf("accept failed\n");
		return 1;
	}
	
	//打印连接信息
	printf("accept succeed\n");
	printf("server connect from %#x : %#x", ntohl(c_add.sin_addr.s_addr), ntohs(c_add.sin_port));
	
	while(1)
	{
		//通过套接字发送数据
		memset(buffer, 0, sizeof(buffer));
		sprintf(buffer, "Hello, seanOY! count = %d\n", count++);
		send(nfd, buffer, strlen(buffer), 0);
		sleep(1);
	}
	
    //关闭网络连接
	close(nfd);
    //关闭监听
	clock(sfd);
	
	return 0;
}
