#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <string>
/* 1. std::thread 产生的线程是复制的
 * 2. std::thread::join() 阻塞回收
 * 3. std::thread::detach() 线程分离
 * 4. std::thread::joinable() 是否可回收
 *
 * */
void job(const int &n, char *buf, const std::string &str)
{	//虽然用的是引用，但创建线程实际是值传递 不建议使用
	//指针是指针传递 使用指针并不安全 detach时会使指针有问题
	//存在主线程已经被回收了然后才转子线程参数的可能性
	for(int i=0; i<n; i++){
		std::cout << buf << std::endl;
		std::cout << str.c_str() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void test1()
{
	int n=3;
	int &ref = n;
	char buf[] = "qwer";
	std::string str = "asdf";
	job(ref,buf,std::ref(str));
	//传递参数时创建临时变量 可以保证 传参的正确性， 不被销毁
	//主线程先进行有参构造 子线程进行拷贝构造
	std::thread my_job(job, ref,buf, std::string(str));
	//thread是标准库里面的一个类
	std::cout << "you  love china" << std::endl;
	if(my_job.joinable()){
		std::cout <<"joinable" << std::endl;
	}else{
		std::cout <<"not joinable" << std::endl;
	}

	my_job.detach();

	if(my_job.joinable()){
		std::cout <<"joinable" << std::endl;
	}else{
		std::cout << "not joinable" << std::endl;
	}
}

class STR{
public:
	int m_i;
	//类型转换构造函数
	STR(int i):m_i(i) {std::cout <<this<< " STR有参构造"<<std::endl;}
	STR(const STR &s) : m_i(s.m_i) {std::cout<<this << " STR拷贝构造" <<std::endl;}
	~STR() {std::cout << "析构函数" << std::endl;}
};

void my_thread(const int i, const STR &str)
{
	std::cout << " i is:" << i <<std::endl;
	std::cout << " str is:" << str.m_i << std::endl;
}
void test11()
{
	int val = 1;
	std::thread th(my_thread,val, STR(val));

	th.detach();//使用detach时，必须小心临时变量是否已经被释放
}


//类对象创建线程
class CL
{
public:
	int &val;
	void operator()(){
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "operator: "<< val << std::endl;
	}
	//CL(){
	//	std::cout << "空构造函数" << std::endl;
	//}
	CL(const CL &cl) : val(cl.val) {
		std::cout << "拷贝构造函数, v is:"<< val << std::endl;
	}

	CL(int &v) : val(v) {
		std::cout << "赋值构造函数,v is:" << val<<std::endl;
	}
	~CL(){
		std::cout << "析构函数"<<std::endl;
	}
};

void test2()
{
	int a=10;
	//方法1
	CL op_class(std::ref(a));
	std::thread th1(op_class);
	th1.join();
	//方法2
	//std::thread th2((CL(a)));
	//th2.detach();
	//方法3
	//std::thread th3{CL(a)};
	//th3.join();
}

//lambda表达式创建线程 先中括号在小括号传参
void test3()
{
	//lambda函数
	auto my_func = [](int a){
		std::cout << "my thread begin:" << a << std::endl;
	};
	std::thread th(my_func,10);
	
	th.join();
}

//线程id



int main()
{
	test11();	
	return 0;
}

