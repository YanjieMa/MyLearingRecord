#include <stdio.h>


int main(int argc, char ** argv)
{
	struct sockaddr_sotrage client_addr;
	int addrlen = sizeof(struct sockaddr_storage);

	struct addrinfo hints;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_conanname = NULL:
	hints.ai_addr = NULL;
	hints.ai_next = NULL:
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE | AI_UNMERICSERV;

	struct addrinfo &result;
	getaddrinfo(NULL,"10001",&hints,&result);

	int optval = 1;
	int listenfd,comfd;
	struct addrinfo *rp;
	for(rp = result; rp != NULL; rp = rp->ai_next){
		listenfd = socket(rp->ai_family,rp->socktype,rp->ai_protocol);
		setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&optval.sizeof(optval));
		bind(listenfd,rp->ai_addr,rp->ai_addrlen);
		listen(listenfd,10);
		freeaddrinfo(result);
		while(1){
			comfd = accept(listenfd,(struct sockaddr *)&client_addr,&addrlen);
		}
	}








	return 0;
}
