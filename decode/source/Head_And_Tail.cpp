#include"qrcode.h"

using namespace std;
using namespace cv;

//�����ʼ֡
void Add_Head(string file)
{
	Mat scri(660, 660, CV_8UC3, Scalar(0, 0, 0));
	string filename, num;//�ļ�����ͼƬ���
	stringstream register_of_name;
	for (int i = 1; i <= 30; i++)
	{
		register_of_name << i;
		register_of_name >> num;
		filename = file + "code" + num + ".jpg";
		imwrite(filename, scri);
	}
}

//�����ֹ֡
void Add_Tail(int number_of_head_plus_content,string file)
{
	Mat scri(660, 660, CV_8UC3, Scalar(0, 0, 0));
	string filename,num;
	stringstream register_of_name;
	for (int i = 1; i <= 15; i++)
	{
		register_of_name << number_of_head_plus_content+i;
		register_of_name >> num;
		filename = file + "code" +num+ ".jpg";
		imwrite(filename,scri);
	}
}