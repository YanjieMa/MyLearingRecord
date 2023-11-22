#include <iostream>
#include <cstring>

using namespace std;


// 函数异常可以抛出然后由主函数处理

void func(int x)
{
	try{
		if(x == 0){
			throw "except";
		}
	}catch(...){
		cout << "throw" << endl;
		throw 1;
	}	
}

int main()
{

	try{
		func(0);
	}catch(int n){
		cout << "value is "<< n <<endl;
	}

	return 0;
}
