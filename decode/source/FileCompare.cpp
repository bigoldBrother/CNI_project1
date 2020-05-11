#include "../head/FileCompare.h"
FileCompare::FileCompare() {
	source_file = "";
	output_file = "";
	compare_file = "";
}

void FileCompare::compare(string source_path, string output_path, string aim_path) {
	
	FILE* sfp = NULL;
	fopen_s(&sfp, source_path.c_str(), "rb");
	char ch;
	string File;
	while (!feof(sfp))
	{
		ch = fgetc(sfp);
		File.push_back(ch);
	}
	fclose(sfp);
	int MAX_SIZE = File.length();
	for (int i = 0; i < MAX_SIZE; i++)
	{
		char ch = File[i];
		unsigned int c = ch;
		string str = "";
		for (int i = 0; i < 8; i++)//一个字节8位
		{
			str = to_string(c & 1) + str;
			c = c >> 1;
		}

		source_file += str;
	}

	FILE* ofp = NULL;
	fopen_s(&ofp, output_path.c_str(), "rb");
	string oFile;
	while (!feof(ofp))
	{
		ch = fgetc(ofp);
		oFile.push_back(ch);
	}
	fclose(ofp);
	MAX_SIZE = oFile.length();
	for (int i = 0; i < MAX_SIZE; i++)
	{
		char ch = oFile[i];
		unsigned int c = ch;
		string str = "";
		for (int i = 0; i < 8; i++)//一个字节8位
		{
			str = to_string(c & 1) + str;
			c = c >> 1;
		}

		output_file += str;
	}
	int length = source_file.length() > output_file.length() ? output_file.length() : source_file.length();//取二者较小值作为比较文件长度。
	cout << "源文件长度：";
	cout << source_file.length()<<"b" << endl;
	cout << "解码文件长度：";
	cout << output_file.length()<<"b" << endl;
	string temp="";//字符串temp存放比较后的01字符串，之后需要将其转化为二进制文件形式
	for (int i = 0; i < length; i++) {
		if (source_file[i] == output_file[i])//解码正确则为1，否则为0
			temp=temp+'1';
		else
			temp=temp+'0';
	}
	ch = 0;
	for (int i = 0; i < temp.length(); i++) {//将temp转化为二进制形式
		if ((i + 1) % 8 != 0) {//若不为第8个数
			int up = pow(2, i%8);
			int bin = temp[i] == '1' ? 1 : 0;
			ch += bin * up;
		}
		else {//第8个数
			int up = pow(2, i % 8);
			int bin = temp[i] == '1' ? 1 : 0;
			ch += bin * up;
			compare_file.push_back(ch);//将此字节放入文件
			ch = 0;
		}
	}

	cout << "比较文件长度：";
	cout << compare_file.length()*8<<"b"<<endl;
	ofstream aim(aim_path);
	aim << compare_file;
}
