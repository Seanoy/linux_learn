//��׼��
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�ļ�IO����
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//���ڲ���
#include <termios.h>
#include <unistd.h>

int uart_init(int,int,int,char,int);

int main(int argc, char* argvp[])
{
	int fd, wr_return, i=10;
	char *uart3 = "/dev/ttySAC3";
	char *buffer = "Hello Seanoy!\n";
	
	printf("\r\n uart3 write test start\r\n");
	
	if((fd = open(uart3, O_RDWR|O_NOCTTY|O_NDELAY))<0){
		printf("open %s failed\r\n", uart3);
	}
	else{
		printf("open %s succeed\r\n", uart3);
		uart_init(fd, 115200, 8, 'N', 1);
		while(i--)
		{
			wr_return = write(fd, buffer, strlen(buffer));
			if(wr_return<0)
				printf("uart3 write failed\r\n");
			else
				printf("uart3 write return %d\r\n", wr_return);
			sleep(1);//����1s
		}
	}
	close(fd);//�ر��ļ�
	return 0;
}

int uart_init(int fd, int nSpeed, int nBits, char nEvent, int nStop){
	struct termios newtio, oldtio;
	if( tcgetattr(fd, &oldtio) !=0 ){
		perror("SetupSerial 1");
		return -1;
	}
	bzero( &newtio, sizeof(newtio));
	newtio.c_cflag |= CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;
	
	switch( nSpeed )
	{
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		break;
	case 460800:
		cfsetispeed(&newtio, B460800);
		cfsetospeed(&newtio, B460800);
		break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	}
	
	switch( nBits ){
	case 7:
		newtio.c_cflag |= CS7;
		break;
		
	case 8:
		newtio.c_cflag |= CS8;
		break;
		
	default:
		break;
	}
	
	switch( nEvent )
	{
	case 'O':
		newtio.c_cflag |= PARENB;//ʹ��У��λ
		newtio.c_cflag |= PARODD;//ʹ����У��λ
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E': 
		newtio.c_cflag |= PARENB;//ʹ��У��λ
		newtio.c_cflag &= ~PARODD;//ʹ��żУ��λ
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'N':  
		newtio.c_cflag &= ~PARENB;//ʧ��У��λ
		break;
	}
	
	if( nStop == 1 )
		newtio.c_cflag &= ~CSTOPB;
	else if( nStop == 2 )
		newtio.c_cflag |= CSTOPB;
		
	newtio.c_cc[VTIME]  = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(fd,TCIFLUSH);
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
	return 0;
}






