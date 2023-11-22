#include <iostream>
#include <array>

using namespace std;
/* 数组 */

/* array<元素名, 元素个数> 数组名; //注意元素个数不能是变量
 * 方法：
 *		begin() end()
 *		size()
 *		at() []
 *		front()
 *		back()
 *		data()
 *		fill()
 *		swap()
 *		get(array)
 * */

// 未对array进行初始化， 将对array分配随机值
void test1()
{
	array<int, 100> arr;

	for(auto i: arr){
		cout << i << '\t';
	}
	cout << endl;
}

void test2()
{
	array<int, 100> arr {1, 2, 3}; //前几个元素进行初始化， 剩余的为0
	for(int i=0; i<arr.size(); i++){
		cout << arr[i] << '\t';
	}
	cout << endl;
}


void test3()
{
	array<int, 10> arr {};
	arr.fill(10);
	for(array<int, 10>::iterator it = arr.begin(); it != arr.end(); it++){
		cout << *it << '\t';
	}
	cout << endl;
}

void test4()
{
	array<int, 10> arr {1,2,3,4,5,6};
	
	// at() 遍历
	for(int i=0; i< arr.size(); i++){
		cout << arr.at(i) << '\t';
	}
	cout << endl;

	// [] 遍历
	for(int i=0; i<arr.size(); i++){
		cout << arr[i] << '\t';
	}
	cout << endl;
}

// front() 和 back()
void test5()
{
	array<int, 3> arr {1,2,3};
	
	cout << "front is "<< arr.front() << endl;
	cout << "back is "<< arr.back() << endl;
}

// data() 返回指针
void test6()
{
	array<int, 5> arr {1,2,3,4,5};

	cout << "*arr.data() is " << *arr.data() << endl;

	cout << "*(arr.data() + 2) is "<< *(arr.data() + 2) << endl;

}


// Tuple接口
void test7()
{
	array<int, 10> arr {1,2,3,4,5};
	int n = 4;
	//cout << "get(3) is " << get<n>(arr) << endl;  // n必须是常数 不能是变量
	cout << "get(3) is " << get<3>(arr) << endl;

	cout << "tuple_size<decltype(arr)>::value is " << tuple_size<decltype(arr)>::value << endl;

	tuple_element<2, decltype(arr)>::type type = get<3>(arr);
	cout << "tuple_element<1, decltype(arr)>::type is " << type << endl;

}


int main()
{

	test1();
/*
	cout << "*************" << endl;
	test2();
	cout << "*************" << endl;
	test3();
	cout << "*************" << endl;
	test4();
	cout << "*************" << endl;
	test5();
	cout << "*************" << endl;
	test6();
	cout << "*************" << endl;
	test7();
*/
	return 0;

/*
	array<int , 10> arr {1,2,3,4,5,6,7,8};

	for(auto i:arr){
		cout << i << endl;
	}
	
	arr.fill(0);
	for(auto i:arr){
		cout << i << endl;
	}
	cout << "++++++" << endl;
	cout << *arr.data() << endl;  //返回数组对象中第一个元素的指针
	cout << arr.at(9) << endl; //会进行数组越界检查， 抛出异常更安全
	cout << arr[7] << endl;

	for(int i(0); i<arr.size(); i++){
		cout << arr[i] << '\t';
	}
	cout << endl;
	arr.at(5) = 100;
	for(auto it = arr.begin(); it != arr.end(); it++){
		cout << *it << " ";
	}
	cout << endl;
	arr[3]=999;
	for(array<int,10>::iterator it= arr.begin(); it!=arr.end(); it++){
		cout << *it << "+" << endl;
	}
	return 0;
*/
}
