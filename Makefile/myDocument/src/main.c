#include <stdio.h>
#include <unistd.h>


#include "add.h"
#include "minus.h"

int main(int argc, char **argv)
{

	int a=10, b=20;
	int c = 0;

	c= add(a, b);
	printf("a+b=%d\n",c);

	c = minus(a,b);
	printf("a-b=%d\n",c);

	return 0;
}
