#include "add.h"

int add(int *pz)
{
	if(pz){
		*pz = (int)pz;
		return 0;
	}else{
		return -1;
	}
}
