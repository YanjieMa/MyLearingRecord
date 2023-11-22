#include <iostream>
#include <deque>

using namespace std;


/* 两端 */

/* size
 * max_size
 * resize
 *
 * */

int main()
{
	// 10个元素 值均为1
	deque<int > dq(10,1);

	for(auto i:dq){
		cout << i << " \t";
	} 
	cout << endl;
	
	//push_back  push_front 在队列末尾、头部增加一个元素
	dq.push_back(999);
	dq.push_front(100);
	for(deque<int>::iterator it = dq.begin(); it != dq.end(); it++){
		cout << *it << "\t";
	}
	cout << endl;

	// emplace_back  emplace_front 在队列末尾、头部增加新的元素
	dq.emplace_back(998);
	dq.emplace_front(101);
	
	// size  at
	for(int i(0); i<dq.size(); i++){
		cout << dq.at(i) << "\t";
	}
	cout << endl;
	
	// insert 在队列的某一元素前增加新的元素
	auto at = dq.begin();
	dq.insert(at,2,10);
	at++;

	//emplace 在队列指定元素位置插入新的元素
	dq.emplace(at,3); //一次只能插入一个元素
	for(auto i:dq){
		cout << i << "\t";
	}
	cout << endl;

	// pop_front  pop_back  在队列的头部或者尾部移除一个元素
	dq.pop_front();
	dq.pop_back();
	
	// erase 在队列的指定元素位置删除元素
	dq.erase(dq.begin(),dq.begin()+2);
	for(auto i:dq){
		cout << i << "\t";
	}
	cout <<endl;
	
	// front  back 返回头部或者尾部元素的引用
	cout << dq.front() << "\t";
	cout << dq.back();
	
	return 0;
}

