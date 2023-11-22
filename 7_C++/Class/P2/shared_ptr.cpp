#include <iostream>



template <class T>
class shared_ptr{
public:

	shared_ptr(T *p) : sp(p) {}

	T& operator*(){
		return (*sp);	
	}

	T* operator->(){ //解释： 箭头符合作用下去的结果 会 继续作用下去
		return sp;
	}


private:
	T* sp;
	long * lp;

};

template <class T>
class Iterator{
public:

private:



};
