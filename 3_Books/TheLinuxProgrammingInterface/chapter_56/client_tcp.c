#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <ctype.h>
#include <arpa/inet.h>

#define SERVER_PORT 9527
#define SERVER_IP "192.168.1.25"

int main(int argc, char ** argv)
{
	char send_buf[1024];
	struct sockaddr_in server_addr;

	memset(&server_addr,0,sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET,SERVER_IP,&server_addr.sin_addr.s_addr);	// int inet_pton(int af, const char *src, void *dst)
	
	int tcp_com_fd;
	tcp_com_fd = socket(AF_INET,SOCK_STREAM,0);
	if(tcp_com_fd < 0){
		perror("socket error");
		exit(-1);
	}

	int ret = 0;
	ret = connect(tcp_com_fd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr));  // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
	if(ret < 0){
		perror("connect error");
		exit(-1);
	}
	while(1){	
		memset(send_buf,0,sizeof(send_buf));
		printf("input:");
		int size = read(STDIN_FILENO, send_buf, sizeof(send_buf));	//ssize_t read(int fd, void *buf, size_t count)
		//send_buf[strlen(send_buf)] = '\n';
		int n = send(tcp_com_fd,send_buf,size, 0); 
		if(n < 0){
			perror("send error");
		}
	}

	close(tcp_com_fd);

	return 0;
}


