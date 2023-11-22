#include <iostream>
#include <cstring>
#include <map>

using namespace std;

int main()
{
	map<const char *, const char *> mp;
	map<const char *, const char *>::iterator iter;
	const char key[3][20] = {"img","system","ip"};
	const char value[3][20] = {"a.img","win7","172.31.3.80"};

	//make_pair 插入
	for(int i=0; i<2; i++){
		mp.insert(make_pair(key[i],value[i]));
	}
	// pair<const char *, const char *> 插入
	mp.insert(pair<const char *, const char *>(key[2],value[2]));
	//数组插入方式
	mp["addr"] = "china";
	// 查找元素
	char key1[20];
	cin.getline(key1,20);
	for(iter = mp.begin(); iter != mp.end(); iter++){
		if(strcmp(iter->first,key1) == 0){
			cout << iter->first << " find " << iter->second <<endl;
		}
	}

	// 删除元素
	char *s = "addr";
	iter = mp.find(s);
	if(iter != mp.end()){
		cout << "找到了" << iter->second << endl;
		mp.erase(iter);
	}


	// 迭代器取出元素
	for(iter=mp.begin(); iter!=mp.end(); iter++){
		cout << iter->first<< "\t" << iter->second << endl;
	}
	
	return 0;
}
