#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
//#include<opencv2/opencv.hpp>//如果要包含所有库
using namespace std;
using namespace cv;
/*
void main()
{
	//这一段程序实现：图像img -> ptr[][] -> 图像img2 的传递过程，即图像->二维数组->图像
	//
	int i = 0, j = 0;
	Mat img = imread("1.jpg", 0);//读取图像img。0表示转换为灰度图像读入
	int row = img.rows;
	int col = img.cols;
	//namedWindow("原图");
	//imshow("原图", img);

	Mat img2 = Mat(row, col, CV_8UC1);//图像img2：row*col大小  这里只是定义了img2图像的大小还没有传递图像的信息

	uchar** ptr = (uchar**)malloc(row * sizeof(uchar*));//二维数组ptr[][]
	for (i = 0; i < row; i++)
		ptr[i] = (uchar*)malloc(col * sizeof(uchar)); //第i行   有cols个列元素

	uchar* ptmp = NULL;//这是关键的指针！！   ptmp指针指向的是img2这个图像

	for (i = 0; i < row; i++)
	{
		ptmp = img2.ptr<uchar>(i);//指针指向img2的第i行
		for (j = 0; j < col; j++)
		{
			ptr[i][j] = img.at<uchar>(i, j);//img的矩阵数据传给二维数组ptr[][]  像素值传递
			ptmp[j] = ptr[i][j];//二维数组数据传给img2的第i行第j列
			cout << int(ptr[i][j]) << " ";
		}
		cout << endl;
	}
	//namedWindow("新图");
	//imshow("新图", img2);

	// 等待100000 ms后窗口自动关闭    
	//waitKey(100000);
}
*/