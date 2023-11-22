#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


int func(int arg)
{
	printf("child is runing...\n");
	printf("para is %d\n",arg);
	return arg;
}




int main(int argc, char **argv)
{
	int arg;

	printf("main begin...\n");

	pid_t pid;

	arg = 1;

	pid = vfork();
	if(pid < 0){
		perror("fork error\n");
	}else if(pid == 0){
		_exit(func(arg));
	}
	
	printf("parent is runing...\n");
	int status = 0;
	if(wait(&status) < 0){
		perror("wait error\n");
	}

	printf("func return value is %d\n",status);
	return 0;
}
