#pragma once
#include <string>
#include <iostream>  
#include <fstream> 

using namespace std;
//@brief load raw data and convert the data to an binary array
class load_data
{
private:
	void ConvertTextToBat(string infile_path);
	string data;
public:
	load_data();
	string get_data();
	void load_from(string infile_path);
};
