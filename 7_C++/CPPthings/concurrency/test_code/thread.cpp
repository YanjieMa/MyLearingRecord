#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <chrono>
#include <shared_mutex>
#include <string>
#include <condition_variable>
#include <queue>
#include <memory>
using namespace std;

/*	<thread> 包含  std::thread  std::this_thread
 *	
 * */

// this_thread   sleep_for
void thread_test()
{
	cout << "创建线程 测试" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
//1.创建线程 然后join回收
void test1()
{
	//thread t1(thread_test); //初始化构造函数
	thread t1; //默认构造函数，创建一个空的thread对象
	t1 = thread(thread_test);
	cout << "main thread\n";
	sleep(1);		
	t1.join();//在主线程结束前应该 join子线程
}

//2.带参数多线程  detach分离线程
void thread_test2(int i)
{
	for(int j=0; j<i; j++){
		cout << "thread " << i << " is running\n";
		sleep(1);
	}
}
void test2()
{
	thread t2(thread_test2,4);
	t2.detach();
	for(int j=0; j< 4; j++){
		cout << "main thread is running\n";
		sleep(1);
	}
}

//3.重载了operator()的类 创建线程
class thread_class
{
	public:
		void operator()() const
		{
			cout << "thread class" << endl;
		}
};
void test3()
{
	//方法一：
	thread_class tc;
	thread task(tc);
	task.join();
	//方法二：
	thread task2((thread_class()));
	task2.join();
	//方法三：
	thread task3{thread_class()};
	task3.join();
}

//线程构造函数 有参数的构造
void ff(int &val)
{
	for(int i=0; i< val; i++){
		cout << "ff is running\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
void test4()
{
	int n=2;
	thread t1; //t1 is not a thread
	thread t2(ff,std::ref(n)); // pass by reference
	thread t3(std::move(t2)); //t3 is now running ff(), t2 is no longer a thread
	
	t3.join();
	cout << "join finish" << endl;
}

// get_id()
std::thread::id main_thread_id = std::this_thread::get_id();
void is_main_thread()
{
	std::thread::id this_thread_id = std::this_thread::get_id();
	cout << "this thread id is:" << this_thread_id << endl;
	if(this_thread_id == main_thread_id){
		cout << "main thread" << endl;
	}else{
		cout << "not main thread" << endl;
	}
}
void test5()
{
	cout << "main thread id is:" << main_thread_id <<endl;
	thread task(is_main_thread);
	task.join();
}

// joinable()
class thread_guard{
	std::thread &t;

public:
	explicit thread_guard(std::thread &t_) : t(t_) {}
// explicit 关键字用来修饰类的构造函数 禁止发生隐式类型转换	
	~thread_guard(){
		if(t.joinable()){
			t.join();
		}
	}
	thread_guard(thread_guard const &) = delete; //对象不能被拷贝构造
	thread_guard &operator=(thread_guard const &) = delete; //对象不能进行赋值构造
};
void test6()
{	
	thread task(is_main_thread);
	thread_guard t(task);
}

// 线程同步 mutex
/* <mutex> 包括  std::mutex  std::recursive_mutex  std::times_mutex
 *				 std::lock_guard  std::unique_lock
 *
 * */
// mutex
mutex mx;
int total_num = 20;
void thread1()
{
	while(total_num > 0){
		mx.lock();
		if(total_num < 0)
			break;
		cout << total_num << endl;
		total_num--;
		sleep(1);
		mx.unlock();
	}	
}

void thread2()
{
	while(total_num > 0){
		mx.lock();
		if(total_num < 0)
			break;
		cout << total_num << endl;
		total_num--;
		sleep(2);
		mx.unlock();
	}	
}
void thread3()
{
	while(total_num > 0){
		mx.lock();
		if(total_num < 0)
			break;
		cout << total_num << endl;
		total_num--;
		sleep(3);
		mx.unlock();
	}	
}
void test7()
{
	thread task1(thread1);
	thread task2(thread2);
	thread task3(thread3);
	task1.join();
	task2.join();
	task3.join();
}
// recursive_mutex
class X
{
	std::recursive_mutex m;
	std::string shared;
public:
	void func1(){
		//管理锁的模板类 被用作临时变量来使用 
		//初始化的时候 锁是lock操作
		//超出作用域 unlock
		std::lock_guard<std::recursive_mutex> lk(m);
		shared = "func1";
		std::cout << "in func1, shared variable is now "<< shared << '\n';
	}
	void func2(){
		std::lock_guard<std::recursive_mutex> lk(m);
		shared = "func2";
		std::cout << "in func2, shared variable is now " << shared << '\n';
		func1();
		std::cout << "back in func2, shared variable is now " <<shared << '\n';
	}
};
void test8()
{
	X x;
	thread t1(&X::func1, &x);
	thread t2(&X::func2, &x);
	t1.join();
	t2.join();
}

//线程同步 timed_mutex 定时尝试获取锁 成功返回true 失败返回false
std::timed_mutex tmx;
void firework()
{
	//等待获取锁，失败时每200ms输出‘-’
	while(!tmx.try_lock_for(std::chrono::milliseconds(400))){
		cout << "-";
	}
	//获取锁成功
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "*\n";
	tmx.unlock();
}
void test9()
{
	std::thread threads[10];
	for(int i=0; i<10; i++)
		threads[i] = std::thread(firework);
	for(auto &th : threads)
		th.join();
	
}

//管理互斥量的模板类 lock_guard
// local_guard 被用作局部变量使用
std::mutex m_tx;
void print_id(int & id)
{
	if(id % 3 == 0)
		cout << id << "is normal id\n";
	else
		throw std::logic_error("not normal id");
}
void print_thread_id(int & id)
{
	std::lock_guard<std::mutex> lck(m_tx);
	try{
		print_id(id);
	}catch(std::logic_error & l_e){
		cout << "catch logic error\n";
	}
	id++;
}
void test10()
{
	int n=0;
	thread threads[10];
	for(int i=0; i<10; i++)
		threads[i] = thread(print_thread_id, std::ref(n));
	for(auto &th : threads)
		th.join();
}

// unique_lock
std::mutex m_lock;
void print_block(int n, char a)
{
	//std::defer_lock 不设置锁的状态
	std::unique_lock<std::mutex> u_lock(m_lock,std::defer_lock);
	// try_lock 尝试对互斥量上锁，成功返回ture 失败返回false
	while(!u_lock.try_lock());
		for(int i=0; i<n;i++){
			cout << a;
		}
		cout << endl;
}
void test11()
{
	std::thread th1(print_block,4,'*');
	std::thread th2(print_block,6,'#');
	std::thread th3(print_block,8,'$');

	th1.join();
	th2.join();
	th3.join();
}

// <shared_mutex> 读锁 shared_lock
// shared_lock 和 unique_lock 一起使用 作为 读写锁
class ThreadSafeCounter
{
	mutable std::shared_mutex mutex_;
	unsigned int value_ = 0;

public:
	ThreadSafeCounter() =  default;
	
	unsigned int get() const
	{
		// 多个线程可以同时读数据
		std::shared_lock<std::shared_mutex> lk(mutex_);
		return value_;		
	}
	void increment()
	{
		// 只有一个线程能写数据
		std::unique_lock<std::shared_mutex> lk(mutex_);
		value_++;
	}
	void reset()
	{
		//只有一个线程能够写数据
		std::unique_lock<std::shared_mutex> lk(mutex_);
		value_ = 0;
	}
};
mutex mu;
void increment_and_print(class ThreadSafeCounter & c)
{
		unique_lock<std::mutex> u(mu,std::defer_lock);
		u.lock();
		//u.unlock();
		for(int i=0; i< 3; i++){
			c.increment();
			cout << std::this_thread::get_id() << '\t' << c.get() << endl;
		}
}

void test12()
{
	ThreadSafeCounter counter;
/*	
	auto increment_and_print = [&counter]() {
		for(int i=0; i< 3; i++){
			counter.increment();
			cout << std::this_thread::get_id() << '\t' << counter.get() << endl;
		}
	};
*/
	thread th1(increment_and_print,std::ref(counter));
	thread th2(increment_and_print,std::ref(counter));

	th1.join();
	th2.join();
}

// once_flag
std::once_flag one_flag;
//once_flag 相当于一个锁，使用它的线程会等待，只有一个线程允许执行。
//如果该线程抛出异常，从等待的线程中选择一个重复上述过程
void do_once(int n,bool f){
	printf("%d start\n",n);
	try{
		std::call_once(one_flag, [f](){cout << "call once\n";if(f) {cout << "throw\n"; throw std::exception();}});
	}catch(...){
		cout << "catch\n";
	}
	cout << "many times\n";
	printf("%d end\n",n);
}
void test13()
{
	thread th1(do_once,1,false);	
	thread th2(do_once,2,true);	
	thread th3(do_once,3,false);	

	th1.join();
	th2.join();
	th3.join();

}

// condition_variable   wait
std::mutex mxx;
std::condition_variable cv;

void print_name(string str)
{
	//std::unique_lock<std::mutex> lck(mxx,std::defer_lock);
	std::unique_lock<std::mutex> lck(mxx);
	cv.wait(lck);
	cout << str << endl;
}
void go()
{
	sleep(2);
	cout << "go" << endl;
	cv.notify_one();
}
void test14()
{
	std::thread threads[10];
	for(int i=0; i<10; i++){
		threads[i] = thread(print_name,"hello");
	}
	go();

	for(auto & th:threads){
		th.join();
	}
}

//生产者消费者
std::mutex mutex_lock;
std::condition_variable con_var;

int cargo = 0;

void consume(int n)
{
	for(int i=0; i<n; i++){
		std::unique_lock<std::mutex> lck(mutex_lock);
		cout << "begin wait\n";
		// 设置了predicate 只有当pred条件为false时 调用wait才会阻塞当前线程
		// 在收到其他线程通知后，只有pred为true时  才会调用lock 然后返回 解除阻塞
		//con_var.wait(lck,[](){return cargo != 0;});
		con_var.wait(lck);
		std::cout << "consume: "<< cargo << endl;
		cargo = 0;
	}
}

void test15()
{
	std::thread th(consume, 10);
	sleep(1);
	for(int i=0; i<10; i++){
		sleep(1);
		while(cargo != 0){
		//	con_var.notify_one();
			std::this_thread::yield();
		}
		std::unique_lock<std::mutex> lck(mutex_lock);
		cargo = i + 1;
		cout <<"cargo:" << cargo << endl;
		con_var.notify_one();
	}
	
	th.join();
}

//condition_variable  wait_for
//枚举类型
// cv_status::no_timeout
// cv_status::timeout
condition_variable con_v;
int value;
void read_value()
{
	cin >> value;
	con_v.notify_one();
}

void test16()
{
	std::thread th(read_value);
	
	std::mutex mx;
	std::unique_lock<std::mutex> ulc(mx);
	while(con_v.wait_for(ulc,std::chrono::seconds(1)) == std::cv_status::timeout){
		cout << '-';
		cout.flush();
	}
	
	cout << "your enter:" << value << endl;
	th.join();
}
// wait_until


//std::vondition_variable::notify_one()
std::mutex mx1;
std::condition_variable cv1;
int fl=0;

void consumer1()
{
	std::unique_lock<std::mutex> ul(mx1);
	while(fl == 0){
		cv1.wait(ul);
	}
	cout << "fl:" << fl << endl;
	fl = 0;
}
void producer1(int id)
{
	sleep(1);
	std::unique_lock<std::mutex> ul(mx1);
	fl = id;
//	while(fl != 0){
		cv1.notify_one();
//	}
}	
void test17()
{
	std::thread consumers[10], producers[10];

	for(int i=0; i<10; i++){
		consumers[i] = thread(consumer1);
		producers[i] = thread(producer1,i+1);
	}
	for(int i=0; i<10; i++){
		producers[i].join();
		consumers[i].join();
	}
}

// void notify_all_at_thread_exit(condition_variable &cv,
// unique_lock<mutex> ul);
// 线程退出时，所有阻塞在条件变量上的线程都会收到通知

//使用条件变量的线程安全队列
template<class T>
class ThreadSafe_Queue
{
	mutable std::mutex mx; //被mutable修饰的变量，将永远处于可变的状态
	std::queue<T> que;
	std::condition_variable cv;
public:
	ThreadSafe_Queue(){}
	ThreadSafe_Queue(ThreadSafe_Queue const & other){
		std::unique_lock<std::mutex> ulock(mx);
		que = other.que;
	}	
	void push(T val){
		std::unique_lock<std::mutex> ulock(mx);
		que.push(val);
		cv.notify_one();
	}
	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_lock<std::mutex> ulock(mx);
		cv.wait(ulock,[this]{return !que.empty();});		
		std::shared_ptr<T> res(std::make_shared<T>(que.front()));
		que.pop();
		return res;
	}
	std::shared_ptr<T>	try_pop()
	{
		std::unique_lock<std::mutex> ulock(mx);
		if(que.empty()){
			return std::shared_ptr<T>();	
		}
		std::shared_ptr<T> res(std::make_shared<T>(que.front()));
		que.pop();
		return res;
	}
	bool empty(){
		std::unique_lock<std::mutex> ulock(mx);
		return que.empty();
	}
};

ThreadSafe_Queue<int> ts;

void save_data()
{
	ts.push(10);
	ts.push(20);
	ts.push(30);
}
void test18()
{
	thread threads[5];
	for(int i=0; i<5; i++){
		threads[i] = thread(save_data);
	}
	sleep(1);
	for(int i=0; i<15;i++){
		cout << *ts.try_pop() << endl;	
	}
	for(int i=0; i<5; i++){
		threads[i].join();
	}
}

int main()
{
	test18();	
	return 0;
}
