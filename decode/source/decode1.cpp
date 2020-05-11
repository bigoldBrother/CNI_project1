#include"../head/decode1.h"
#include"../head/cTest.h"
using namespace cv;
using namespace std;
const int image_height = 66;
const int image_length = 66;
int number_wrong_count = 0;//记录当前编码出错的帧数

void ConvertIntoPoint(int  img[64][64][2], int height, int width)
{
	//x_leftup = 0, y_leftup = 0给左上角的坐标,default=0 
	int x_leftup = 0; int y_leftup = 0;
	float dx = (float)width / (float)image_length;//横向的步长
	float dy = (float)height / (float)image_height;//纵向的步长
	//左上角的格子
	float x_location = x_leftup + 3 * dx / 2.0;
	float y_location = y_leftup + 3 * dy / 2.0;
	//把各个格子的信息存入数组img
	for (int i = 0; i < 64; i++)
	{
		float y_currentlocation = y_location + dy * i;
		float x_currentlocation = x_location;
		for (int j = 0; j < 64; j++)
		{
			img[i][j][0] = (int)x_currentlocation;
			img[i][j][1] = (int)y_currentlocation;
			x_currentlocation += dx;
		}
	}
	return;
}

//解码函数，如果成功解码返回true，如果不是内容帧则返回false
bool decode(string filename,string& raw_data,int& code_count)
{

	Mat gray_src;
	Mat src = imread(filename);//文件名要修改


	if (src.empty())
	{
		cout << "图像未找到" << endl;
		return -1;
	}
	//imshow("input Image", src);

	cvtColor(src, gray_src, CV_BGR2GRAY);
	//imshow("gray Image", gray_src);

	//------------二值化操作-------------
	Mat binary;
	threshold(gray_src, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	//imshow("binary Image", binary);

	//---------------形态学操作-------------
	Mat dst;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	erode(binary, dst, kernel, Point(-1, -1), 1);//1表示迭代1次
	//bitwise_not(dst, dst);
	//imshow("erode Image", dst);

	//---------------轮廓发现----------------
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(-1, -1));

	//---------------轮廓绘制-----------------
	int height = src.rows;
	int width = src.cols;
	Mat drawImg = Mat::zeros(src.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Rect rect = boundingRect(contours[i]); //获取最小外接矩形

		if (rect.width > width / 3 && rect.width < (2 * width) / 3 && rect.height>3 * height / 5 && rect.height < height)
		{
			drawContours(drawImg, contours, static_cast<int>(i),
				Scalar(0, 0, 255), 2, 8, hierarchy, 0, Point());
		}
	}
	//imshow("drawContours Image", drawImg);

	//霍夫直线检测
	Mat houghImg;
	cvtColor(drawImg, houghImg, CV_BGR2GRAY);
	vector<Vec4i> lines;
	//int accu = min(width/2,height/2);
	HoughLinesP(houghImg, lines, 1, CV_PI / 180.0, 30, 100, 0);
	Mat linesImg = Mat::zeros(src.size(), CV_8UC3);

	//排除非内容帧
	if (lines.size() == 0)
	{
		cout <<filename<<" "<< "非内容帧" << endl;
		return false;
	}
	
	Mat output;
	Mat grayImage;
	RectSegmentation(src, output);
	cvtColor(output, grayImage, CV_BGR2GRAY);//使图像转换为灰度图，存入grayImage


		//threshold(grayImage, thresholdImage, 0, 255, THRESH_OTSU + THRESH_BINARY);//改用透视变换以后，对grayImage执行二值化

		//求每个格子中的像素点的坐标
		int img[64][64][2];
		width = grayImage.rows;
		height = grayImage.cols;
		ConvertIntoPoint(img, width, height);

		//求每个格子像素的灰度值
		int intensity[64][64];
		int decode[64][64];
		for (int i = 0; i < 64; i++)
		{
			for (int j = 0; j < 64; j++)
			{

				int col = img[i][j][0];
				int row = img[i][j][1];

				uchar *pValue = grayImage.ptr<uchar>(row);

				intensity[i][j] = pValue[col];

				
				if (intensity[i][j] >= 128)//white
				{
					decode[i][j] = 0;

					//std::cout << decode[i][j];
				}
				if (intensity[i][j] < 128)//black

				{
					decode[i][j] = 1;

					//std::cout << decode[i][j];

				}

			}
			//std::cout << endl;
		}
		
		int page_number[4] = {0,0,0,0};
		
		for (int i = 4; i >=1; i--)
		{
			int up = 0;
			//从最低位，即每十六位的最右一位开始计算
			for (int j = 16 * i - 1; j >= 16 * (i-1); j--)
			{
				int x = pow(2, up++);//x代表二进制转十进制中2的几次方，up代表2的次方
				page_number[i-1] = page_number[i-1] + decode[0][j] * x;
			}
		}

		int count = 0;//记录出现正确编号的次数
		for (int i = 0; i < 4; i++) {
			if (page_number[i] == code_count) //每当出现计算出的编号等于当前编号的情况，计数加一。
				count++;
		}

		
		if (count >= 1) {//若最后计数大于等于1，视为正常帧，将其携带数据录入,否则返回
			
			for (int k = 1; k < 64; k++) {//从第二行开始遍历整个数组
				for (int i = 1; i <= 8; i++)//将每一行转换为8个字节输入文件中
				{
					char ch = 0;
					int up = 0;
					//从最低位，即每8位的最右一位开始计算
					for (int j = 8 * i - 1; j >= 8 * (i - 1); j--)
					{
						int x = pow(2, up++);//x代表二进制转十进制中2的几次方，up代表2的次方
						ch = ch + decode[k][j] * x;
					}
					raw_data.push_back(ch);
				}
			}
			code_count++;
			number_wrong_count = 0;
			cout <<code_count<<" " << filename << " "<< "解码成功！" << endl;
			return true;
			
		}

		cout <<code_count << " " << filename << " " <<"二维码编号错误！" << endl;
		number_wrong_count++;
		if (number_wrong_count >= 10) {
			code_count++;
			number_wrong_count = 0;
			
			
		}
		return false;
}
