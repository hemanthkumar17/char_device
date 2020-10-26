#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main ()
{
	char buffer[10];
	int n,fd;
	printf("Enter message length: ");
	scanf("%d",&n);
	fd=open ("/dev/simple_char_device",O_RDWR);
	printf("Enter message : ");
	scanf("%s",buffer);
	write(fd,buffer,n);
	read(fd,buffer,n);
	printf("%s\n",buffer);
	close(fd);
}
