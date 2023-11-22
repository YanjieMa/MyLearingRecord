#include <iostream>
#include <vector>


using namespace std;

/* 动态数组 */

int main()
{
	
	//定义
	vector<int> vec;
	
	// push_back 尾部添加数据
	vec.push_back(9);
	
	vec.push_back(10);

	//遍历
	for(auto v:vec){
		cout << v << " ";
	}	
	cout << endl;
	
	//size 获取大小
	cout << "size:" << vec.size() << endl;;

	vec.push_back(8);
	//insert 在指定位置插入数据
	vec.insert(vec.begin()+1,1);

	//遍历
	for(vector<int>::iterator it=vec.begin(); it!= vec.end(); it++){
		cout << *it << " ";
	}
	cout << endl;

	// erase 删除数据
	vec.erase(vec.begin(),vec.end()-1);
	
	for(int i(0); i< vec.size();i++){
		cout << vec[i] << " ";
	}
	cout << endl;

	// pop_back 尾部删除数据
	vec.pop_back();
	
	// resize 重新调整大小
	vec.resize(10);
	
	// at()
	for(int j=0; j< 10; j++){
		vec.at(j) = j;
	}

	// []
	for(int i=0; i< vec.size(); i++){
		cout << vec[i] << " ";
	}
	cout << endl;
	
	// clear
	vec.clear();
	return 0;
}
