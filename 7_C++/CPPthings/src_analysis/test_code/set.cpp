#include <iostream>
#include <set>

using namespace std;

int main()
{
	set<int> myset;

	

	//1. insert
	myset.insert(10);
	myset.insert(20);
	myset.insert(30);
	myset.insert(40);
	myset.insert(50);
	myset.insert(50);
	//2. find
	set<int>::iterator  ite = myset.find(10);
	cout << "find " << *ite << endl;

	//遍历
	for(set<int>::iterator it = myset.begin(); it != myset.end(); it++){
		cout << *it << " ";
	}
	cout << endl;


	//3. erase
	myset.erase(ite);
	myset.erase(20);
	myset.erase(myset.begin(), myset.end());
	
	//4. auto遍历
	for(auto it = myset.begin(); it != myset.end(); it++){
		cout << *it << " ";
	}
	cout << endl;

	//5. size
	cout << "size is " << myset.size() << endl;

	//6. empty
	cout << "empty: " << (myset.empty() ? "yes":"no") << endl;
	return 0;
}
