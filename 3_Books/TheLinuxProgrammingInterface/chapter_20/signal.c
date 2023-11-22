


#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

typedef	void (*signalhandler_t)(int);

void sigint(int sig){
	printf("recv signal %d\n",sig);
	sleep(5);
	printf("sigint handler finish\n");

}

void sigquit(int sig){

	printf("recv signal %d\n",sig);
	sleep(5);
	printf("sigquit handler finish\n");
}


int main()
{

	signalhandler_t oldhandler;

	printf("sigint si %s\n",strsignal(10000));


	oldhandler = signal(SIGINT,sigint);
	oldhandler = signal(SIGQUIT,sigquit);
	printf("old sig handler addr is %x\n",oldhandler);
	for(int i=0; i<5; i++){
		sleep(1);
		printf("main i is %d\n",i);
	}


	return 0;
}
