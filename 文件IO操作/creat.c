//��׼�������ͷ�ļ�
#include <stdio.h>

//�ļ���������ͷ�ļ�
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main()
{
	int fd;
	//��Ҫ�½����ļ�/bin/test3
	char *test3 = "/bin/test3";
	
	fd = creat(test3,0777);//·��test3�´����ļ�������Ȩ����Ϊ777��
	if(fd = -1){
		printf("%s fd is %d\n",test3,fd);
	}
	else{
		printf("create %s is succeed\n",test3);
	}
}