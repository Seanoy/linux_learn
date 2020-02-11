#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int  main(int argc, char*argv[])
{
	struct in_addr ia;
	int portnum = 0x12345678;
	short portnum2 = 0x1234;
	int net, host;
	if(argc<2)
	{
		printf("please input correct parameters\n");
		return 1;
	}
	printf("address:%s\n",argv[1]);
	
	
	inet_aton(argv[1], &ia);
	printf("inet_aton:0x%x\n", ia.s_addr);
	
	printf("inet_addr:0x%x\n", inet_addr(argv[1]));

	printf("inet_network:0x%x\n", inet_network(argv[1]));

	printf("inet_ntoa:%s\n", inet_ntoa(ia));
	
	host = inet_lnaof(ia);
	printf("inet_lnaof:0x%x\n", host);
	
 	net = inet_netof(ia);
	printf("inet_netof:0x%x\n", net);
	
	ia = inet_makeaddr(net,host);
	printf("inet_makeaddr:0x%x\n\n\n", ia.s_addr);

	printf("portnum:0x%x\n", portnum);
	
	printf("htonl:0x%x\n",htonl(portnum));
	printf("htons:0x%x\n",htons(portnum2));

	printf("ntohl:0x%x\n",ntohl(portnum));
	printf("ntohs:0x%x\n",ntohs(portnum2));


	return 0;
}
