#include <iostream>
#include <cstring>

using namespace std;




// 类型转换函数没有参数
// 类型转换函数没有返回值类型
// 类型转换函数必须返回将要转换成的type数据类型
class Circle
{
private:
	double x,y,r;
public:
	Circle(double x1,double y1, double r1){x=x1,y=y1,r=r1;}
	operator int(){
		return int(r);
	}
	operator double(){
		return 2*3.14*r;
	}
	operator float(){
		return (float)3.14*r*r;
	}
};


int main()
{
	Circle c(1,2,3);
	int r = c;
	cout << "r:" << r << endl;
	double length = c;
	cout << "length:" << length << endl;
	float area = c;
	cout << "area:" << area << endl;
		
	return 0;
}
