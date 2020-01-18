#include <stdio.h>
#include <time.h>
#include <string.h>

int main(void)
{
	time_t time_struct;
	struct tm *tblock;
	
	time(&time_struct);
	
	printf("ctime:%s\n", ctime(&time_struct));
	printf("asctime:%s\n", asctime(gmtime(&time_struct)));
	
	tblock = localtime(&time_struct);
	printf("local time:%s\n",asctime(tblock));
	printf("local time:%s\n",ctime(&time_struct));
	
	return 0;
}
