#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER 999

int main(int argc, char* argv[]) {
    
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	char buf[BUFFER];
	struct sockaddr_in address;
	char *host=getlogin();
	address.sin_family = AF_INET;
	address.sin_port = htons(5010);
	address.sin_addr.s_addr = inet_addr("224.0.0.22");
	
	strcpy(buf, "FROM ");
	strcat(buf, host);
	strcat(buf, "\n");
    
	if (fd == -1) {
		// an error occurred
		printf("Socket created unsuccessfully \n");
		return 1;
	} else { //
		printf("Socket created successfully \n");
	}
    
	if (host == NULL) {
		printf("host cannot be found");
		return 1;
	} else {
		if(sizeof(host) <= 16)
		{
			printf("This is the login info: %s \n", host);
		}
		else
		{
			printf("Your hostname has exceed the size of 16\n");
			exit(0);
		}
	}
    
	if (argc > 1) {
        printf("argv[1] = %s\n", argv[1]);
        strcat(buf,argv[1]);
        strcat(buf,"\n");
        strcat(buf,"\0");
        
    } else {
		printf("Usage: ./chirp \"Message\"\n");
		return 1;
	}
    /*
	if (sizeof(buf)>999){
		printf("Exceeded maximum length of 1000\n");
		return 1;
		//exit(0);
	}
    */
	printf("buffer = %s\n", buf);
	    	if (sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *) &address, sizeof(address)) < 0) {
        	perror("unable to send the message to the group");
		}
	
        return 1;
    
    
    
	close(fd);
	return 0;
}
