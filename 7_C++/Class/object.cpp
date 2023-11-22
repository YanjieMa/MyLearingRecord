

#include <iostream>



// comp复合 
// comp by ref (Delegation) 委托
// inheritance继承,  virtual function 虚函数
//


class Animal{

public:
	Animal() {
		std::cout << "Animal gou zao" << std::endl;
	}



	~Animal() {
		std::cout << "Animal xi gou" << std::endl;
	}

	virtual void voice() {};


private:


};

class Func{
public:
	Func(){
		std::cout << "Func gou zao" << std::endl;		
	}
	~Func(){
		std::cout << "Func xi gou" << std::endl;	
	}
private:


};



class Dog : public Animal{
public:
	Dog(){
		std::cout << "Dog gou zao" << std::endl;
	}

	~Dog(){
		std::cout << "Dog xi gou" << std::endl;
	}

private:

	Func * f;

};






class Value{
public:
	Value(int a, int b) : num(a), den(b) {}

	operator double() const {
		return (double)num/den;
	}


private:
	int num;
	int den;


};
int main()
{
	Value v(3,2);	

	std::cout << (2.1+v) << std::endl;

	return 0;
}
