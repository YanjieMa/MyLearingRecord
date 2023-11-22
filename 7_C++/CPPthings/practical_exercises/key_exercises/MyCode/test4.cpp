#include <iostream>
#include <cstring>

using namespace std;

class Time
{
private:
	int hh,mm,ss;
public:
	Time(int h, int m, int s):hh(h),mm(m),ss(s){}
	void operator()(int h,int m, int s){
		hh = h;
		mm = m;
		ss = s;
	}
	void show(){
		cout << hh <<":"<< mm << ":" << ss << endl;
	}
};




int main()
{
	Time t(10,11,12);
	t.show();
	t.operator()(1,2,3);
	t.show();
	t(4,5,6); //重载小括号
	t.show();
	return 0; 
}
