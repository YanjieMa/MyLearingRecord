#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <ctype.h>

int main (int argc, char **argv)
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
	
	if(remove(sock_path) == -1 && errno != ENOENT){
		perror("remove error");
		exit(-1);
	}

	struct sockaddr_un addr;
	memset(&addr,0,sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path,sock_path,sizeof(addr.sun_path)-1);
	//保证sun_path的最后一盒字节是NULL
	int ret = bind(sock_fd,(struct sockaddr *)&addr,sizeof(struct sockaddr_un));
	if(ret < 0){
		perror("bind error");
		exit(-1);
	}

	char recv_buf[1024];
    char send_buf[1024];
	struct sockaddr_un client_addr;
	socklen_t client_addr_len;
	client_addr_len = sizeof(struct sockaddr_un);

    while(1){
        int size = recvfrom(sock_fd,recv_buf,sizeof(recv_buf),0,(struct sockaddr *)&client_addr,&client_addr_len);
        fprintf(stdout,"client addr:%s\n",client_addr.sun_path);
        write(STDOUT_FILENO,recv_buf,size);
        memset(send_buf,0,sizeof(send_buf));
        for(int i=0; i<size; i++){
            send_buf[i] = toupper(recv_buf[i]);
        }
        sendto(sock_fd,send_buf,size,0,(struct sockaddr *)&client_addr,client_addr_len);
    }


    close(sock_fd);

    return 0;
}
