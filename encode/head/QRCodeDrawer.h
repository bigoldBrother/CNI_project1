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
	int code_pixel_col;//二维码横向像素数
	int code_pixel_row;//二维码纵向像素数
	int all_code_pixel_col;//整个图像的横向像素数
	int all_code_pixel_row;//整个图像的纵向像素数
	int code_col;//二维码列数
	int code_row;//二维码行数
	int frame_wid;//边框宽度
	int rect_len;//二维码中单位正方形的边长
	int code_num;//根据信息长度所需二维码数量
	long int data_index;
	int num_row;//用于存放二维码序号的行数
	int outer_frame_width;//最外围宽边框的像素宽度
	void draw_frame();
	void set_code_num();
	void draw_code(int count);
	void initial();
public:
	Mat code;
	QRCodeDrawer();
	void set_data(string data);
	void generate_code(string file_path);
	int getCode_num();
};

