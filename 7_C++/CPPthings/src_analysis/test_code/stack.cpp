#include <iostream>
#include <stack>
#include <vector>
#include <list>
using namespace std;

/* 栈 */

int main()
{
	clock_t s_time;
	s_time = clock();

	stack<int, list<int>> s;
	for(int i(0); i<100000; i++){
		// push 入栈
		s.push(i);
	}
	// top 获取栈顶元素
	cout << "s.top():" << s.top() << endl;
	// size 获取栈的大小
	cout << "s.size():" << s.size() << endl;
	// pop 出栈
	s.pop();	

	cout << "s.top():" << s.top() << endl;
	cout << "s.size():" << s.size() << endl;
	
	cout << "time is:" << (clock()-s_time) << endl;
	cout << "+_+++++++++" << endl;


	s_time = clock();
	stack<int, deque<int>> ds;
	for(int i(0); i<100000; i++){
		ds.push(i);
	}
	cout << "ds.top():" << ds.top() << endl;
	cout << "ds.size():" << ds.size() << endl;
	s.pop();	
	cout << "ds.top():" << ds.top() << endl;
	cout << "ds.size():" << ds.size() << endl;

	cout << "time is:" << (clock()-s_time) << endl;

	cout << "+_+++++++++" << endl;


	s_time = clock();
	stack<int, vector<int>> vs;
	for(int i(0); i<100000; i++){
		vs.push(i);
	}
	cout << "vs.top():" << vs.top() << endl;
	cout << "vs.size():" << vs.size() << endl;

	s.pop();	
	cout << "ds.top():" << vs.top() << endl;
	cout << "ds.size():" << vs.size() << endl;

	cout << "time is:" << (clock()-s_time) << endl;
	return 0;
}

