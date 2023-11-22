#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <cstring>
using namespace std;

// string --> num

// C语言风格
void str2int_c()
{
	cout << "atoi" << endl;
	//在遇到非数字型的非法字符终止
	string str = "123str456";
	int val = atoi(str.c_str());
	const char *p = str.c_str();
	cout << p << endl;
	cout << val << endl;

	cout << "strtol" << endl;
	// 相比之下 支持多种进制转换
	int v = strtol(str.c_str(), NULL, 10);
	cout << v << endl;
}

// C++语言风格
void str2int_cpp()
{
	// stoi 不能转换时，会抛出异常 
	try{
	string str1 = "aaa123,asd456";
	int val1 = stoi(str1);
	cout << val1 << endl;
	}catch(...){
		cout << "catch(...)" << endl;
	}
}

// 自己动手
double my_str2int(const string &str)
{
	double ret;
	stringstream ss;
	ss << str;
	ss >> ret;
	return ret;
}

string my_int2str(double val)
{
	stringstream ss;
	ss << "val is " << val << endl;
	cout << "ss is --> " << ss.str() << endl;
	ss.setf(ios::fixed);	//显示小数
	ss.precision(2);		//2位小数
	
	cout << "ss is --> " << ss.str() << endl;
	return ss.str();
}


int main()
{
	
	string str =  my_int2str(123.456);
	cout << str << endl;
	return 0;
}
