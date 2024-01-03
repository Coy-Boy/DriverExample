#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>



int main(int argc,char *argv[])
{
   
	int fd = open("/dev/leds",O_RDWR); //路径和驱动设备节点名字保持一致
	int value = 0;
	if(fd < 0){
	 perror("open failed");
 	 exit(0);
	}
    
	
	read(fd,&value,4);
	
	printf("__USER__ value : %d\n",value);

	//重新给value赋值
    	value = 666;
   
	write(fd,&value,4);
	
	while(1)
	{
		value = 0;
		write(fd,&value,4);
		sleep(1);
		value = 1;
		write(fd,&value,4);
		sleep(1);	
	}
	close(fd);
    return 0;	
}
