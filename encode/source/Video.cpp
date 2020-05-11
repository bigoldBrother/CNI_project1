#include"../head/Video.h"

using namespace cv;
using namespace std; 

//������ʼ֡ͼƬ
void Add_Head(string file)
{
	Mat scri(860, 860, CV_8UC3, Scalar(0, 0, 0));
	string filename;//�ļ���
		filename = file + "head.jpg";
		imwrite(filename, scri);
	
}

//������ֹ֡ͼƬ
void Add_Tail(string file)
{
	Mat scri(860, 860, CV_8UC3, Scalar(0, 0, 0));
	string filename;//�ļ���
	filename = file + "tail.jpg";
	imwrite(filename, scri);
}

//ͼƬת��Ƶ,����ͼƬ����������Ƶ�����ƣ������Ƶʱ��
void Image_TO_Video(int number_of_frame,string video_name,int max_video_length)
{
	
	cv::VideoWriter writer;
	int isColor = 1;//ֻ����Ƶ����ʶ�ͼ
	int frame_fps = 10;//֡��
	int frame_width = 860;   //������ͼ����ʵ�ķֱ��ʣ��ⲻ��ָ��������Ƶ�ķֱ���
	int frame_height = 860;
	int head_num = 5;//��ʼ֡����
	int tail_num = 5;//����֡����
	

	writer = VideoWriter(video_name, VideoWriter::fourcc('D', 'I', 'V', 'X'), frame_fps, Size(frame_width, frame_height), isColor);//��Ƶ���֡������ʽ��֡�ʡ���֡ͼƬ��С��ֻ����ʶ�ͼ
	cout << "frame_width is " << frame_width << endl;
	cout << "frame_height is " << frame_height << endl;
	cout << "frame_fps is " << frame_fps << endl;
	//cv::namedWindow("image to video", WINDOW_AUTOSIZE);
	int num = number_of_frame;//����Ķ�ά��������
	
	Mat img;
	Add_Head("./");//������ʼ֡
	Add_Tail("./");//���ɽ���֡

	if (!writer.isOpened())
	{
		cout << "Error : fail to open video writer" << endl;
		system("pause");
		return;
	}

	string s_image_name;//���ͼƬ����
	int i = 1;
	while (i <= head_num)//����ʼ֡������Ƶ
	{
		
		s_image_name = "head.jpg";//ͼƬ������
		img = imread(s_image_name);//����ͼƬ
		if (!img.data)//�ж�ͼƬ�����Ƿ�ɹ�
		{
			cout << "Could not load head image file..." << endl;
			system("pause");
			break;
		}
		writer << img;
		//imshow("image to video", img);
		i++;
	}
	i = 0;
	while (i <= num)//����ά�������Ƶ
	{
		//string path = "D:\\test_example\\";
		s_image_name =  "code" + std::to_string(i++) + ".jpg";//ͼƬ������
		img = imread(s_image_name);//����ͼƬ
		if (!img.data)//�ж�ͼƬ�����Ƿ�ɹ�
		{
			cout << "Could not load code image file..." << endl;
			system("pause");
			break;
		}
		writer << img;
		//imshow("image to video", img);
		

		
		if (cv::waitKey(30) == 27 || i == num||((i+head_num+tail_num)/frame_fps)*1000>max_video_length)//֡������ͨ��ESC��ǰ��������
		{	
			break;
		}
	}
	i = 1;
	while (i <= tail_num)//��15֡��ֹ֡������Ƶ
	{
		//string path = "D:\\test_example\\";
		s_image_name = "tail.jpg";//ͼƬ������
		img = imread(s_image_name);//����ͼƬ
		if (!img.data)//�ж�ͼƬ�����Ƿ�ɹ�
		{
			cout << "Could not load tail image file..." << endl;
			system("pause");
			break;
		}
		writer << img;
		//imshow("image to video", img);
		i++;
		if (i==tail_num)//֡�����
		{

			cvReleaseVideoWriter;
			break;
		}
	}
}

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
			//cout << "���ܴ���Ƶ�ļ���ȡ֡" << endl;
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

