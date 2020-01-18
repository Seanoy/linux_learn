#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int ret;
	
	if(argc<2)
	{
		printf("Pleast input correct path\n");
		return 1;
	}
	
	ret = unlink(argv[1]);
	if(ret)
	{
		printf("unlink failed\n");
		return 1;
	}
	else
	{
		printf("unlink %s succeed!\n", argv[1]);
	}
	
	return 0;
}
