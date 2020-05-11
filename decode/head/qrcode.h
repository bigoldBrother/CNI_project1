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
	int currentX;//��ǰ������ƾ������Ͻǵ�x����
	int currentY;//��ǰ������ƾ������Ͻǵ�y����
	int code_pixel_col;//��ά������������
	int code_pixel_row;//��ά�����������
	int code_col;//��ά������
	int code_row;//��ά������
	int frame_wid;//�߿���
	int rect_len;//��ά���е�λ�����εı߳�
	int code_num;//������Ϣ���������ά������
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
