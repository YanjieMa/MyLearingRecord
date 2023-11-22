#include <iostream>
#include <cstring>

using namespace std;

template<typename T, int MaxSize>
class Stack{
public:
	Stack(){
		cout << "Stack init ..." << endl;
		top = -1;
	}
	bool isFull(){
		if(top >= MaxSize){
			return true;
		}
		return false;
	}
	bool isEmpty(){
		if(top == -1){
			return true;
		}
		return false;
	}	
	void push(T e);
	T pop();	
private:
	T elems[MaxSize];
	int top;
};

template<typename T, int MaxSize> void Stack<T, MaxSize>::push(T e){
	if(!isFull()){
		elems[++top] = e;
	}else{
		cout << "has full" << endl;
	}
}

template<typename T, int MaxSize> T Stack<T, MaxSize>::pop(){
	if(!isEmpty()){
		return elems[top--];
	}else{
		cout << "is empty" << endl;
		return 0;
	}
}

int main()
{
	Stack<int, 2> s;
	for(int i=0; i<7; i++){
		s.push(i);
	}
	for(int j=0; j< 4;j++){
		cout << s.pop() << endl;
	}
	return 0;
}



