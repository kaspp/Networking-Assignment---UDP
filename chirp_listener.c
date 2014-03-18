/*
NAME: 			ONG MING THYE, DERRICK
SIT MATRIC NO:		13AGC039H
GUID:			2110010O
SUBMISSION DATE:	14 MAR 2014
DEADLINE:		14 MAR 2014
STARTED DATE:		12 MAR 2014
DOCUMENT NAME:		CHIRP.C
ASSIGNMENT NAME:	NS3 SUMMATIVE EXERCISE 2
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define HOST 15
#define MESSAGE 2000
#define REPLY 2000
#define BUFFER 999
#define PORT 5010


int main() {
    
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in address;
	struct tm *info;
	struct ip_mreq  ipmreq;
	socklen_t slen = sizeof(address);
	time_t getTime;
	char timestamp[80];
	unsigned int i;
	
	char *h = NULL, *msg = NULL,*buf = NULL, *r = NULL;
    
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_family = AF_INET; 
	address.sin_port = htons(PORT); 
    
	if (fd == -1) {
		// an error occurred
		printf("Socket Cannot Be Created \n");
		return 1;
	} else { //
		printf("Socket Created\n");
	}
	
	if (bind(fd,(struct sockaddr *)&address,(int) slen) == -1)
	{
		perror("Error Binding");
		return 1;
	}
    
	inet_pton(AF_INET, "224.0.0.22", &(ipmreq.imr_multiaddr.s_addr));
	ipmreq.imr_interface.s_addr = INADDR_ANY;
	if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &ipmreq, sizeof(ipmreq)) < 0) {
		printf("Fail to Join\n");
		return 1;
	}
    
	while (1) {
		h = malloc(HOST);
		msg = malloc(MESSAGE);
		buf = malloc(BUFFER);
		r = malloc(REPLY);
		if (recvfrom(fd, buf, 1000, 0, (struct sockaddr *)&address, &slen) < 0) {
			printf("Received Failed\n");
			return 1;
		}
		if (strcmp(buf, "FROM ") ==0) {
			printf("Message not start with FROM format.\n");
			return 1;
		}else {
			//buffer+=5;
			h=strtok(buf,"\n");
			msg=strtok(NULL,"\n");
			if (h ==NULL){
				printf(" Unknown HOSTNAME! \n");
				continue;
			}
			if (msg==NULL){
				printf("There is no message. \n");
				continue;
			}
		}
		
		if (sizeof(buf)>BUFFER){
			printf("Excceded Maximum Length 1000\n");
			return 1;
		}
		
		for (i=0; i<strlen(msg);i++){
			if (isprint(msg[(unsigned char)i])==0){
				msg[i]='?';
			}
		}
		
        for (i=0; i<strlen(h);i++){
			if (isprint(h[(unsigned char)i])==0){
				h[i]='?';
			}
		}
        
		time( &getTime );
		info=localtime(&getTime);
		strftime(timestamp,80,"%d-%m-%Y %H:%M:%S - ", info);
		strcpy(r,timestamp);
		strcat(r,h);
		strcat(r," - ");
		strcat(r,msg);
		printf("%s\n", r);
	}

	free(msg);
	free(h);
	free(buf);
	free(r);

	if (setsockopt(fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &ipmreq, sizeof(ipmreq)) < 0) {
		printf("Unable to leave room!\n");
		return 1;
	}
	
	close (fd);
	return 0;
}
