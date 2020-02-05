#ifndef __PROCESS_SHMDATA_H  
#define __PROCESS_SHMDATA_H  
  
#define TEXT_SZ 2048  
  
struct shared_use_st  
{  
    //读写标志位 非0：可读 0：可写
	int written;
	//记录写入和读取的文本
    char text[TEXT_SZ];  
};  
  
#endif
