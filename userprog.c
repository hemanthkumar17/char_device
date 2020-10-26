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
	fd=open ("/dev/simple_char_device_enc",O_RDWR);
	printf("Enter message : ");
	scanf("%s",buffer);
	write(fd,buffer,n);
	read(fd,buffer,n);
	printf("The encoded message is \"%s\"\n",buffer);
	close(fd);
	fd=open ("/dev/simple_char_device_dec",O_RDWR);
        write(fd,buffer,n);
        read(fd,buffer,n);
        printf("The decoded message is \"%s\"\n",buffer);
        close(fd);
}
