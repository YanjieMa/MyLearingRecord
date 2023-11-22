
#include <errno.h>

#define SERVER_PORT 9999
#define MAX_EVENTS 20
#define LISNUM 10




struct my_event{
	int fd;
	int events;
	void *arg;
	void (*call_back)(int fd, int events, void *arg);
	int status;
	long last_active_time;
};

struct my_event g_events[MAX_EVENTS + 1]; //最后一个用于 listen
threadpool_t pool;
int g_efd;


void eventset(struct my_event *ev, int fd, void (*call_back)(int, int, void *), void *arg)
{
	ev->fd = fd;
	ev->events = 0;
	ev->arg = arg;
	ev->call_back = call_back;
	ev->status = 0;
	ev->last_active_time = time(NULL);
}

void eventadd(int efd, int events, struct my_event *ev)
{
	struct epoll_event epv = {0, {0}};
	int op;

	epv.data.ptr = ev;
	epv.events = ev->events = events;

	if(ev->status == 1){
		op = EPOLL_CTL_MOD;
	}else{
		op = EPOLL_CTL_ADD;
		ev->status = 1;
	}

	if(epoll_ctl(g_efd, op, ev->fd, &epv) < 0){
		printf("event add failed! ")
	}else{
		printf("event add ok! fd:%d, event:%d\n",ev->fd, events);
	}
}


void eventdel(int efd, struct my_event *ev)
{
	struct epoll_event epv = {0, {0}};
	
	if(ev->status != 1){
		return ;
	}

	epv.data.ptr = ev;
	epv.events = EPOLL_CTL_DEL;
	ev->status = 0;
	epoll_ctl(g_efd, EPOLL_CTL_DEL, ev->fd, &epv)
}

int MyRecv(int sfd, char *buf, size_t len){
	int read_len = 0;
	unsigned int total_read = 0;
	
	if(len < 0){
		return 0;
	}
	while(total_read < len){
		do{
			read_len = read(sfd, buf,len-read_len, 0);	
		}while(read_len < 0 && errno == EINTR);
		if(read_len < =){
			return total_read;
		}
		total_read += read_len;
		buf += read_len;
	}
	return total_read;
}



void recvdata(int fd, int events, void *arg)
{
	char *type = new char[4];
	int read_len;
	struct my_event *ev = (struct my_event *)arg;

	printf("recv data is: %d\n",fd);
	read_len = MyRecv(fd,type,sizeof(int));
	int itype;
	memcpy(&itype,type,sizeof(int));
	itype = htonl(itype);
	if(itype == 0){
		eventdel(g_efd,ev);
		threadpool_add_task(&pool, recvfile, arg);
	}else if(itype == 1){
		eventdel(g_efd, ev);
		threadpool_add_task(&pool,readfilefromlocal, arg);
	}

	delete [] type;
}


void acceptconn(int lfd, int events, void *arg)
{
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);

	int acceptfd,i;

	if((acceptfd = accept(lfd, (struct sockaddr *)&client_addr), &client_addr_len) < 0){
		perror("accept error");
		return;
	}else{
		printf("accept a new client: %s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	}

	do{
		for(i=0; i < MAX_EVENTS; i++){
			if(g_events[i].status == 0){
				break;
			}
		}
		if(i == MAX_EVENTS){
			printf("can not accept more client!\n");
		}
		
		int flag = 0;
		if((flag = fcntl(acceptfd,F_SETFL, O_NONBLOCK)) < 0){
			printf("fcntl set non block failed: %s\n", strerror(errno));
		}

		eventset(&g_events[i],acceptfd,recvdata,&g_events[i]);

		eventadd(g_efd,EPOLLIN,&g_events[i]);
	}while(0)
		
}




int mian(int argc, char **argv)
{
	unsigned short port = SERVER_PORT;

	if(argc >= 2){
		port = atoi(argv[1]);
	}
	// 1.创建epoll对象
	g_efd = epoll_create(MAX_EVENTS + 1);
	if(g_efd < 0){
		printf("create efd error:%s\n",strerror(errno));
	}else{
		printf("g_efd: %d\n",g_efd);
	}
	
	// 2.创建socket 连接套接字 listenfd
	int lfd;
	lfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("lfd is %d\n",lfd);
	
	// 设置listenfd非阻塞
	fcntl(lfd,F_SETFL,O_NONBLOCK);

	// 设置端口在TIME_WAIT状态下可以重用
	int reuse = 1;
	setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,(const void *)&reuse,sizeof(reuse));

	// 设置server addr结构
	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// 3.bind
	if(bind(lfd, (struct sockaddr *)&server_addr), sizeof(server_addr) < 0){
		perror("bind error");
	}else{
		printf("bind ok!\n");
	}
	// 4.listen
	if(listen(lfd,LISNUM) < 0){
		perror("listen error");
	}else{
		perror("listen ok!\n");
	}
	
	//5.添加监听的事件
	eventset(&g_events[MAX_EVENTS], lfd, acceptconn, &g_events[MAX_EVENTS]);
	eventadd(g_efd, EPOLLIN, &g_events[MAX_EVENTS]);

	return 0;
}

