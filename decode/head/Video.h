#pragma once
#include <iostream>  
#include<stdlib.h>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include<opencv2/opencv.hpp>//如果要包含所有库

using namespace cv;
using namespace std;

void Image_TO_Video(int number_of_frame);
int Video_TO_Image(string filemane);