

#include <iostream>


//类中包含其他自定义的class或者struct,采用初始化列表，实际上就是创建对象同时并初始化。
//采用类中赋值的方式，等价于先定义对象，再进行赋值，一般会先调用默认构造函数，再调用=操作符

class Animal{
public:
	Animal(){
		std::cout << "Animal() is called" << std::endl;
	}
	Animal(const Animal &){
		std::cout << "Animal(const Animal *) is called" << std::endl;
	}
	Animal &operator=(const Animal &){
		std::cout << "Animal & operator=(const Animal &) is called" << std::endl;
		return *this;
	}
	~Animal(){
		std::cout << "~Animal() is called" << std::endl;
	}
	
};

class Dog{
public:
	//使用初始化列表
	/*第一种  等价于 ==》 Animal _animal = animal;
	Dog(const Animal & animal) : _animal(animal) {
		std::cout << "Dog(const Animal &animal) is called" << std::endl;
	}	
	*/

//	/*第二种
 	Dog(const Animal &animal){
 		_animal = animal;
 		std::cout << "Dog(const Animal &animal) is called" << std::endl;
 	}
 
 // */
	~Dog(){
		std::cout << "~Dog() is called" << std::endl;
	}
private:
	Animal _animal;
};

int main()
{
	Animal animal;
	std::cout << "11111111111" << std::endl;	
	Dog dog(animal);
	
	return 0;
}


