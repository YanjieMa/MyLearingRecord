#include <iostream>

using namespace std;

//归并排序
template <typename T>
T* merge_sort( T arr[], int len)
{
	T *arr_head = arr;
	T *tmp = new T[len];

	for( int seg = 1; seg < len; seg += seg){ // 步长为 seg, 每次*2
		for(int start =0; start < len; start += (seg + seg)){ //按2*seg分割 进行排序
			int low = start, mid = min(start+seg, len), high = min(start+seg+seg, len);
			int k = low;
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			// 将长度为2*seg的排序放到tmp[low]
			while(start1 < end1 && start2 < end2){
				tmp[k++] = arr_head[start1] < arr_head[start2] ? arr_head[start1++] : arr_head[start2++];
			}
			while(start1 < end1){
				tmp[k++] = arr_head[start1++];
			}
			while(start2 < end2){
				tmp[k++] = arr_head[start2++];
			}
		}
		T *temp = arr_head;  //交换 arr 和 tmp
		arr_head = tmp;
		tmp = temp;	
	}
	//如果最后 arr_head 不是 arr的地址
	if (arr_head != arr){
		// tmp是arr的地址， 将所有的值放进tmp
		for(int i=0; i<len; i++){
			tmp[i] = arr_head[i];
		}	
		// 将tmp的地址改为临时申请的堆空间地址
		tmp = arr_head;
	}
	// 释放申请的空间
	delete [] tmp;

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
	
	merge_sort(arr,argc-1);

	for(int i=0;i < argc-1;i++){
		cout << arr[i] << "\t";
	}
	cout << endl;
	
	delete [] arr;
	return 0;
}
