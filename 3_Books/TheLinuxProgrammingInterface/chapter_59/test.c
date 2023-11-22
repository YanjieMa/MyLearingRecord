#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	struct addrinfo hints;
	struct addrinfo *result;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;	//TCP套接字
	hints.ai_family = AF_UNSPEC;		//支持IPv4 and IPv6
	hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
	
	/*
 *	1. 函数原型 int getaddrinfo(const char * host, const char * service, const struct addrinfo * hints, strict addrinfo **res);
 *	host: 主机名或者IP地址， www.example.com  172.32.10.32,;  NULL 则表示本地主机
 *	service： 服务名或者端口号的字符串;
 *	hints: 指定一些筛选条件， 无条件则可以为NULL
 *	res: 存储返回的结构体链表
 * */
	if(getaddrinfo("www.example.com", NULL, &hints, &result) != 0){
		perror("get addr info error");
		return -1;
	}
	struct addrinfo *rp;
	for(rp = result; rp != NULL; rp = rp->ai_next){
		struct sockaddr_in *addr;
		char p[1024];
		addr = (struct sockaddr_in *)rp->ai_addr;
		inet_ntop(rp->ai_family, &addr->sin_addr, p, 1024);
		printf("addr is %s\n", p);	
		printf("port is %d\n", ntohs(addr->sin_port));
		printf("ai_family is %d\n", rp->ai_family);	

		
	}

	return 0;
}
