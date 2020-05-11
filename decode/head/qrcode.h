#pragma once
#include <opencv2/opencv.hpp>
#include <iostream> 
#include <math.h>
#include<string>
using namespace cv;
using namespace std;
//@breif generate code
//@author shitaotao
class QRCodeDrawer
{
private:
	string data;
	int currentX;//当前所需绘制矩形左上角的x坐标
	int currentY;//当前所需绘制矩形左上角的y坐标
	int code_pixel_col;//二维码纵向像素数
	int code_pixel_row;//二维码横向像素数
	int code_col;//二维码列数
	int code_row;//二维码行数
	int frame_wid;//边框宽度
	int rect_len;//二维码中单位正方形的边长
	int code_num;//根据信息长度所需二维码数量
	int data_index;
	void draw_frame();
	void set_code_num();
	void draw_code();
	void initial();
public:
	Mat code;
	QRCodeDrawer();
	void set_data(string data);
	int generate_code(string file_path,int number_of_head);
};

void Add_Head(string file);
void Add_Tail(int number_of_head_plus_content,string file);
