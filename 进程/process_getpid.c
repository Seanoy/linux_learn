#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	pid_t idp, id;
	
	idp = getppid();
	printf("ppid = %d\n", idp);
	
	id = getpid();
	printf("pid = %d\n", id);
	return 0;
}

