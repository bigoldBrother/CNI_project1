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
	int code_pixel_col;//��ά�����������
	int code_pixel_row;//��ά������������
	int all_code_pixel_col;//����ͼ��ĺ���������
	int all_code_pixel_row;//����ͼ�������������
	int code_col;//��ά������
	int code_row;//��ά������
	int frame_wid;//�߿���
	int rect_len;//��ά���е�λ�����εı߳�
	int code_num;//������Ϣ���������ά������
	long int data_index;
	int num_row;//���ڴ�Ŷ�ά����ŵ�����
	int outer_frame_width;//����Χ��߿�����ؿ��
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

