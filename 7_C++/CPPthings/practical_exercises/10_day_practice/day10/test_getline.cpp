#include <iostream>
#include <iomanip>
using namespace std;

// cin.getline() 会删除截止字符
// cin.get() 不会删除截止字符

void test1()
{
	char c;
	char array[10];
	cin.getline(array,10,',');
	cin.get(c);
	cout << setw(10) <<left<< "ok" << endl;

	cout << array << endl;
	cout <<"c:"<< c << endl;
}

void test2()
{
	char c;
	char array[5];
	
	cin.get(array,20,',');
	cin.get(c);
	
	cout << array << endl;
	cout << "c:" << c << endl;
	cout << sizeof(array) << endl;
}

int main()
{

	test2();

	return 0;
}
