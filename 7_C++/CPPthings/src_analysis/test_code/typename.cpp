#include <iostream>

using namespace std;

/* typename */
template <typename T>
int compare(const T &a, const T &b)
{
	return a>b ? a:b;
}

template <typename T>
void foo()
{
	typename T::iterator *iter; //告诉编译器 T::iterator 是类型，而不是变量
}


int main()
{

	return 0;
}
