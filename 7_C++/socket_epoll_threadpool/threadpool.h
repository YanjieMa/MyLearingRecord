#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "condition.h"
typedef struct task {
	void (*run)(void *args);
	void * args;
	struct task *next;
}task_t;


typedef struct thread {
	pthread_t tid;
	int status;
}thread_t;

typedef struct threadpool{
	pthread_mutex_t tmutex;
	pthread_cond_t tcond;
	task_t *first;
	task_t *last;
	thread_t *threads;
	int count;
	int idle;
	int max_threads;
	int close_flag;
}threadpool_t;


void threadpool_init(threadpool *pool, int threads);
void threadpool_add_task(threadpool_t *pool,void (*run)(void *args),void *args);
void threadpool_destroy(threadpool_t *pool);



#endif
