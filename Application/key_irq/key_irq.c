#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>



int main(int argc,char *argv[])
{
   
	int fd = open("/dev/button_irq",O_RDWR|O_NDELAY); //路径和驱动设备节点名字保持一致
	int value = 0;
	char buffer;
	if(fd < 0){
	 perror("open failed\n");
 	 exit(0);
	}
	printf("asdf*********");
    printf("button read test!\n");
	printf("asdf*********");
	while(1)
	{
	 printf("**********");
	 read(fd,&buffer,sizeof(buffer));	
	 printf("button value id:%d\n",buffer);
	 sleep(1);
	}
	close(fd);
    return 0;	
}