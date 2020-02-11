#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>

void main()
{
	printf("sizeof(short int):%ld\n", sizeof(short int));
	printf("sizeof(unsigned short int):%ld\n", sizeof(unsigned short int));
	printf("sizeof(struct in_addr):%ld\n", sizeof(struct in_addr));
}
