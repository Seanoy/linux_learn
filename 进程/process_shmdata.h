#ifndef __PROCESS_SHMDATA_H  
#define __PROCESS_SHMDATA_H  
  
#define TEXT_SZ 2048  
  
struct shared_use_st  
{  
    //��д��־λ ��0���ɶ� 0����д
	int written;
	//��¼д��Ͷ�ȡ���ı�
    char text[TEXT_SZ];  
};  
  
#endif
