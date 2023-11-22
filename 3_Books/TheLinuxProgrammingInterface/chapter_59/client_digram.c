#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv)
{
	struct sockaddr_in servaddr, clieaddr;
	int clieaddrlen = sizeof(struct sockaddr_in);
	int sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd < 0){
		perror("socket error");
		return -1;
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	//servaddr.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET,"172.25.52.9",&servaddr.sin_addr);
	servaddr.sin_port = htons(9527);
	
//	if(bind(sfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in)) < 0){
//		perror("bind error");
//		return -1;
//	}

	int readlen = 0;
	char readbuf[5];
	char claddrstr[16];
	while((readlen = read(0, readbuf, sizeof(readbuf))) > 0){

		if(sendto(sfd, readbuf, readlen, 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in)) != readlen){
			perror("sendto error");
			break;
		}
		readlen = recvfrom(sfd, readbuf, sizeof(readbuf), 0, (struct sockaddr *)&clieaddr, &clieaddrlen);
		if(readlen < 0){
			perror("recvfrom error");
			break;
		}
		if(!(inet_ntop(AF_INET, &clieaddr.sin_addr, claddrstr, 16))){
			perror("inet_ntop error");
			break;
		}
		printf("recv from %s:%s\n", claddrstr, readbuf);
	
		memset(readbuf,0,sizeof(readbuf));	
	}
	close(sfd);


	return 0;
}
