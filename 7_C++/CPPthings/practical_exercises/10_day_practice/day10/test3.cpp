#include <iostream>

using namespace std;


int main()
{
	char c;
	char str[50] = "this is string...";
	while((c = cin.get()) != '\n'){
		cout.put(c);
		cout.put('\n');
		
		cout.write(str,50).put('\n');
	}


	return 0;
}
