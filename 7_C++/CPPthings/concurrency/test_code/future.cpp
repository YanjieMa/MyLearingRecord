#include <iostream>
#include <future>

using namespace std;

// std::future<T>
// std::saync()
// std::shared_future
int get_value(int a, int b)
{
	return a+b;
}

void test1()
{
	std::future<int> a_future = std::async(get_value,10,20);
	std::shared_future<int> a_shared_future = a_future.share();
	
	//共享的future对象可以被多次访问
	cout << "value: " << a_shared_future.get() << endl;
	cout << "value: " << a_shared_future.get()+1 << endl;

}

void get_int(std::promise<int> &prom)
{
	int x;
	std::cout << "input an int:";
	std::cin.exceptions(std::ios::failbit);
	try{
		std::cin >> x;
		prom.set_value(x);
	}catch(std::exception &){
		prom.set_exception(std::current_exception());
	}
}
void print_int(std::future<int> &fut)
{
	try{
		int x = fut.get();
		cout << "value is:" << x << endl;
	}catch(std::exception &e){
		std::cout << "catch exception:" << e.what() << endl;
	}	
}
void test2()
{
	std::promise<int> prom;
	std::future<int> fut = prom.get_future();
	
	std::thread th1(get_int,std::ref(prom));
	std::thread th2(print_int,std::ref(fut));

	th1.join();
	th2.join();
}

int main()
{
	test2();
	return 0;
}
