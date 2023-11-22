#include <iostream>

using namespace std;

//冒泡排序
template <typename T>
T* bubble_sort( T arr[],int len)
{
	for(int i=0; i< len-1; i++){ //需要遍历 len-1 次
		for(int j=0; j<len-1-i;j++){ // 每次遍历 len-1-i 个元素
			if(arr[j] > arr[j+1]){
				T tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
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
	
	bubble_sort(arr,argc-1);

	for(int i=0;i < argc-1;i++){
		cout << arr[i] << "\t";
	}
	cout << endl;
	
	delete [] arr;
	return 0;
}
