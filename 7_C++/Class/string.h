#ifndef __STRING_H__
#define __STRING_H__

#include <string.h>

class String{

public:
//构造函数
	String(const char *p = 0);

	String(const String& s);
	
	String& operator=(const String& s);

	char * c_str() const { return p_data; }

//析构函数
	~String() {}

private:

	char * p_data;

};

//构造函数
inline
String::String(const char *p = 0){
	if(p){
		p_data = new char[strlen(p) + 1]; 
		strcpy(p_data, p);
	}else{
		p_data = new char[1];
		memcpy(p_data,'\0');
	}
}
//拷贝构造函数
inline
String::String(const String& s){
	p_data = new char[strlen(s.m_data) + 1];
	strcpy(p_data, s.p_data);
}
//赋值
String& String::operator=(const Strong& str){
	if(this == str){
		return *this;
	}
	if(p_data){
		delete [] p_data;
	}

	p_data = new char[strlen(str.p_data) + 1];
	strcpy(p_data,str.p_data);
	return *this;
}




inline
String::~String(){
	if(p_data){
		delete [] p_data;
	}
}





#endif
