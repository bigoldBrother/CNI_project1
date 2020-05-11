#include<string>
#include"../head/decode1.h"
#include"../head/Video.h"
#include"../head/FileCompare.h"

void usage();
int main(int argc, char* argv[])
{
	if (argc != 4) {
		usage();
		return 1;
	}
	string address_and_name_of_video=argv[1];//������Ƶָ����ŵ�ַ
	int number_of_frame = Video_TO_Image(address_and_name_of_video);//��ƵתͼƬ��������֡��

	
	string out_path=argv[2];//��������ļ�����
	string data="";//�洢������
	int code_count = 0;
	for (int i = 0; i < number_of_frame; )//��������֡
	{
		string filename = "image" + to_string(++i) + ".jpg";
		decode(filename,data,code_count);//����
		
	}
	cout << "������ɣ��������ɱȽ��ļ�..." << endl;
	ofstream out(out_path);
	out << data;
	out.close();
	string compare_file_name = argv[3];//�Ƚ��ļ��������
	FileCompare fcompare;
	fcompare.compare("source.bin", out_path, compare_file_name);
	cout << "�Ƚ��ļ�������ϣ�" << endl;
}
void usage() {
	cout << "========================================================================" << endl;
	cout << "����ȷʹ�ó���decode video_name output_file_name compare_file name" << endl;
	cout << "For example:decode out.mp4 out.bin vout.bin" << endl;
	cout << "�뽫ԭ�������ļ�����ͬһĿ¼�£�������Ϊsource.bin���Ա��ڱȶ�" << endl;
	cout<< "========================================================================" << endl;
}