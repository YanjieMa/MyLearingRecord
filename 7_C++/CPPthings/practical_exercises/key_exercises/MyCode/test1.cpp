#include <iostream>
#include <cstring>

using namespace std;
//职工基本信息结构
struct Person
{
	double salary;
	char *name;
};

class SalaryManager
{
private:
	Person *emplory; //存放职工信息的数组
	int max;		 //数组下标的上界
	int n;			 //数组中实际的职工人数
public:
	SalaryManager(int max){
		this->max = max;
		n = 0;
		emplory = new Person[3];
	}
	double &operator [](char *name){
		Person *p;
		for(p=emplory; p<emplory+n; p++){
			if(strcmp(p->name,name) == 0){
				return p->salary;
			}
		}
		p = emplory + n++;
		p->name = new char[strlen(name) + 1];
		strcpy(p->name, name);
		p->salary = 0;
		return p->salary;
	}
	void displary(){
		for(int i=0; i< n; i++){
			cout << emplory[i].name << " "<< emplory[i].salary << endl;
		}
	}
	~SalaryManager(){
		delete [] emplory;
	}

};

int main()
{
	SalaryManager s(3);
	s["zhangsan"] = 10.1;
	s["LISI"] = 20.2;
	s["wangwu"] = 30.3;
	cout << "zhangsan\t" << s["zhangsan"] << endl;
	cout << "LISI\t" << s["LISI"] << endl;
	cout << "wangwu\t" << s["wangwu"] << endl;
	s.displary();
}
