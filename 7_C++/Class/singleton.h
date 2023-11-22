#include <string.h>



class A{

public:
	static A& getInstance();

	void work();

private:
	A();

}

A& A::getInstance(){
	static A value;
	return value;
}

