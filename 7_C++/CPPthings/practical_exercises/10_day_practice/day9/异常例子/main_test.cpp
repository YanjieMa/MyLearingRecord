#include <iostream>

using namespace std;

//test 10
#define MAX 3
class Full{
	int a;
public:
	Full(int i):a(i) {}
	int getValue(){
		return a;
	}
};
class Empty{
public:
	Empty(){
		cout << "empyt is" << endl;
	}
};

class Stack{
private:
	int s[MAX];
	int top;
public:
	Stack(){top = -1;}
	void push(int a){
		if(top >= MAX-1) throw Full(a);
		s[++top] = a;
	}
	int pop(){
		if(top < 0){
			throw Empty();
		}
		return s[top--];
	}
};

void test10()
{
	Stack s;

	try{
		s.push(10);
		s.push(20);
		s.pop();
		s.pop();
		s.pop();
		s.pop();
		s.pop();
		s.push(40);
	}
	catch(Full e){
		cout << "the value is "<< e.getValue() << endl;
	}
	catch(Empty){
		cout << "stack is empty" << endl;
	}
}





/*
//test 9
class BasicException{
public:
	char *where(){
		return "BasicException...";
	}
};
class FileSysException:public BasicException{
public:
	char *where(){
		return "FileSysException...";
	}
};
class FileNotFound:public FileSysException{
public:
	char *where(){
		return "FileNotFound...";
	}
};
class DiskNotFound:public FileSysException{
public:
	char *where(){
		return "DiskNotFound...";
	}
};


void test9()
{
	try{
		throw FileSysException();
	}
	catch(FileNotFound p) { cout << p.where() << endl;} //子类不能捕获父类抛出的异常
	catch(DiskNotFound p) { cout << p.where() << endl;}
	catch(BasicException p) { cout << p.where() << endl;}//父类可以捕获子类和本身抛出的异常
	//catch(FileSysException p) { cout << p.where() << endl;}
}
*/

//test 9-2
class BasicException{
public:
	virtual char *where(){
		return "BasicException...";
	}
};
class FileSysException:public BasicException{
public:
	virtual char *where(){
		return "FileSysException...";
	}
};
class FileNotFound:public FileSysException{
public:
	virtual char *where(){
		return "FileNotFound...";
	}
};
class DiskNotFound:public FileSysException{
public:
	virtual char *where(){
		return "DiskNotFound...";
	}
};

void test9_2(){
	try{
		DiskNotFound err;
		throw &err;
	}
	catch(BasicException *p){// 可以通过虚函数 catch 基类异常 ，获取所有继承类的异常
		cout << p->where() << endl;
	}


}


int main()
{
	test10();
	return 0;
}
