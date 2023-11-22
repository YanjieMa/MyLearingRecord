#include "threadpool.h"
#include <stdio.h>
#include <unistd.h>

threadpool_t pool;



void  task_handler(void *args){

	int * p = (int *)args;
	printf("task %d begin\n", *p);
	sleep(3);
	printf("task %d end\n", *p);
		

}


int main()
{
	int para[7] = {0};
	threadpool_init(&pool,5);

	for(int i=0; i< 7; i++){
		para[i] = i;
		threadpool_add_task(&pool,task_handler,(void *)&para[i]);
	}

	sleep(20);

	printf("结束线程池\n");
	threadpool_destroy(&pool);


	return 0;	

}
