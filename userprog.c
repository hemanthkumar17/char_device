#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main ()
{
	char buffer[3];
	char ibuffer[3];
	int fd;
	fd=open ("/dev/simple_char_device",O_RDWR);
	//printf("%d",fd);
	buffer[0]='a';
	buffer[1]='b';
	buffer[2]='c';
	write(fd,buffer,3);
	read(fd,ibuffer,3);
	printf("%s",ibuffer);
	//printf("Value : 0x %02x\n",buffer[0]);
	close(fd);
}
