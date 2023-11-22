
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	for(int i=0; i<argc; i++){
		printf("argc[%d] is %s\n",i,argv[i]);
	}
	char buf[1024];
	while(1){
		int len = read(fileno(stdin),buf,1024);

		printf("this recv %s\n",buf);
		if(len=0) break;
		bzero(buf,sizeof(buf));
	}
	printf("recv %s\n",buf);
	return 0;
}
