#include <iostream>

using namespace std;

//选择排序
template <typename T>
T* selection_sort( T arr[], int len)
{
	int min_index;
	int tmp;

	for(int i=0; i<len-1; i++){ //需要遍历 len-1 次; 第0个 到 第len-1个
		min_index = i;	//假设每次遍历的起始元素是最小的
		for(int j=i+1; j<len;j++){ //与之后的每个元素比较
			if(arr[j] < arr[min_index])	{ //如果不是最小的 就把最小元素的index记录下来
				min_index = j;
			}
		}
		//更换起始元素和本次遍历最小元素的位置
		tmp = arr[min_index];
		arr[min_index] = arr[i];
		arr[i] = tmp;
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
	
	selection_sort(arr,argc-1);

	for(int i=0;i < argc-1;i++){
		cout << arr[i] << "\t";
	}
	cout << endl;
	
	delete [] arr;
	return 0;
}
