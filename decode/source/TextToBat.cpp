#include "TextToBat.h"
//@brief constructor
load_data::load_data() :data("") 
{

	return;
}

//@breif convert raw text to binary data
//@author laiyancheng
void load_data::ConvertTextToBat(string infile_path) 
{
	ifstream infile(infile_path);

	string s;
	if (infile.fail())
	{
		cout << "Cannot open text File" << endl;
		system("pause");
		exit(0);
	}
	while (getline(infile, s))//读取每行的s然后把其每个字符转化成二进制串输出
	{
		for (unsigned int i = 0; i < s.length(); i++)
		{
			int c = (int)s[i];
			string str = "";
			while (c)
			{
				str = to_string(c & 1) + str;
				c = c >> 1;

			}
			while (str.length() < 8)
			{
				str = "0" + str;
			}
			data += str;
		}

	}
	infile.close();
	return;
}

//@breif read binary data and save as a boolean array
//@author shitaotao
void load_data::load_from(string infile_path) 
{
	ConvertTextToBat(infile_path);
	return;
}

string load_data::get_data() 
{
	return data;
}