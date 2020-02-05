#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void filecopy(FILE *, char *);

int main(int argc, char* argv[])
{
	FILE *fp1;
	long int i = 100000;
	char buf[] = "I love Linux!";
	char *file1 = "data.txt";
	
	printf("create fifo test begins\n");
	
	if((fp1 = fopen(file1, "a+")) == NULL)
	{
		printf("open file %s failed\n", file1);
	}
	while(i--)
		filecopy(fp1, buf);
	
	fclose(fp1);
	
	printf("create fifo test is over\n");
	
	return 0;
}

void filecopy(FILE *fp, char *buf)
{
	char c;
	int i, j=0;
	i = strlen(buf) - 1;
	while(i--)
	{
		putc(buf[j], fp);
		j++;
	}
	putc('\n', fp);
}
