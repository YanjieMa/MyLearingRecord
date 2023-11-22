#include <iostream>
#include <cstring>

using namespace std;

// 时钟类
class Clock
{
private:
	int hour;
	int minite;
	int second;
public:
	Clock(int h=0, int m=0, int s=0);
	void show_time();
	Clock& operator ++();
	Clock operator ++(int);
};

//时钟类的构造函数
Clock::Clock(int h, int m, int s)
{
	if( h>= 0 && h <= 24 && m>= 0 && m<= 60 && s >= 0 && s <= 60){
		hour = h;
		minite = m;
		second = s;
	}else{
		cout << "格式错误" << endl;
	}
}

//显示时间
void Clock::show_time()
{
	cout << hour <<":" << minite << ":" << second << endl; 
}

//重载前缀++
Clock& Clock::operator++()
{
	second++;
	if(second >= 60){
		second = second - 60;
		minite++;
		if(minite >= 60){
			minite = minite -60;
			hour++;
			hour = hour % 24;
		}
	}
	return *this;
}

//重载后缀++
Clock Clock::operator++(int)
{
	Clock old = *this; //默认拷贝构造
	++(*this);
	return old;
}

int main()
{
	Clock mc(10,10,10);
	mc.show_time();

	(mc++).show_time();

	(++mc).show_time();

	return 0;


}






