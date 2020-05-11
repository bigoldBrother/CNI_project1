#pragma once
#include<string>
#include <iostream>
#include <fstream>
using namespace std;
class FileCompare
{
private:
	string source_file;//原始数据文件
	string output_file;//解码后数据的文件
	string compare_file;//比较文件
public:
	FileCompare();//原始数据文件名，解码后数据文件名，比较文件输出路径
	void compare(string source_path, string output_path, string aim_path);

};

