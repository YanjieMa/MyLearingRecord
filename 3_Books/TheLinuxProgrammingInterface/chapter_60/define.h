
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <time.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>



int mysend(int sockfd, char *buf, size_t len)
{
	unsigned int sended = 0;//已经发送的数据
	int thissended;//本次发送的数据
	
	if(len <= 0){
		return sended;
	}

	while(sended < len){
		do{
			thissended = send(sockfd, buf, len-sended, 0);
		}while(thissended < 0 && errno == EINTR);//发送时遇到终端 重新发送
		if(thissended < 0){
			return sended;
		}
		sended += thissended;
		buf += thissended;
	}

	return len;
}

int myrecv(int sockfd, char *buf, size_t len)
{


}
