#ifndef __HEAD_H__
#define __HEAD_H__

#include <iostream>

/*


4. 参数传递与返回值
5. 操作符重载与临时对象	
*/



class Complex{
//公共
public:
	//构造函数 初值列
	Complex(double r = 0, double i = 0): re(r), im(i) {}


	//操作符重载1 成员函数
	inline Complex& operator += (const Complex &r);

	// const 表示不能修改成员变量，除非用mutable修饰
	double real() const  { return re;} //隐式内敛函数 建议编译器内敛
	inline double image() const  { return im;} //显式内联函数 建议
	inline double get_abs() ;//显式内敛 建议
	double get_sum() const ; //不内敛 

	//相同class的各个object互为friend
	double add_real(const Complex& param){
		return this->re + param.re;
	}

	//相同class的各个object互为friend
	inline double image(Complex& c);

//私有
private:
	double re;
	double im;

	// 友元
	friend Complex& __doapl(Complex* ths, const Complex& r);

};



//操作符重载1 成员函数
inline Complex& Complex::operator += (const Complex &r){
	return __doapl(this, r);
}

//
inline double Complex::get_abs() {
	return re*re + im*im;
}
//
double Complex::get_sum() const {
	return re + im; 
} //不内敛  //const后 不能修改成员变量，除非用mutable修饰
		    //const成员函数可以访问所有成员变量，但是只能访问const的成员函数
			// const修饰对象 只能调用const成员函数，因为非const成员函数可能修改成员变量。

//友元函数 可以访问私有成员
inline Complex& __doapl(Complex* ths, const Complex& r){
	ths->re += r.re;
	ths->im += r.im;
	return *ths;
}

//相同class的各个object互为friend
inline double Complex::image(Complex& c){
	return c.im;
}


//操作符重载2 非成员函数 没有this pointer
//正号

Complex operator + (Complex& c){
	return Complex(-c.real(),-c.image());
}
//加号1
Complex operator + (const Complex &a, const Complex& b){
	return Complex(a.real()+b.real(), a.image()+b.image());
}
//加号2(重载)
Complex operator + (const Complex &a, double b){
	return Complex(a.real()+b, a.image());
}

//输出 ostream 
std::ostream& operator << (std::ostream& os, const Complex& c){
	return os << '(' <<	c.get_sum() << ')';
}


#endif


//	Complex& operator += (const Complex& ); // pass by reference( to const) //return and para 尽量 by reference
