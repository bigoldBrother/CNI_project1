#include"../head/decode1.h"

using namespace std;

void ConvertBatToText()//二进制转文本
{
	ifstream infile("decode.txt");//文件名要加入文件地址!
	ofstream outfile("output.txt", ofstream::out);
	string s;
	if (infile.fail())
	{
		cout << "Cannot open text File" << endl;
		system("pause");
		exit(0);
	}
	char c; 
	int idx = 0, asc = 0;;
	while ((infile >> c && c != EOF))
	{

		if (c == '1')asc = asc * 2 + 1;
		else if (c == '0')asc = asc * 2;
		if (idx % 8 == 7)
		{
			outfile << (char)asc;
			asc = 0;
		}
		++idx;
	}
	infile.close();
	outfile.close();
	return;
}