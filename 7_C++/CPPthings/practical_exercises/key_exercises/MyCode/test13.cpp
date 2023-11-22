#include <iostream>
#include <cstring>

using namespace std;

class Sale
{
public:
	Sale(char *name, char *id, int age)
	{
		strcpy(Name,name);
		strcpy(Id,id);
		Age = age;
	}
	
	friend Sale &operator<<(ostream &os, Sale &s);
	friend Sale &operator>>(istream &is, Sale &s);

private:
	char Name[20];
	char Id[20];
	int Age;

};

Sale &operator<<(ostream &os, Sale &s)
{
	os << s.Name << "\t";
	os << s.Id << "\t";
	os << s.Age << endl;
	return s;
}

Sale &operator>>(istream &is, Sale &s)
{
	cout << "input name id age:" << endl;
	is >> s.Name >> s.Id >> s.Age;
	return s;
}


int main()
{
	Sale s("xiaoma","123",30);
	cout << s;
	cout << endl;
	cin >> s;
	cout << s;
	return 0;
}
