#include"../head/Video.h"

using namespace cv;
using namespace std; 


//void Image_TO_Video(int number_of_frame)//图片转视频
//{
//	string s_image_name;
//	cv::VideoWriter writer;
//	int isColor = 1;//只向视频输入彩度图
//	int frame_fps = 30;//帧率
//	int frame_width = 660;   //必须是图像真实的分辨率，这不是指定生成视频的分辨率
//	int frame_height = 660;
//
//	string video_name = "output.mp4";//输出的视频名字和格式
//	writer = VideoWriter(video_name, VideoWriter::fourcc('D', 'I', 'V', 'X'), frame_fps, Size(frame_width, frame_height), isColor);//视频名字、编码格式、帧率、单帧图片大小、只输入彩度图
//	cout << "frame_width is " << frame_width << endl;
//	cout << "frame_height is " << frame_height << endl;
//	cout << "frame_fps is " << frame_fps << endl;
//	cv::namedWindow("image to video", WINDOW_AUTOSIZE);
//	int num = number_of_frame;//输入的图片总张数
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
//		s_image_name = path + "code" + std::to_string(i++) + ".jpg";//图片的名字
//		img = imread(s_image_name);//读入图片
//		if (!img.data)//判断图片调入是否成功
//		{
//			cout << "Could not load image file..." << endl;
//			system("pause");
//			break;
//		}
//		writer << img;
//		//imshow("image to video", img);
//		waitKey(1);
//
//		if (cv::waitKey(30) == 27 || i == num)//帧数达标或通过ESC提前结束生成
//		{
//			cout << "按下ESC键" << endl;
//			cvReleaseVideoWriter;
//			break;
//		}
//	}
//}

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
			cout << "不能从视频文件读取帧" << endl;
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
