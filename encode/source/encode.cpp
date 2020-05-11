#include "../head/load_data.h"
#include <opencv2/opencv.hpp> //����ͷ�ļ�
#include <iostream> 
#include"../head/QRCodeDrawer.h"
#include"../head/Video.h"
void usage();
int main(int argc, char* argv[])
{
	if (argc != 4) {
		usage();
		return 1;
	}
	load_data load_data;
	QRCodeDrawer Drawer;
	string input_file = argv[1];
	string video_name = argv[2];
	string len = argv[3];
	int length =stoi(len);
	cout << "���ڶ�ȡ�ļ�..." << endl;
	load_data.load_from(input_file,length);
	string data = load_data.get_data();
	cout << "�ļ���ȡ��ɣ�" << endl;
	Drawer.set_data(load_data.get_data());
	cout << "��������֡..." << endl;
	Drawer.generate_code("./");
	cout << "֡������ɣ�" << endl;
	cout << "����������Ƶ..." << endl;
	Image_TO_Video(Drawer.getCode_num(), video_name, length);
	cout << "��Ƶ������ϣ�" << endl;
	//namedWindow("test opencv setup", WINDOW_AUTOSIZE); //�������ڣ��Զ���С
	//imshow("test opencv setup", code); //��ʾͼ��ָ���Ĵ���
	//waitKey();
}

void usage() {
	cout << "========================================================================================================="<<endl;
	cout << "����ȷʹ�ñ������encode input_file_name video_file_name video_length(ms)" << endl;
	cout << "For example:encode in.bin in.mp4 1000" << endl;
	cout << "����������һ����Ϊsource.bin���ļ���Ϊ�ȶԱ�׼���ڽ���ʱ�뽫�����decode.exe��ͬһĿ¼��" << endl;
	cout << "========================================================================================================="<<endl;
}