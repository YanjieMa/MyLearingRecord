#include <stdio.h>
#include <string.h>
#include <unistd.h>



int main(int argc, char **argv)
{

	int i=0;
//	while(argv[i] != NULL){
	while(i<10){
		printf("argv %d is %s\n", i, argv[i]);
		sleep(3);		
		i++;
		char *x = 0x7fffffff1234;
		printf("x --> is:%s\n", *x);
	}

}
