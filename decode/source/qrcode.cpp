#include"qrcode.h"
QRCodeDrawer::QRCodeDrawer()
{
	frame_wid = 10;
	currentX = frame_wid;
	currentY = frame_wid;//前十个像素为边框
	rect_len = 10;//二维码单位长方形边长为10像素
	code_col = 64;
	code_row = 64;//二维码为64行64列
	data_index = 0;//初始时读到的数据位置为0
	code_pixel_col = 2 * frame_wid + rect_len * code_col;
	code_pixel_row = 2 * frame_wid + rect_len * code_col;
	code = Mat(code_pixel_col, code_pixel_row, CV_8UC3, Scalar(255, 255, 255));
}

//@breif draw a frame for the code
void QRCodeDrawer::draw_frame() 
{
	Scalar frame_color = Scalar(255, 255, 255); //边框颜色
	Rect rect_all = Rect(0, 0, code_pixel_col, code_pixel_col); //矩形范围:起始位置xy，宽，高,包括边框在内的整个图形
	Rect rect_code = Rect(currentX, currentY, code_pixel_col - 2 * frame_wid, code_pixel_row - 2 * frame_wid);//二维码区域，以白色为底色
	Scalar white = Scalar(255, 255, 255);   //白色
	rectangle(code, rect_all, frame_color, -1, LINE_8); //原图，矩阵范围，线颜色，线宽，线类型
	rectangle(code, rect_code, white, -1, LINE_8);
}

//@breif set the number of needed codes
void QRCodeDrawer::set_code_num() 
{
	double length = data.length();
	double coverage = code_col * code_row;
	code_num = ceil(length / coverage);
}

//@breif set the binary data stored as a string
void QRCodeDrawer::set_data(string data) 
{
	this->data = data;
}

//@breif initialize the parameters
void QRCodeDrawer::initial() 
{
	currentX = frame_wid;
	currentY = frame_wid;//前十个像素为边框
	rect_len = 10;//二维码单位长方形边长为10像素
	code_col = 64;
	code_row = 64;//二维码为64行64列
	code_pixel_col = 2 * frame_wid + rect_len * code_col;
	code_pixel_row = 2 * frame_wid + rect_len * code_col;
	code = Mat(code_pixel_col, code_pixel_row, CV_8UC3, Scalar(255, 255, 255));
}

//@breif draw the main part of the code
void QRCodeDrawer::draw_code() 
{
	Scalar black = Scalar(0, 0, 0); //黑
	for (; currentY < code_pixel_row - frame_wid; currentY += rect_len) {
		int len = data.length();
		if (data_index >= len)
			break;
		for (; currentX < code_pixel_col - frame_wid; currentX += rect_len) {
			Rect rect = Rect(currentX, currentY, rect_len, rect_len); //当前要绘图的矩形
			if (data_index >= data.length())
				break;
			else if (data[data_index] == '1')
				rectangle(code, rect, black, -1, LINE_8);
			data_index++;
		}
		currentX = frame_wid;
	}
}

//@breif generate the code
int QRCodeDrawer::generate_code(string file_path,int number_of_head) 
{
	set_code_num();//设置所需二维码数
	for (int code_count = 0; code_count < code_num; code_count++) {
		initial();//还原初始数据
		draw_frame();//绘制边框
		draw_code();//绘制二维码区域
		stringstream ss;
		string num;
		ss << code_count+number_of_head;
		ss >> num;
		string path = file_path + "code" + num + ".jpg";
		imwrite(path, code);//保存图片
	}
	return code_num + number_of_head;
}