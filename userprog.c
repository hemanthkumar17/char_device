#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	// To store the message to be encrypted and decrypted
	char buffer[100];
	//fd -> File Descriptor    n-> Length of the message
	int fd,n=0;
	
	printf("Enter message : ");
	scanf("%s",buffer);
	while(buffer[n++] != '\0');
	n--;
	
	fd=open("/dev/enc_device",O_RDWR);
	if(fd<0){
		printf("Cannot open Encryption char device file\n");
		return 0;
	}
	//Write to device
	write(fd,buffer,n);
	// Read from device to user
	read(fd,buffer,n);
	printf("The encoded message is \"%s\"\n",buffer);
	close(fd);
	
	
	fd=open ("/dev/dec_device",O_RDWR);
	if(fd<0){
		printf("Cannot open Decryption char device file\n");
		return 0;
	}
	//Write to device
        write(fd,buffer,n);
        
        //Read from device to user
        read(fd,buffer,n);
        
        printf("The decoded message is \"%s\"\n",buffer);
        close(fd);
}
