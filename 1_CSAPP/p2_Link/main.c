#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int myadd(int x, int y);

int global = 0x11223344;
int global_0 = 0;

int main()
{
	static int ret = 0;
	static int sum1 = 0x20;
	int sum2 = 0x30;
	ret = myadd(sum1, sum2);	
	ret = ret + global;
	printf("hello world, %d\n",ret);
	return 0;
}
