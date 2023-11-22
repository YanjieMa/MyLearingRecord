#include <iostream>
#include <string.h>

using namespace std;


class Conver{
public:
	explicit Conver(int num, int den = 1) : _num(num), _den(den) {}

	operator double() const {
		return (double) _num / _den;
	}

	Conver operator+ (const Conver& c){
		return Conver(_num+c._num, _den+c._den);
	}

private:
	int _num;
	int _den;
	string s = "123";
};



int main()
{

	Conver a(3,5);
	std::cout << (2.1 + a) << std::endl; //a会转换为double
	Conver b(4,5);
	cout << (a + b) << endl; // 重载了 加号
	cout << (a + 4) << endl; // 4会先转化为Conver，然后调用重载的加号   如果有两条路  会有歧义 报错
	return 0;
}
