#include"../head/Video.h"

using namespace cv;
using namespace std; 


//void Image_TO_Video(int number_of_frame)//ͼƬת��Ƶ
//{
//	string s_image_name;
//	cv::VideoWriter writer;
//	int isColor = 1;//ֻ����Ƶ����ʶ�ͼ
//	int frame_fps = 30;//֡��
//	int frame_width = 660;   //������ͼ����ʵ�ķֱ��ʣ��ⲻ��ָ��������Ƶ�ķֱ���
//	int frame_height = 660;
//
//	string video_name = "output.mp4";//�������Ƶ���ֺ͸�ʽ
//	writer = VideoWriter(video_name, VideoWriter::fourcc('D', 'I', 'V', 'X'), frame_fps, Size(frame_width, frame_height), isColor);//��Ƶ���֡������ʽ��֡�ʡ���֡ͼƬ��С��ֻ����ʶ�ͼ
//	cout << "frame_width is " << frame_width << endl;
//	cout << "frame_height is " << frame_height << endl;
//	cout << "frame_fps is " << frame_fps << endl;
//	cv::namedWindow("image to video", WINDOW_AUTOSIZE);
//	int num = number_of_frame;//�����ͼƬ������
//	int i = 1;
//	Mat img;
//
//
//	if (!writer.isOpened())
//	{
//		cout << "Error : fail to open video writer" << endl;
//		system("pause");
//		return;
//	}
//
//
//	while (i <= num)//
//	{
//		string path = "D:\\test_example\\";
//		s_image_name = path + "code" + std::to_string(i++) + ".jpg";//ͼƬ������
//		img = imread(s_image_name);//����ͼƬ
//		if (!img.data)//�ж�ͼƬ�����Ƿ�ɹ�
//		{
//			cout << "Could not load image file..." << endl;
//			system("pause");
//			break;
//		}
//		writer << img;
//		//imshow("image to video", img);
//		waitKey(1);
//
//		if (cv::waitKey(30) == 27 || i == num)//֡������ͨ��ESC��ǰ��������
//		{
//			cout << "����ESC��" << endl;
//			cvReleaseVideoWriter;
//			break;
//		}
//	}
//}

//��ƵתͼƬ
int Video_TO_Image(string filename)
{
	cv::VideoCapture capture(filename);
	if (!capture.isOpened())
	{
		cout << "open video error";
	}
	/*CV_CAP_PROP_POS_MSEC �C ��Ƶ�ĵ�ǰλ�ã����룩
	CV_CAP_PROP_POS_FRAMES �C ��Ƶ�ĵ�ǰλ�ã�֡��
	CV_CAP_PROP_FRAME_WIDTH �C ��Ƶ���Ŀ��
	CV_CAP_PROP_FRAME_HEIGHT �C ��Ƶ���ĸ߶�
	CV_CAP_PROP_FPS �C ֡���ʣ�֡ / �룩*/
	int frame_width = (int)capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = (int)capture.get(CAP_PROP_FRAME_HEIGHT);
	float frame_fps = capture.get(CAP_PROP_FPS);
	//int frame_number = capture.get(CAP_PROP_FRAME_COUNT);//��֡��
	//cout << "frame_width is " << frame_width << endl;
	//cout << "frame_height is " << frame_height << endl;
	//cout << "frame_fps is " << frame_fps << endl;

	int num = 0;//ͳ��֡��
	cv::Mat img;
	string img_name;
	char image_name[20];
	//cv::namedWindow("MyVideo", WINDOW_AUTOSIZE);//����һ�����ڲ�����Ƶ
	while (true)
	{
		cv::Mat frame;
		//����Ƶ�ж�ȡһ��֡
		bool bSuccess = capture.read(frame);
		if (!bSuccess)
		{
			cout << "���ܴ���Ƶ�ļ���ȡ֡" << endl;
			break;
		}
		//��MyVideo��������ʾ��ǰ֡
		//imshow("MyVideo", frame);
		//�����ͼƬ��
		//sprintf(const_cast<char*>(img_name.data()), "%s%d%s", "image", ++num, ".jpg");//�����ͼƬ��
		Size size = Size(832,624);//����ͼƬ��С
		resize(frame, img, size);//����ͼƬ��С
		sprintf_s(image_name, "%s%d%s", "image", ++num, ".jpg");//�����ͼƬ��
		img_name = image_name;
		imwrite(img_name, img);//����һ֡ͼƬ
		if (cv::waitKey(30) == 27)//��Ƶ̫����ֻ����num==300ʱ�����߰���ESC��ǰ�˳�
		{
			cout << "����ESC��" << endl;
			break;
		}
	}
	capture.release();
	return num;
}
