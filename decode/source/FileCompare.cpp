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
		for (int i = 0; i < 8; i++)//һ���ֽ�8λ
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
		for (int i = 0; i < 8; i++)//һ���ֽ�8λ
		{
			str = to_string(c & 1) + str;
			c = c >> 1;
		}

		output_file += str;
	}
	int length = source_file.length() > output_file.length() ? output_file.length() : source_file.length();//ȡ���߽�Сֵ��Ϊ�Ƚ��ļ����ȡ�
	cout << "Դ�ļ����ȣ�";
	cout << source_file.length()<<"b" << endl;
	cout << "�����ļ����ȣ�";
	cout << output_file.length()<<"b" << endl;
	string temp="";//�ַ���temp��űȽϺ��01�ַ�����֮����Ҫ����ת��Ϊ�������ļ���ʽ
	for (int i = 0; i < length; i++) {
		if (source_file[i] == output_file[i])//������ȷ��Ϊ1������Ϊ0
			temp=temp+'1';
		else
			temp=temp+'0';
	}
	ch = 0;
	for (int i = 0; i < temp.length(); i++) {//��tempת��Ϊ��������ʽ
		if ((i + 1) % 8 != 0) {//����Ϊ��8����
			int up = pow(2, i%8);
			int bin = temp[i] == '1' ? 1 : 0;
			ch += bin * up;
		}
		else {//��8����
			int up = pow(2, i % 8);
			int bin = temp[i] == '1' ? 1 : 0;
			ch += bin * up;
			compare_file.push_back(ch);//�����ֽڷ����ļ�
			ch = 0;
		}
	}

	cout << "�Ƚ��ļ����ȣ�";
	cout << compare_file.length()*8<<"b"<<endl;
	ofstream aim(aim_path);
	aim << compare_file;
}
