#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

class Person{
private:
	char Name[20];
	char Id[20];
	int Math;
	int Chinese;
	int English;
	int Sum;
public:
	Person()
	{}
	Person(char *name,char *id, int math, int chinese, int english)
	{
		strcpy(Name,name);
		strcpy(Id,id);
		Math = math;
		Chinese = chinese;
		English = english;
		Sum = Math + Chinese + English;
	}
	void display()
	{
		cout << "name: " << Name << endl;
		cout << "sum: " << Sum << endl;
	}
};


int main()
{
	char ch;
	char name[20];
	char id[20];
	int math,chinese,english;
	fstream io_file;
	io_file.open("./tmp.txt",ios::out | ios::app);
	do{
	cout << "input info..." << endl;
	cout << "name：";
	cin >> name;
	cout << "id:";
	cin >> id;
	cout << "math:";
	cin >> math;
	cout << "chinese:";
	cin >> chinese;
	cout << "english";
	cin >> english;
	Person p(name,id,math,chinese,english);
	io_file.write((char *)&p,sizeof(p));
	cout << "y?";
	cin >> ch;
	}while(ch =='y' | ch == 'Y');

	io_file.close();
	io_file.open("./tmp.txt",ios::in);
	
	Person p2;
	io_file.read((char *)&p2,sizeof(p2));
	
	vector<Person> v;
	while(!io_file.eof()){
		v.push_back(p2);
		io_file.read((char *)&p2, sizeof(p2));
	}
	io_file.close();
	cout << "info" << endl;
	for(vector<Person>::iterator it= v.begin();it != v.end();it++){
		(*it).display();
	}
	return 0;
}
