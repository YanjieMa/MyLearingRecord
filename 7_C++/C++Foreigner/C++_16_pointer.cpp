#include <iostream>

#define print(X) std::cout << (X) << std::endl;

int main()
{
	int val = 8;
	void *ptr = &val;
	print(ptr);
	
	void **pp = &ptr;
	print(pp);
	

	print((int *)*pp);
	return 0;
}
