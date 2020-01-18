#include <stdio.h>

int main(int argc, char* argv[])
{
	int ret;
	
	if(argc<3)
	{
		printf("Please input correct path\n");
		return 1;
	}
	else
	{
		ret = rename(argv[1], argv[2]);
		if(ret)
		{
			perror("rename error\n");
			return 1;
		}
		else
		{
			printf("rename %s to %s succeed!\n", argv[1], argv[2]);
		}
	}
	
	return 0;
}