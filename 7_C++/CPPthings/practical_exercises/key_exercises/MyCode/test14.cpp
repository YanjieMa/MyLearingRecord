#include <iostream>
#include <iomanip>

using namespace std;



int main()
{
	char *s = "this is string...";
	double digit = -101234.12345;
	// 设置宽度30 左对齐 填充*
	cout << setw(30) << left << setfill('*') << s << endl;
	// 设置10进制 4个数字位	
	cout << dec << setprecision(4) << digit << endl;

	cout << hex << setprecision(2) << 1000 << endl;

	cout << setbase(8) << 20 << endl;
	return 0;

}
