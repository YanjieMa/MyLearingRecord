#include <stdio.h>
#include <assert.h>
#include "add.h"

int addend = 1;

int main(int argc, char **argv)
{
	int zr=0, res;

	res = add(&zr);
	assert(res == 0);
	assert(res == 1);
	return 0;
}
