#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>

#define SYNC_SIG SIGCHLD

void handler()
{
	printf("hhhhhhhh\n");
}

void test_fork()
{

	sigset_t block_mask, orig_mask, empty_mask;
	struct sigaction sa;

	sigemptyset(&block_mask);
	sigaddset(&block_mask,SYNC_SIG);
	if(sigprocmask(SIG_BLOCK,&block_mask,&orig_mask) < 0){
		printf("func %s error\n",__func__);
		exit(1);
	}

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;
	sigaction(SYNC_SIG, &sa, NULL);


	pid_t pid;
	pid = fork();
	if(pid > 0){
		printf("i am parent pid\n");

		sigemptyset(&empty_mask);
		sigsuspend(&empty_mask);
		sigprocmask(SIG_SETMASK,&orig_mask,NULL);
		printf("go on...\n");
		int status = 0;
		wait(&status);
		printf("pid(%d), exit %d\n",getpid(),status);
	}else if(pid == 0){
		printf("i am child pid\n");
		sleep(1);
		kill(55, getppid());
		sleep(2);
		printf("child end\n");
		exit(-1);
	}
}


int main()
{
	
	test_fork();
	
	return 0;
}



