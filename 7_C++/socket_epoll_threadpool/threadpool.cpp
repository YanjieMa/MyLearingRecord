#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include "threadpool.h"

void *thread_routine(void *args)
{
	struct timespec abstime;
	int timeout;

	threadpool_t *pool = (threadpool_t *) args;
	printf("thread %d is starting, pool size: %d\n",(int)pthread_self(),pool->count);

	while(1){
		timeout = 0;
		condition_lock(&pool->ready);
		pool->idle++;
		while(pool->first==NULL && !pool->close_flag){
			clock_gettime(CLOCK_REALTIME,&abstime);
			abstime.tv_sec += 10;
			int status;
			status = condition_timewait(&pool->ready,&abstime);
			if(status == ETIMEDOUT){
				printf("thread %d wait timeout\n",(int)pthread_self());
				timeout = 1;
				break;
			}
		}	
		pool->idle--;
		
		if(pool->first != NULL){
			task_t *task = pool->first;
			pool->first = task->next;
			condition_unlock(&pool->ready);
			task->run(task->args);
			free(task);
			condition_lock(&pool->ready);
		}	
		if(pool->close_flag && pool->first == NULL){
			pool->count--;
			if(pool->count == 0){
				condition_signal(&pool->ready);
			}
			condition_unlock(&pool->ready);
			break;
		}
		if(timeout == 1){
			pool->count--;
			condition_unlock(&pool->ready);
			break;
		}
		
		condition_unlock(&pool->ready);
	}
	printf("thread %d exit\n", (int)pthread_self());
	return NULL;
}



void threadpool_init(threadpool_t *pool, int max_threads)
{
	condition_init(&pool->ready);
	pool->first = NULL;
	pool->last = NULL;
	pool->count = 0;
	pool->idle = 0;
	pool->max_threads = max_threads;
	pool->close_flag = 0;
}


void threadpool_add_task(threadpool_t *pool, void (*run)(void *args), void *args)
{
	task_t *newtask = (task_t *)malloc(sizeof(task_t));
	newtask->run = run;
	newtask->args = args;
	newtask->next = NULL;

	condition_lock(&pool->ready);
	if(pool->first == NULL){
		pool->first = newtask;
	}else{
		pool->last->next = newtask;
	}
	pool->last = newtask;

	if(pool->idle > 0){
		condition_signal(&pool->ready);
	}else if(pool->count < pool->max_threads){
		pthread_t tid;
		pthread_create(&tid,NULL,thread_routine,pool);
		pool->count++;
	}else{
		printf("新的任务已经没有空闲线程执行了,等待\n");
	}
	condition_unlock(&pool->ready);
}

void threadpool_destroy(threadpool_t * pool){
	if(pool->close_flag){
		return;
	}

	condition_lock(&pool->ready);
	pool->close_flag = 1;
	if(pool->count > 0){
		if(pool->idle > 0){
			condition_broadcast(&pool->ready);
		}
		while(pool->count > 0){
			condition_wait(&pool->ready);
		}
	}
	condition_unlock(&pool->ready);
	condition_destroy(&pool->ready);		
}
