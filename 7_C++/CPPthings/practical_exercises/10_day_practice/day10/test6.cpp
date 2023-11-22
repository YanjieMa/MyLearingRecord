#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{
	fstream io_file;
	io_file.open("./io.txt",ios::out);

	io_file << "xiaoma" << " " << 12 << " " <<34 << endl;
	io_file << "laoli" << " " << 78 << " " << 99 << endl;
	
	io_file.close();
	
	io_file.open("./io.txt", ios::in | ios::binary);
	char name[10];
	int math;
	int chinese;
	while(!io_file.eof()){
		io_file >> name >> math >> chinese;
		cout << name << " " << math << " " << chinese << endl;
		bzero(name,10);
		math = 0;
		chinese = 0;
	}

	io_file.close();
	
	return 0;
}

