/*

	open a device and receive data.

	Author: Jianfeng Xie & Qiushi Wang

	Date: April 6th, 2011

*/


#include "read.h"

unsigned char init_read(char *dev){

	FILE *fp;

	if((fp = fopen(dev, "w+")) == NULL)
	{
		return 0;
	}

	printf("usb reader initialized\n");

	return 1;
}





void read_dev(char *dev){

	FILE *fp;
   
	int letter;

	int i;

	unsigned char line [100];

	if((fp = fopen(dev, "r+")) == NULL)
	{
		puts("Cannot oepn the file");
		exit(0);
	}
	
	i = 0;
	
	while(1){
	
	letter = fgetc(fp);

	//printf("%d ",letter);	

	if(letter != -1)	
	line [i] = letter;
	
	i++;	

	if(letter == 10)
	{	
	line [i] = '\0';	
	printf("%s",line);
	i = 0;
	break;
	}

	usleep(1000);	
	}

	fclose(fp);
}





void init_serial()
{
	system("stty -F /dev/ttyUSB1 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
}





int main(void){

	printf("processing...\n");

	init_serial(MEGA1);

	sleep(6);
	init_read(MEGA1);

	while(1)
	read_dev(MEGA1);			

	return 0;
}
