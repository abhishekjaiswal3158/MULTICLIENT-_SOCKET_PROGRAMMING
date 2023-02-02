
#include <iostream>
#include <fstream>
#include<unordered_map>
using namespace std;

class File {
public:
	string port;
    string status;
	void input();
	unordered_map<string,string> accessStatus();
};


void File::input()
{
	ofstream file_obj;
	file_obj.open("Input.txt", ios::app);
	File obj;
    string pt="5555";
    string st="up";
	obj.port=pt;
    obj.status=st;
	file_obj.write((char*)&obj, sizeof(obj));
	pt="5556";
    st="up";
	obj.port=pt;
    obj.status=st;
	file_obj.write((char*)&obj, sizeof(obj));
    pt="5557";
    st="down";
	obj.port=pt;
    obj.status=st;
	file_obj.write((char*)&obj, sizeof(obj));
	return;
}

unordered_map<string,string> File::accessStatus()
{
	ifstream file_obj;
	file_obj.open("Input.txt", ios::in);
	File obj;
	file_obj.read((char*)&obj, sizeof(obj));
	unordered_map<string,string> data;
	while (!file_obj.eof()) {
		data[obj.port]=obj.status;
		file_obj.read((char*)&obj, sizeof(obj));
	}
	
    return data;
}

