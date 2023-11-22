#include <iostream>
#include <cstring>

using namespace std;

class Emplory
{
public:
	Emplory(const char *name, const char *id)
	{
		strcpy(this->name, name);	
		strcpy(this->id, id);	
	}
	char *getname()
	{
		return name;
	}
	char *getid()
	{
		return id;
	}
	void display()
	{
		cout <<	name << ": " << id << endl;
	}

private:
	char name[20];
	char id[20];
};

class Manager:public Emplory
{
public:
	Manager(char *name, char *id, int salary):Emplory(name, id)
	{
		this->salary = salary;
	}
	void display(){
		cout << "Manager: " << getname() << ": " << getid() << ":" << salary << endl;
	}
private:
	int salary;
};

class Worker:public Emplory{
public:
	Worker(const char *name, const char *id, int time):Emplory(name,id){
		this->hour = time;	
	}
	void display()
	{
		cout << "Worker: "<< getname() << ": " << getid() << ":"<< hour << endl;
	}
private:
	int hour;

};

int main()
{
	Manager m("xiao wang", "001", 1000);
	Worker w("xiao mi", "007", 8);
	m.display();
	w.display();

	return 0;
}














