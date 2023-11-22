#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>


#define PORT 9527
#define SERVER_IP "192.168.1.25"

int main(int argc, char ** argv)
{
	int ret;
	int sock_fd;	//监听套接字
	int com_fd;		//通信套接字

	struct sockaddr_in server_addr;	//服务器地址结构体
	struct sockaddr_in client_addr;	//客户端地址结构体
	socklen_t client_addr_len;		//客户端地址长度
	
	char client_ip[256];	//客户端ip地址 "172.0.0.1"
	
	char recv_buf[1024];
	char send_buf[1024];

	// 1.socket
	sock_fd = socket(AF_INET,SOCK_STREAM,0);	// int socket(int domain, int type, int protocol)
	if(sock_fd < 0){
		perror("socket failed");
		exit(-1);
	}	
	// 2.bind
	memset(&server_addr,0,sizeof(struct sockaddr_in));	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	//server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET,SERVER_IP,&server_addr.sin_addr.s_addr);	// int inet_pton(int af, const char *src, void *dst)
	//int inet_pton(int af, const char *src, void *dst);
	ret = bind(sock_fd,(struct sockaddr *)&server_addr,sizeof(server_addr)); // int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen)
	if(ret < 0){
		perror("bind failed");
		exit(-1);
	}	
	// 3.listen
	ret = listen(sock_fd,3); // int listen(int sockfd, int backlog)
	if(ret < 0){
		perror("listen error");
		exit(-1);
	}
	while(1){
		// 4.accept
		printf("waiting connect...\n");

		client_addr_len = sizeof(client_addr);
		int com_fd = accept(sock_fd,(struct sockaddr *)&client_addr,&client_addr_len);	// int accept(int sockfd, struct sockaddr *addr,socklen_t *addrlen) // addrlen是一个传入传出参数，attention!!!
		if(com_fd < 0){
			perror("accept failed");
			exit(-1);
		}
		// const char *inet_ntop(int af, const char *src, char *dst,socklen_t size);
		inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,client_ip,sizeof(client_ip));	// const char *inet_ntop(int af,const void *src, char *dst, socklen_t dst_size)
		printf("client addr:%s, port:%d\n",client_ip,ntohs(client_addr.sin_port));
		
		while(1){
			memset(recv_buf,0,sizeof(recv_buf));
			// 5.recv
			int size = recv(com_fd,recv_buf,sizeof(recv_buf),0);  // ssize_t recv(int sockfd, void *buf, size_t len, int flags)
			if(size == 0){
				printf("client closed\n");
				close(com_fd);
				break;
			}else if(size < 0){
				perror("recv error");	
				exit(-1);
			}else{
				write(STDOUT_FILENO,recv_buf,size);	// ssize_t write(int fd, const void *buf,size_t count)
				memset(send_buf,0,sizeof(recv_buf));
				// 6.send
//				strncpy(send_buf,"recv\n",sizeof(send_buf));
//				send(com_fd,send_buf,strlen(send_buf),0);	// ssize_t send(int sockfd, const void *buf, size_t len, int flags)
			}
		}
	}
	
	close(sock_fd);

	return 0;
}








