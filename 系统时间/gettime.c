#include <time.h>
#include <stdio.h>

int main(void)
{
	time_t time_strcut;
	time(&time_strcut);
	printf("UTC Time:%ld\n", time_strcut);
	
	time_strcut = time(NULL);
	printf("UTC Time:%ld\n", time_strcut);

	return 0;
}