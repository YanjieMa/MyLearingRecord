#include <iostream>
#include <thread>
#include <unistd.h>
#include <cassert>

using namespace std;

class back_ground_task
{
    public:
        void operator()() const
        {
            cout << "ok" << endl;
        }

};

void do_something(int &i)
{
    cout << "do somethiong " << i << endl; 
}

struct func
{
    int &i;

    func(int &i_) : i(i_) {}

    void operator()(){
        for(int j=0; j<1000; j++){
            do_something(i);
        }
    }

};

void f()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    thread t(my_func);
    cout << "f" << endl;
    try{

    }catch(...){
        t.join();
        throw;
    }
    t.join();

}

int main()
{
    back_ground_task bk_task;
    thread t(bk_task);
    t.join();

    thread my_thread1((back_ground_task()));
    my_thread1.join();

    thread my_thread2{back_ground_task()};
    my_thread2.join();

    thread t2(f);

    t2.detach();
    assert(t2.joinable());

    return 0;
}