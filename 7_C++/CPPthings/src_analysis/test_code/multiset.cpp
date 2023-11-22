#include <iostream>
#include <set>

using namespace std;

int main()
{
	//构造函数
	multiset<int> mset;
	//1. insert
	mset.insert(10);
	mset.insert(10);
	mset.insert(20);
	mset.insert(30);
	mset.insert(40);
	mset.insert(50);
	
	//2. begin end
	for(auto it = mset.begin(); it != mset.end(); it++){
		cout << *it << " ";
	}
	cout << endl;
	//3. size
	cout << "size is " << mset.size() <<endl;

	//4. empty
	cout << "empty: "<< (mset.empty()?"yes":"no") << endl;
	
	//5. find
	auto f = mset.find(10);
	//cout << "f is " << f << endl;
	cout << "*f is " << *f << endl;

	// count
	cout << "10 occuor: " << mset.count(10) << endl;


	//6. erase
	mset.erase(10);
	for(multiset<int>::iterator it = mset.begin(); it != mset.end(); it++){
		cout << *it << " ";
	}
	cout << endl;
	return 0;
}
