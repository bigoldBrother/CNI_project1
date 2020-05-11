#include"../head/decode1.h"
#include"../head/cTest.h"
using namespace cv;
using namespace std;
const int image_height = 66;
const int image_length = 66;
int number_wrong_count = 0;//��¼��ǰ��������֡��

void ConvertIntoPoint(int  img[64][64][2], int height, int width)
{
	//x_leftup = 0, y_leftup = 0�����Ͻǵ�����,default=0 
	int x_leftup = 0; int y_leftup = 0;
	float dx = (float)width / (float)image_length;//����Ĳ���
	float dy = (float)height / (float)image_height;//����Ĳ���
	//���Ͻǵĸ���
	float x_location = x_leftup + 3 * dx / 2.0;
	float y_location = y_leftup + 3 * dy / 2.0;
	//�Ѹ������ӵ���Ϣ��������img
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

//���뺯��������ɹ����뷵��true�������������֡�򷵻�false
bool decode(string filename,string& raw_data,int& code_count)
{

	Mat gray_src;
	Mat src = imread(filename);//�ļ���Ҫ�޸�


	if (src.empty())
	{
		cout << "ͼ��δ�ҵ�" << endl;
		return -1;
	}
	//imshow("input Image", src);

	cvtColor(src, gray_src, CV_BGR2GRAY);
	//imshow("gray Image", gray_src);

	//------------��ֵ������-------------
	Mat binary;
	threshold(gray_src, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	//imshow("binary Image", binary);

	//---------------��̬ѧ����-------------
	Mat dst;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	erode(binary, dst, kernel, Point(-1, -1), 1);//1��ʾ����1��
	//bitwise_not(dst, dst);
	//imshow("erode Image", dst);

	//---------------��������----------------
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(-1, -1));

	//---------------��������-----------------
	int height = src.rows;
	int width = src.cols;
	Mat drawImg = Mat::zeros(src.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Rect rect = boundingRect(contours[i]); //��ȡ��С��Ӿ���

		if (rect.width > width / 3 && rect.width < (2 * width) / 3 && rect.height>3 * height / 5 && rect.height < height)
		{
			drawContours(drawImg, contours, static_cast<int>(i),
				Scalar(0, 0, 255), 2, 8, hierarchy, 0, Point());
		}
	}
	//imshow("drawContours Image", drawImg);

	//����ֱ�߼��
	Mat houghImg;
	cvtColor(drawImg, houghImg, CV_BGR2GRAY);
	vector<Vec4i> lines;
	//int accu = min(width/2,height/2);
	HoughLinesP(houghImg, lines, 1, CV_PI / 180.0, 30, 100, 0);
	Mat linesImg = Mat::zeros(src.size(), CV_8UC3);

	//�ų�������֡
	if (lines.size() == 0)
	{
		cout <<filename<<" "<< "������֡" << endl;
		return false;
	}
	
	Mat output;
	Mat grayImage;
	RectSegmentation(src, output);
	cvtColor(output, grayImage, CV_BGR2GRAY);//ʹͼ��ת��Ϊ�Ҷ�ͼ������grayImage


		//threshold(grayImage, thresholdImage, 0, 255, THRESH_OTSU + THRESH_BINARY);//����͸�ӱ任�Ժ󣬶�grayImageִ�ж�ֵ��

		//��ÿ�������е����ص������
		int img[64][64][2];
		width = grayImage.rows;
		height = grayImage.cols;
		ConvertIntoPoint(img, width, height);

		//��ÿ���������صĻҶ�ֵ
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
			//�����λ����ÿʮ��λ������һλ��ʼ����
			for (int j = 16 * i - 1; j >= 16 * (i-1); j--)
			{
				int x = pow(2, up++);//x���������תʮ������2�ļ��η���up����2�Ĵη�
				page_number[i-1] = page_number[i-1] + decode[0][j] * x;
			}
		}

		int count = 0;//��¼������ȷ��ŵĴ���
		for (int i = 0; i < 4; i++) {
			if (page_number[i] == code_count) //ÿ�����ּ�����ı�ŵ��ڵ�ǰ��ŵ������������һ��
				count++;
		}

		
		if (count >= 1) {//�����������ڵ���1����Ϊ����֡������Я������¼��,���򷵻�
			
			for (int k = 1; k < 64; k++) {//�ӵڶ��п�ʼ������������
				for (int i = 1; i <= 8; i++)//��ÿһ��ת��Ϊ8���ֽ������ļ���
				{
					char ch = 0;
					int up = 0;
					//�����λ����ÿ8λ������һλ��ʼ����
					for (int j = 8 * i - 1; j >= 8 * (i - 1); j--)
					{
						int x = pow(2, up++);//x���������תʮ������2�ļ��η���up����2�Ĵη�
						ch = ch + decode[k][j] * x;
					}
					raw_data.push_back(ch);
				}
			}
			code_count++;
			number_wrong_count = 0;
			cout <<code_count<<" " << filename << " "<< "����ɹ���" << endl;
			return true;
			
		}

		cout <<code_count << " " << filename << " " <<"��ά���Ŵ���" << endl;
		number_wrong_count++;
		if (number_wrong_count >= 10) {
			code_count++;
			number_wrong_count = 0;
			
			
		}
		return false;
}
