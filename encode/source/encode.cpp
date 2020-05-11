#include "../head/load_data.h"
#include <opencv2/opencv.hpp> //包含头文件
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
	cout << "正在读取文件..." << endl;
	load_data.load_from(input_file,length);
	string data = load_data.get_data();
	cout << "文件读取完成！" << endl;
	Drawer.set_data(load_data.get_data());
	cout << "正在生成帧..." << endl;
	Drawer.generate_code("./");
	cout << "帧生成完成！" << endl;
	cout << "正在生成视频..." << endl;
	Image_TO_Video(Drawer.getCode_num(), video_name, length);
	cout << "视频生成完毕！" << endl;
	//namedWindow("test opencv setup", WINDOW_AUTOSIZE); //创建窗口，自动大小
	//imshow("test opencv setup", code); //显示图像到指定的窗口
	//waitKey();
}

void usage() {
	cout << "========================================================================================================="<<endl;
	cout << "请正确使用编码程序：encode input_file_name video_file_name video_length(ms)" << endl;
	cout << "For example:encode in.bin in.mp4 1000" << endl;
	cout << "本程序将生成一个名为source.bin的文件作为比对标准，在解码时请将其放入decode.exe的同一目录下" << endl;
	cout << "========================================================================================================="<<endl;
}