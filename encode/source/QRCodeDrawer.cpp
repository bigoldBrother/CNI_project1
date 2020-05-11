#include "../head/QRCodeDrawer.h"
QRCodeDrawer::QRCodeDrawer() {
	outer_frame_width = 100;//外层宽边框
	frame_wid = 10;//内层细边框
	currentX = frame_wid+ outer_frame_width;
	currentY = frame_wid+ outer_frame_width;//二维码内容区起始处为内外边框之和
	rect_len = 10;//二维码单位长方形边长为10像素
	code_col = 64;
	code_row = 64;//二维码为64行64列
	data_index = 0;//初始时读到的数据位置为0
	num_row = 1;//第一行用于存放二维码序号
	code_pixel_col= 2 * frame_wid + rect_len * code_col;
	code_pixel_row= 2 * frame_wid + rect_len * code_row;
	all_code_pixel_col = 2 * outer_frame_width + 2 * frame_wid + rect_len * code_col;
	all_code_pixel_row = 2 * outer_frame_width + 2 * frame_wid + rect_len * code_row;
	code=Mat(all_code_pixel_col, all_code_pixel_row, CV_8UC3, Scalar(255, 255, 255));
}

//@breif draw a frame for the code
void QRCodeDrawer::draw_frame() {
	Scalar outer_frame_color= Scalar(0, 0, 0);//外层边框颜色
	Scalar frame_color = Scalar(255, 255, 255); //边框颜色
	Rect rect_all = Rect(0, 0, all_code_pixel_col, all_code_pixel_row); //矩形范围:起始位置xy，宽，高,包括外层和内层边框在内的整个图形
	Rect rect_code_and_frame = Rect(outer_frame_width, outer_frame_width, code_pixel_col, code_pixel_row);//包括内层边框在内的矩形
	Rect rect_code = Rect(currentX, currentY, rect_len * code_col, rect_len * code_row);//二维码区域，以白色为底色
	Scalar white = Scalar(255, 255, 255);   //白色
	rectangle(code, rect_all, outer_frame_color, -1, LINE_8); //原图，矩阵范围，线颜色，线宽，线类型
	rectangle(code, rect_code_and_frame, frame_color,-1,LINE_8);//内层边框
	rectangle(code, rect_code, white, -1, LINE_8);//二维码有效区域
}

//@breif set the number of needed codes
void QRCodeDrawer::set_code_num() {
	double length = data.length();
	double coverage = (double)code_col * (code_row-num_row);
	code_num = ceil(length / coverage);
}


//@breif set the binary data stored as a string
void QRCodeDrawer::set_data(string data) {
	this->data = data;
}

//@breif initialize the parameters
void QRCodeDrawer::initial() {
	currentX = frame_wid+ outer_frame_width;
	currentY = frame_wid+ outer_frame_width;//二维码内容区起始处为内外边框之和
	rect_len = 10;//二维码单位长方形边长为10像素
	code_col = 64;
	code_row = 64;//二维码为64行64列
	code = Mat(all_code_pixel_col, all_code_pixel_row, CV_8UC3, Scalar(255, 255, 255));
}

//@breif draw the main part of the code
void QRCodeDrawer::draw_code(int count) {
	Scalar black = Scalar(0, 0, 0); //黑
	for (; currentY < all_code_pixel_row - frame_wid-outer_frame_width; currentY += rect_len) {
		if (currentY == frame_wid+outer_frame_width) {//若正在绘制第一行
			string str = "";
			if(count == 0){//若开始直接为0，行数增加，直接跳过绘制
				continue;
			}
			else {//否则开始绘制编号
				while (count)
				{
					str = to_string(count & 1) + str;
					count = count >> 1;

				}
				while (str.length() < 16)//用16位存放二维码编号
				{
					str = "0" + str;
				}
				int i = 0;
				for (; currentX < all_code_pixel_col - frame_wid-outer_frame_width; currentX += rect_len) {
					Rect rect = Rect(currentX, currentY, rect_len, rect_len); //当前要绘图的矩形
					if (str[i] == '1')
						rectangle(code, rect, black, -1, LINE_8);
					if (i >= 15)
						i = 0;
					else
						i++;
				}
			}
		}
		else {//否则开始绘制数据部分
			int len = data.length();//数据的总长度
			if (data_index >= len)
				break;
			for (; currentX < all_code_pixel_col - frame_wid-outer_frame_width; currentX += rect_len) {
				Rect rect = Rect(currentX, currentY, rect_len, rect_len); //当前要绘图的矩形
				if (data_index >= data.length())
					break;
				else if (data[data_index] == '1')
					rectangle(code, rect, black, -1, LINE_8);
				data_index++;
			}
		}
		currentX = frame_wid+ outer_frame_width;
	}
}

//@breif generate the code
void QRCodeDrawer::generate_code(string file_path) {
	set_code_num();//设置所需二维码数
	for (int code_count = 0; code_count < code_num; code_count++) {
		initial();//还原初始数据
		draw_frame();//绘制边框
		draw_code(code_count);//绘制二维码区域
		stringstream ss;
		string num;
		ss << code_count;
		ss >> num;
		string path = file_path + "code" + num + ".jpg";
		imwrite(path,code);//保存图片
	}
	
}

int QRCodeDrawer::getCode_num() {
	return code_num;
}