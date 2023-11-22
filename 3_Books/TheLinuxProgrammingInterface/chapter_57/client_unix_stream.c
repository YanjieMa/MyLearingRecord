#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>


int main(int argc, char ** argv)
{
	int sock_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if(sock_fd < 0){
		perror("socket error");
		exit(-1);
		/*
		fprintf(stderr,"Error: %s(errno:%d)\n",strerr(errno),errno);
		*/
	}
	char *path= "xyz";	
    struct sockaddr_un client_addr;
    memset(&client_addr,0,sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    snprintf(&client_addr.sun_path[1],sizeof(client_addr.sun_path)-1,"%s.client",path);

    int ret = bind(sock_fd,(struct sockaddr *)&client_addr,sizeof(client_addr));
    if(ret < 0){
        perror("bind error");
        exit(-1);
    }

//	if(unlink(client_addr.sun_path) < 0){
//		perror("unlink error");
//		return -1;
//	}
	struct sockaddr_un addr;
	memset(&addr,0,sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(&addr.sun_path[1], path, sizeof(addr.sun_path)-2);

	if(connect(sock_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un)) < 0){
		perror("connect error");	
		return -1;
	}


	printf("connecting success\n");

	char send_buf[1024];
    char recv_buf[1024];
	int n;
	while((n = read(STDIN_FILENO,send_buf,1024)) > 0){
		ret = send(sock_fd, send_buf, n, 0);
		if(ret != n){
			printf("write error\n");
		}
		memset(send_buf, 0, sizeof(send_buf));
        int recv_size = recv(sock_fd, recv_buf, sizeof(recv_buf), 0);
        write(STDOUT_FILENO, recv_buf, recv_size);
		memset(recv_buf,0,sizeof(recv_buf));
	}
	if(n < 0){
		perror("read error");
	}

	close(sock_fd);


	return 0;
}








