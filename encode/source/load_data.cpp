#include "../head/load_data.h"
//@brief constructor
load_data::load_data():data("") {
	fps = 10;
	head_tail_num = 10;
	return;
}

//@breif convert raw text to binary data and save the binary data as a file
//@author laiyancheng
void load_data::ConvertTextToBat(string infile_path) {
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
	ofstream out_file("source.txt");
	out_file << data;
	infile.close();
	out_file.close();
	return;
}

//@breif read binary data and save as a boolean array
//@author shitaotao
void load_data::load_from(string infile_path,int video_length) {
	
	//ifstream infile(infile_path,ios::in|ios::binary);
	//char ch;
	//
	//if (infile.fail())
	//{
	//	cout << "源文件打开失败，无法生成视频。请检查源文件路径！" << endl;
	//	system("pause");
	//	exit(0);
	//}
	//while (infile.read((char*)&ch,sizeof(ch)))//读取每行的s然后把其每个字符转化成二进制串
	//{
	//	string str = "";
	//	for (unsigned int i = 0; i < 8; i++)//一个字节8位
	//	{
	//		str = to_string((int)ch & 1) + str;
	//		ch = ch >> 1;
	//		
	//	}
	//	data = data+str;

	//}
	FILE* fp = NULL;
	fopen_s(&fp,infile_path.c_str(), "rb");
	char ch; 
	string File;
	int char_count = 0;//当前读入的字节数
	int frame_num = 0;//当前帧数
	while (frame_num+head_tail_num<(video_length/1000*fps))//若当前帧数小于设定帧数，则继续读取，否则读取结束，
	{
		ch = fgetc(fp);
		File.push_back(ch);
		char_count++;
		frame_num = char_count * 8 / 63 / 64;//当前帧数为位数除以63*64
	}
	fclose(fp);
	int MAX_SIZE = File.length();
	string Frame = "";
	for (int i = 0; i < MAX_SIZE; i++)
	{
		char ch = File[i];
		unsigned int c = ch;
		string str = "";
		for(int i=0;i<8;i++)//一个字节8位
		{
			str = to_string(c & 1) + str;
			c = c >> 1;
		}
		
		data += str;
	}

	ofstream out("source.bin");
	out << File;
	
	
}

string load_data::get_data() {
	return data;
}