


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "condition.h"


int main()
{
	condition_t cd;
	if(condition_init(&cd) < 0){
		printf("init error\n");
		return 0;
	}
	printf("cond begin\n");

	struct timespec tm;
	//clock_gettime(CLOCK_REALTIME, &tm);
	tm.tv_sec = time(NULL) + 5;
	printf("time is %d\n", tm.tv_sec);
	condition_lock(&cd);
	int res = condition_timedwait(&cd, &tm);
	
	printf("cond end, res is %d\n",res);
	condition_destroy(&cd);
	return 0;
}
