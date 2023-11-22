#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

/* 双向链表容器 */

void print_int(int &val){
	cout << val << " ";
}

int main()
{
	//定义
	list<int> li(10,1);

	// 遍历元素
	for(list<int>::iterator it = li.begin(); it != li.end(); it++){
		cout << *it << " ";
	}
	cout << endl;

	//添加元素
	li.push_back(0);
	li.push_front(9);

	//遍历元素
	for(auto i:li){
		cout << i << " ";
	}
	cout << endl;

	// 删除元素
	li.pop_back();
	li.pop_front();

	//容器容量
	cout << "size:" << li.size() << endl;	

	//遍历元素
	for_each(li.begin(), li.end(), print_int);
	cout << endl;

	//判断元素为空
	cout << "empty:" << li.empty() << endl;

	//重置
	li.assign(5,9);

	for(auto i=li.begin(); i!= li.end(); i++){
		cout << *i << " ";
	}	
	cout << endl;
	//清空
	li.clear();

	li.push_back(1);
	li.push_back(2);
	// 删除指定位置元素
	li.erase(li.begin());
	
	for_each(li.begin(), li.end(), print_int);
	cout << endl;


	list<int> st;
	st.push_front(3);
	st.push_front(2);
	st.push_front(1);
	st.push_front(6);
	st.push_front(5);
	st.push_front(4);

	//merge
	li.merge(st);

	//sort 默认从小到大
	li.sort();


	for_each(li.begin(), li.end(), print_int);
	cout << endl;

	//sort 从大到小
	li.sort(greater<int>());
	for_each(li.begin(), li.end(), print_int);
	cout << endl;

	// 移除相邻重复元素
	li.unique();
	for_each(li.begin(), li.end(), print_int);
	cout << endl;
	return 0;
}
