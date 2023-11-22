#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

/* 队列 */

int main()
{
	queue<int , list<int> > qu;
	for(int i(0); i<10; i++){
		qu.push(i);
	}
	// 遍历比较困难	

	cout <<"front " << qu.front() << endl;
	cout << "size:" << qu.size() << endl;

	qu.pop();
	cout <<"front " <<qu.front() << endl;
	cout << "size:" << qu.size() << endl;
	cout << "empty: " << qu.empty() << endl;
	return 0;
}

