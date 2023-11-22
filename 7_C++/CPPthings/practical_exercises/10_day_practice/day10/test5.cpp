#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	char str[20] = "this is string...";
	double d = -123.456;

	cout << setw(30) << left << setfill('*') << str << "---l1" << endl;
	cout << setw(30) << right << setfill('+') << str << "---l2" << endl;

	cout << dec << showbase << showpoint << setw(20) << "---l3" << endl;
	cout << setw(30) << showpoint << setprecision(10) << d << "---l4" << endl;
	cout << setw(30) << setbase(16) << 100 << "---l5" << endl;

	return 0;
}
