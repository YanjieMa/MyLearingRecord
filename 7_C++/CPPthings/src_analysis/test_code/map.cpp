#include <iostream>
#include <map>
#include <string>
using namespace std;



int main()
{
	map<int, string> mp;

	// insert
	mp.insert(pair<int,string>(1,"mayajie"));
	mp.insert(pair<int,string>(2,"mayijie"));	
	mp.insert(pair<int,string>(3,"mayanchao"));	
	mp.insert(pair<int,string>(4,"mashije"));	
	
	mp.insert(map<int,string>::value_type(001,"ma"));
	
	mp[006] = "danyang";
	// find
	auto it = mp.find(1);
	if(it != mp.end()){
		cout << it->first<< " "<<it->second<< endl;
	}else{
		cout << "not find" << endl;
	} 
	// erase
	mp.erase(001);
	mp.erase(mp.find(3));
	mp.erase(mp.begin(), mp.end());	
	// 遍历
	for(map<int,string>::iterator t = mp.begin(); t != mp.end(); t++){
		cout << t->first << " "<< t->second << endl;
	}
	
	mp.insert(pair<int, string>(10,"hello"));	
	for(auto m : mp){
		cout << m.first << " "<< m.second << endl;
	}

	return 0;
}
