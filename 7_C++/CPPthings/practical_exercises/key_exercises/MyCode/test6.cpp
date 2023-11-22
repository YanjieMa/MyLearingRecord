#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	char *pStr;
	const char *s = "hello linux";
	pStr = new char[strlen(s) + 1];
	strncpy(pStr,s, strlen(s));
	cout << pStr << endl;
	delete pStr;
	return 0;
}
