#include <stdio.h>
#include <sys/time.h>
//���»�ȡ��������ʱ��

void test(void)
{
	int i,j;
	double k;
	for(i=1000;i>0;i--)
		for(j=1000;j>0;j--)
			k=i/j;
}

int main(void)
{
	struct timeval time_begin, time_end;
	int interval_s, interval_us;
	float interval;
	gettimeofday(&time_begin, NULL);
	test();
	gettimeofday(&time_end, NULL);
	interval_s = time_end.tv_sec - time_begin.tv_sec;//��
	interval_us = time_end.tv_usec - time_begin.tv_usec;//΢��
	interval = interval_s*1000000 + interval_us;
	interval/=1000000;
	printf("test run time:%fs\n", interval);

	return 0;
}
