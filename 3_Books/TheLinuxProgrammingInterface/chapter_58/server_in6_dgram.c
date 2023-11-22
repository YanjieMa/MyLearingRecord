#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORT 9527
#define IP	 "192.168.1.25"

int main(int argc, char ** argv)
{
	int sock_fd;
	struct sockaddr_in6 server_addr,client_addr;
	socklen_t client_addr_len;
	char recv_buf[1024];
	char send_buf[1024];
	char client_ip[256];

	client_addr_len = sizeof(struct sockaddr_in6);

	sock_fd = socket(AF_INET6,SOCK_DGRAM,0);

	memset(&server_addr,0,sizeof(struct sockaddr_in6));
	memset(&client_addr,0,sizeof(struct sockaddr_in6));
	server_addr.sin6_family = AF_INET6;
	server_addr.sin6_addr = in6addr_any;
	server_addr.sin6_port = htons(PORT);

	bind(sock_fd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr_in6));
	
	fprintf(stdout,"step %d: init sucess\n",1);
	while(1){
		memset(client_ip,0,sizeof(client_ip));
		memset(recv_buf,0,sizeof(recv_buf));
		int size = 	recvfrom(sock_fd,recv_buf,sizeof(recv_buf),0,(struct sockaddr *)&client_addr,&client_addr_len);
		inet_ntop(AF_INET6,&client_addr.sin6_addr,client_ip,256);
		printf("clinet ip:%s, port:%d, msg:%s",client_ip,ntohs(client_addr.sin6_port),recv_buf);
		memset(send_buf,0,sizeof(send_buf));
		for(int j=0; j<size; j++){
			send_buf[j] = toupper(recv_buf[j]);
		}
		sendto(sock_fd,send_buf,size,0,(struct sockaddr *)&client_addr,client_addr_len);

	}

	close(sock_fd);
	return 0;
}
