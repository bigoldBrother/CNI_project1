#include "../head/QRCodeDrawer.h"
QRCodeDrawer::QRCodeDrawer() {
	outer_frame_width = 100;//����߿�
	frame_wid = 10;//�ڲ�ϸ�߿�
	currentX = frame_wid+ outer_frame_width;
	currentY = frame_wid+ outer_frame_width;//��ά����������ʼ��Ϊ����߿�֮��
	rect_len = 10;//��ά�뵥λ�����α߳�Ϊ10����
	code_col = 64;
	code_row = 64;//��ά��Ϊ64��64��
	data_index = 0;//��ʼʱ����������λ��Ϊ0
	num_row = 1;//��һ�����ڴ�Ŷ�ά�����
	code_pixel_col= 2 * frame_wid + rect_len * code_col;
	code_pixel_row= 2 * frame_wid + rect_len * code_row;
	all_code_pixel_col = 2 * outer_frame_width + 2 * frame_wid + rect_len * code_col;
	all_code_pixel_row = 2 * outer_frame_width + 2 * frame_wid + rect_len * code_row;
	code=Mat(all_code_pixel_col, all_code_pixel_row, CV_8UC3, Scalar(255, 255, 255));
}

//@breif draw a frame for the code
void QRCodeDrawer::draw_frame() {
	Scalar outer_frame_color= Scalar(0, 0, 0);//���߿���ɫ
	Scalar frame_color = Scalar(255, 255, 255); //�߿���ɫ
	Rect rect_all = Rect(0, 0, all_code_pixel_col, all_code_pixel_row); //���η�Χ:��ʼλ��xy������,���������ڲ�߿����ڵ�����ͼ��
	Rect rect_code_and_frame = Rect(outer_frame_width, outer_frame_width, code_pixel_col, code_pixel_row);//�����ڲ�߿����ڵľ���
	Rect rect_code = Rect(currentX, currentY, rect_len * code_col, rect_len * code_row);//��ά�������԰�ɫΪ��ɫ
	Scalar white = Scalar(255, 255, 255);   //��ɫ
	rectangle(code, rect_all, outer_frame_color, -1, LINE_8); //ԭͼ������Χ������ɫ���߿�������
	rectangle(code, rect_code_and_frame, frame_color,-1,LINE_8);//�ڲ�߿�
	rectangle(code, rect_code, white, -1, LINE_8);//��ά����Ч����
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
	currentY = frame_wid+ outer_frame_width;//��ά����������ʼ��Ϊ����߿�֮��
	rect_len = 10;//��ά�뵥λ�����α߳�Ϊ10����
	code_col = 64;
	code_row = 64;//��ά��Ϊ64��64��
	code = Mat(all_code_pixel_col, all_code_pixel_row, CV_8UC3, Scalar(255, 255, 255));
}

//@breif draw the main part of the code
void QRCodeDrawer::draw_code(int count) {
	Scalar black = Scalar(0, 0, 0); //��
	for (; currentY < all_code_pixel_row - frame_wid-outer_frame_width; currentY += rect_len) {
		if (currentY == frame_wid+outer_frame_width) {//�����ڻ��Ƶ�һ��
			string str = "";
			if(count == 0){//����ʼֱ��Ϊ0���������ӣ�ֱ����������
				continue;
			}
			else {//����ʼ���Ʊ��
				while (count)
				{
					str = to_string(count & 1) + str;
					count = count >> 1;

				}
				while (str.length() < 16)//��16λ��Ŷ�ά����
				{
					str = "0" + str;
				}
				int i = 0;
				for (; currentX < all_code_pixel_col - frame_wid-outer_frame_width; currentX += rect_len) {
					Rect rect = Rect(currentX, currentY, rect_len, rect_len); //��ǰҪ��ͼ�ľ���
					if (str[i] == '1')
						rectangle(code, rect, black, -1, LINE_8);
					if (i >= 15)
						i = 0;
					else
						i++;
				}
			}
		}
		else {//����ʼ�������ݲ���
			int len = data.length();//���ݵ��ܳ���
			if (data_index >= len)
				break;
			for (; currentX < all_code_pixel_col - frame_wid-outer_frame_width; currentX += rect_len) {
				Rect rect = Rect(currentX, currentY, rect_len, rect_len); //��ǰҪ��ͼ�ľ���
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
	set_code_num();//���������ά����
	for (int code_count = 0; code_count < code_num; code_count++) {
		initial();//��ԭ��ʼ����
		draw_frame();//���Ʊ߿�
		draw_code(code_count);//���ƶ�ά������
		stringstream ss;
		string num;
		ss << code_count;
		ss >> num;
		string path = file_path + "code" + num + ".jpg";
		imwrite(path,code);//����ͼƬ
	}
	
}

int QRCodeDrawer::getCode_num() {
	return code_num;
}