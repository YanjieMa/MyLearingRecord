#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>


#define PORT 9527
#define IP	 "192.168.1.25"

int main(int argc, char **argv)
{
	int sock_fd;
	struct sockaddr_in6  server_addr;
	char send_buf[1024];
	char recv_buf[1024];
	sock_fd = socket(AF_INET6,SOCK_DGRAM,0);

	memset(&server_addr,0,sizeof(struct sockaddr_in6));
	server_addr.sin6_family = AF_INET6;
	server_addr.sin6_port = htons(PORT);
	inet_pton(AF_INET6,IP,&server_addr.sin6_addr);

	while(1){
		memset(send_buf,0,sizeof(send_buf));
		memset(recv_buf,0,sizeof(send_buf));
		gets(send_buf);
		send_buf[strlen(send_buf)] = '\n';
		sendto(sock_fd,send_buf,strlen(send_buf),0,(struct sockaddr *)&server_addr,sizeof(struct sockaddr_in6));

		recvfrom(sock_fd,recv_buf,sizeof(recv_buf),0,NULL,NULL);
		printf("recv:%s",recv_buf);
	}
	close(sock_fd);

	return 0;
}
