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
	string address_and_name_of_video=argv[1];//拍摄视频指定存放地址
	int number_of_frame = Video_TO_Image(address_and_name_of_video);//视频转图片并返回总帧数

	
	string out_path=argv[2];//输出数据文件名称
	string data="";//存储总数据
	int code_count = 0;
	for (int i = 0; i < number_of_frame; )//遍历所有帧
	{
		string filename = "image" + to_string(++i) + ".jpg";
		decode(filename,data,code_count);//解码
		
	}
	cout << "解码完成，正在生成比较文件..." << endl;
	ofstream out(out_path);
	out << data;
	out.close();
	string compare_file_name = argv[3];//比较文件输出名称
	FileCompare fcompare;
	fcompare.compare("source.bin", out_path, compare_file_name);
	cout << "比较文件生成完毕！" << endl;
}
void usage() {
	cout << "========================================================================" << endl;
	cout << "请正确使用程序：decode video_name output_file_name compare_file name" << endl;
	cout << "For example:decode out.mp4 out.bin vout.bin" << endl;
	cout << "请将原二进制文件放入同一目录下，并命名为source.bin，以便于比对" << endl;
	cout<< "========================================================================" << endl;
}