#include"../head/Video.h"

using namespace cv;
using namespace std; 

//生成起始帧图片
void Add_Head(string file)
{
	Mat scri(860, 860, CV_8UC3, Scalar(0, 0, 0));
	string filename;//文件名
		filename = file + "head.jpg";
		imwrite(filename, scri);
	
}

//生成终止帧图片
void Add_Tail(string file)
{
	Mat scri(860, 860, CV_8UC3, Scalar(0, 0, 0));
	string filename;//文件名
	filename = file + "tail.jpg";
	imwrite(filename, scri);
}

//图片转视频,传入图片数，生成视频的名称，最大视频时长
void Image_TO_Video(int number_of_frame,string video_name,int max_video_length)
{
	
	cv::VideoWriter writer;
	int isColor = 1;//只向视频输入彩度图
	int frame_fps = 10;//帧率
	int frame_width = 860;   //必须是图像真实的分辨率，这不是指定生成视频的分辨率
	int frame_height = 860;
	int head_num = 5;//起始帧数量
	int tail_num = 5;//结束帧数量
	

	writer = VideoWriter(video_name, VideoWriter::fourcc('D', 'I', 'V', 'X'), frame_fps, Size(frame_width, frame_height), isColor);//视频名字、编码格式、帧率、单帧图片大小、只输入彩度图
	cout << "frame_width is " << frame_width << endl;
	cout << "frame_height is " << frame_height << endl;
	cout << "frame_fps is " << frame_fps << endl;
	//cv::namedWindow("image to video", WINDOW_AUTOSIZE);
	int num = number_of_frame;//输入的二维码总张数
	
	Mat img;
	Add_Head("./");//生成起始帧
	Add_Tail("./");//生成结束帧

	if (!writer.isOpened())
	{
		cout << "Error : fail to open video writer" << endl;
		system("pause");
		return;
	}

	string s_image_name;//存放图片名称
	int i = 1;
	while (i <= head_num)//将起始帧编入视频
	{
		
		s_image_name = "head.jpg";//图片的名字
		img = imread(s_image_name);//读入图片
		if (!img.data)//判断图片调入是否成功
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
	while (i <= num)//将二维码编入视频
	{
		//string path = "D:\\test_example\\";
		s_image_name =  "code" + std::to_string(i++) + ".jpg";//图片的名字
		img = imread(s_image_name);//读入图片
		if (!img.data)//判断图片调入是否成功
		{
			cout << "Could not load code image file..." << endl;
			system("pause");
			break;
		}
		writer << img;
		//imshow("image to video", img);
		

		
		if (cv::waitKey(30) == 27 || i == num||((i+head_num+tail_num)/frame_fps)*1000>max_video_length)//帧数达标或通过ESC提前结束生成
		{	
			break;
		}
	}
	i = 1;
	while (i <= tail_num)//将15帧终止帧编入视频
	{
		//string path = "D:\\test_example\\";
		s_image_name = "tail.jpg";//图片的名字
		img = imread(s_image_name);//读入图片
		if (!img.data)//判断图片调入是否成功
		{
			cout << "Could not load tail image file..." << endl;
			system("pause");
			break;
		}
		writer << img;
		//imshow("image to video", img);
		i++;
		if (i==tail_num)//帧数达标
		{

			cvReleaseVideoWriter;
			break;
		}
	}
}

//视频转图片
int Video_TO_Image(string filename)
{
	cv::VideoCapture capture(filename);
	if (!capture.isOpened())
	{
		cout << "open video error";
	}
	/*CV_CAP_PROP_POS_MSEC – 视频的当前位置（毫秒）
	CV_CAP_PROP_POS_FRAMES – 视频的当前位置（帧）
	CV_CAP_PROP_FRAME_WIDTH – 视频流的宽度
	CV_CAP_PROP_FRAME_HEIGHT – 视频流的高度
	CV_CAP_PROP_FPS – 帧速率（帧 / 秒）*/
	int frame_width = (int)capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = (int)capture.get(CAP_PROP_FRAME_HEIGHT);
	float frame_fps = capture.get(CAP_PROP_FPS);
	//int frame_number = capture.get(CAP_PROP_FRAME_COUNT);//总帧数
	//cout << "frame_width is " << frame_width << endl;
	//cout << "frame_height is " << frame_height << endl;
	//cout << "frame_fps is " << frame_fps << endl;

	int num = 0;//统计帧数
	cv::Mat img;
	string img_name;
	char image_name[20];
	//cv::namedWindow("MyVideo", WINDOW_AUTOSIZE);//建立一个窗口播放视频
	while (true)
	{
		cv::Mat frame;
		//从视频中读取一个帧
		bool bSuccess = capture.read(frame);
		if (!bSuccess)
		{
			//cout << "不能从视频文件读取帧" << endl;
			break;
		}
		//在MyVideo窗口上显示当前帧
		//imshow("MyVideo", frame);
		//保存的图片名
		//sprintf(const_cast<char*>(img_name.data()), "%s%d%s", "image", ++num, ".jpg");//保存的图片名
		Size size = Size(832,624);//重置图片大小
		resize(frame, img, size);//重置图片大小
		sprintf_s(image_name, "%s%d%s", "image", ++num, ".jpg");//保存的图片名
		img_name = image_name;
		imwrite(img_name, img);//保存一帧图片
		if (cv::waitKey(30) == 27)//视频太大，我只读到num==300时，或者按下ESC提前退出
		{
			cout << "按下ESC键" << endl;
			break;
		}
	}
	capture.release();
	return num;
}

