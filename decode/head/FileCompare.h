#pragma once
#include<string>
#include <iostream>
#include <fstream>
using namespace std;
class FileCompare
{
private:
	string source_file;//ԭʼ�����ļ�
	string output_file;//��������ݵ��ļ�
	string compare_file;//�Ƚ��ļ�
public:
	FileCompare();//ԭʼ�����ļ���������������ļ������Ƚ��ļ����·��
	void compare(string source_path, string output_path, string aim_path);

};

