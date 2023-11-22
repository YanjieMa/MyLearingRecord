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
	const char *sock_path = argv[1];

	int sock_fd = socket(AF_UNIX,SOCK_DGRAM,0);
	if(sock_fd < 0){
		perror("socket error");
		exit(-1);
		/*
		fprintf(stderr,"Error: %s(errno:%d)\n",strerr(errno),errno);
		*/
	}
	
    struct sockaddr_un client_addr;
    memset(&client_addr,0,sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    snprintf(client_addr.sun_path,sizeof(client_addr.sun_path),"%s.1",argv[1]);

    int ret = bind(sock_fd,(struct sockaddr *)&client_addr,sizeof(client_addr));
    if(ret < 0){
        perror("bind error");
        exit(-1);
    }

	struct sockaddr_un addr;
	memset(&addr,0,sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path,sock_path,sizeof(addr.sun_path)-1);

	printf("connecting...\n");

	char send_buf[1024];
    char recv_buf[1024];
	int n;
	while((n = read(STDIN_FILENO,send_buf,1024)) > 0){
		ret = sendto(sock_fd,send_buf,n,0,(struct sockaddr *)&addr,sizeof(struct sockaddr_un));
		if(ret != n){
			printf("write error\n");
		}
        int recv_size = recvfrom(sock_fd,recv_buf,sizeof(recv_buf),0,NULL,NULL);
        write(STDOUT_FILENO,recv_buf,recv_size);
	}
	if(n < 0){
		perror("read error");
	}

	close(sock_fd);


	return 0;
}







