#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
//#include<opencv2/opencv.hpp>//���Ҫ�������п�
using namespace std;
using namespace cv;
/*
void main()
{
	//��һ�γ���ʵ�֣�ͼ��img -> ptr[][] -> ͼ��img2 �Ĵ��ݹ��̣���ͼ��->��ά����->ͼ��
	//
	int i = 0, j = 0;
	Mat img = imread("1.jpg", 0);//��ȡͼ��img��0��ʾת��Ϊ�Ҷ�ͼ�����
	int row = img.rows;
	int col = img.cols;
	//namedWindow("ԭͼ");
	//imshow("ԭͼ", img);

	Mat img2 = Mat(row, col, CV_8UC1);//ͼ��img2��row*col��С  ����ֻ�Ƕ�����img2ͼ��Ĵ�С��û�д���ͼ�����Ϣ

	uchar** ptr = (uchar**)malloc(row * sizeof(uchar*));//��ά����ptr[][]
	for (i = 0; i < row; i++)
		ptr[i] = (uchar*)malloc(col * sizeof(uchar)); //��i��   ��cols����Ԫ��

	uchar* ptmp = NULL;//���ǹؼ���ָ�룡��   ptmpָ��ָ�����img2���ͼ��

	for (i = 0; i < row; i++)
	{
		ptmp = img2.ptr<uchar>(i);//ָ��ָ��img2�ĵ�i��
		for (j = 0; j < col; j++)
		{
			ptr[i][j] = img.at<uchar>(i, j);//img�ľ������ݴ�����ά����ptr[][]  ����ֵ����
			ptmp[j] = ptr[i][j];//��ά�������ݴ���img2�ĵ�i�е�j��
			cout << int(ptr[i][j]) << " ";
		}
		cout << endl;
	}
	//namedWindow("��ͼ");
	//imshow("��ͼ", img2);

	// �ȴ�100000 ms�󴰿��Զ��ر�    
	//waitKey(100000);
}
*/