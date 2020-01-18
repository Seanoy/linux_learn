#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int ret;
	
	if(argc<3)
	{
		printf("Pleast input correct path\n");
		return 1;
	}
	
	ret = link(argv[1], argv[2]);
	if(ret)
	{
		printf("link failed\n");
		return 1;
	}
	else
	{
		printf("link %s to %s succeed!\n", argv[1], argv[2]);
	}
	
	return 0;
}
