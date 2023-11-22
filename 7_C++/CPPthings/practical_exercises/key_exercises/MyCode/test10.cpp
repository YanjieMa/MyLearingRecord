#include <iostream>
#include <cstring>

using namespace std;

#define MAX_SIZE 10

template<class T>
class Array
{
public:
	Array(){
		for(int i=0; i<MAX_SIZE; i++){
			array[i] = 0;
		}
	}
	T &operator[] (int i);
	void sort();

private:
	T array[MAX_SIZE];
};

template<class T> T &Array<T>::operator[] (int i){
	if(i < 0 || i >= MAX_SIZE){
		cout << "array failed" << endl;
	}
	return array[i];
}

template<class T> void Array<T>::sort(){
	int m,n;
	for(int i=0; i<MAX_SIZE-1; i++){
		m = i;
		for(n = i+1; n< MAX_SIZE; n++){
			if(array[m] < array[n]){
				m = n;
			}
		}
		T t;
		t = array[i];
		array[i] = array[m];
		array[m] = t;		
	}
} 

template<> void Array<char *>::sort(){
	int m,n;
	for(int i = 0; i<MAX_SIZE-1; i++){
		m = i;
		for(n=m+1; n<MAX_SIZE; n++){
			if(strcmp(array[m],array[n]) < 0){
				m = n;
			}
		}
		char *t = array[i];
		array[i] = array[m];
		array[m] = t;
	}
}

int main()
{
	Array<int> a1;
	for(int i = 0; i < 10; i++){
		a1[i] = i;
	}	
	a1.sort();
	for(int i = 0; i<10; i++){
		cout <<a1[i] << endl;
	}
	Array<char*> a2;
	a2[0] = "aa";
	a2[1] = "bb";
	a2[2] = "cc";
	a2[3] = "dd";
	a2[4] = "ee";
	a2[5] = "ff";
	a2[6] = "cc";
	a2[7] = "cc";
	a2[8] = "cc";
	a2[9] = "cc";
	a2.sort();
	for(int i=0; i<3; i++){
		cout << a2[i] << endl;
	}
	return 0;
}





