#include <iostream>

using namespace std;




int main()
{
	char str[20] = "this is string...";
	cout.width(30);
	cout.fill('*');
	cout.setf(ios::left);
	cout << str << "-- l1" << endl;
	cout << "1234" << endl;

	cout.width(20);
	cout.fill('-');
	cout.setf(ios::right);
	cout<< str << "++l2" << endl;

	double d = -123.456;
	cout.setf(ios::dec | ios::showbase | ios::showpoint);
	cout.width(20);
	cout.fill('+');
	cout.setf(ios::left);
	cout <<d << "--l3"<< endl;	

	cout.setf(ios::oct, ios::basefield);
	cout << 100 << endl;

	return 0;
}
