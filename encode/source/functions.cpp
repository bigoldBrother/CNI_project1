
#include <string>
#include <iostream>  
#include <fstream> 
#include <typeinfo>
#include "../head/load_data.h"
#include <opencv2/opencv.hpp> //����ͷ�ļ�
#include <iostream> 
#include"../head/QRCodeDrawer.h"
using namespace cv;
using namespace std;



//int main()
//{
//	load_data load_data;
//	QRCodeDrawer Drawer;
//	load_data.load_from("./data/input.txt");
//	string data = load_data.get_data();
//
//	Drawer.set_data(load_data.get_data());
//	Drawer.generate_code("./data/");
//		
//	
//	//namedWindow("test opencv setup", WINDOW_AUTOSIZE); //�������ڣ��Զ���С
//	//imshow("test opencv setup", code); //��ʾͼ��ָ���Ĵ���
//	//waitKey();
//}

void draw_qrcode() {
	Mat dst(10,10,CV_8UC3, Scalar(0, 0, 255));
	
}
//@breif convert raw text to binary data
//@author laiyancheng
//void converttxttobat()
//{ 
//	string infile_path = "./data/input.txt";
//	string output_path = "./data/output.dat";
//	ifstream infile(infile_path);
//	ofstream outfile(output_path, ofstream::out);
//	string s;
//	if (infile.fail())
//	{
//		cout << "cannot open text file" << endl;
//		system("pause");
//		exit(0);
//	}
//	while(getline(infile,s))//��ȡÿ�е�sȻ�����ÿ���ַ�ת���ɶ����ƴ����
//	{
//		for (unsigned int i = 0; i < s.length(); i++)
//		{
//			int c =(int) s[i];
//			string str = "";
//			while (c)
//			{
//				str = to_string(c & 1) + str;
//				c = c >> 1;
//				cout << typeid(c).name()<<endl;
//			}
//			while (str.length() < 8)
//			{
//				str = "0" + str;
//			}
//			//str += " ";
//			outfile << str;
//		}
//		
//	}
//	infile.close();
//	outfile.close();
//	return;
//}



////@breif generate a qr code based on binary data
////@author shitaotao
////int generate_qrcode() {
////
////
////
////
////
////}