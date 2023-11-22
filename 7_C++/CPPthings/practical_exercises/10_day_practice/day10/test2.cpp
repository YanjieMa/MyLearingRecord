#include <iostream>

using namespace std;

int main()
{
	char str[5][10];
	int i;

	for(i=0; i< 5; i++){
		cin.getline(str[i], sizeof(str[i]), ',');
	}
	for(i=0; i< 5; i++){
		cout << str[i] << endl;
	}



	return 0;
}
