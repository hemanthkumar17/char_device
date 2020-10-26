#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main ()
{
	char buffer [1];
	int fd;
	fd=open ("/dev/simple_char_device",O_RDWR);
	printf("%d",fd);
	buffer[0]=1;
	write(fd,buffer,1);
	read(fd,buffer,1);
	printf("Value : 0x %02x\n",buffer[0]);
	close(fd);
}
