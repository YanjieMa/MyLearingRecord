#include <iostream>

using namespace std;

//插入排序
template <typename T>
T* insertion_sort( T arr[], int len)
{
	for(int i=1; i<len; i++){  //从第二个元素开始遍历
		int pre_index = i-1;   //记录前一个元素的index 
		int current_val = arr[i];
		while(pre_index >= 0 &&  current_val < arr[pre_index]){ //当前一个元素存在 并且 当前元素小于前一个元素
			arr[pre_index+1] = arr[pre_index]; //把前一个元素移动到后面一个位置
			pre_index--;
		}
		arr[pre_index+1] = current_val;//知道当前元素找到适合自己的位置
	}
	return arr;
}

int main(int argc, char **argv)
{
		
	int *arr = new int[argc-1];
	for(int i=0; i< argc-1; i++){
		arr[i] = atoi(argv[i+1]);
	}
	for(int i=0;i < argc-1;i++){
		cout << arr[i] << "\t";
	}
	cout << endl;
	
	insertion_sort(arr,argc-1);

	for(int i=0;i < argc-1;i++){
		cout << arr[i] << "\t";
	}
	cout << endl;
	
	delete [] arr;
	return 0;
}
