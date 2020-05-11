#include <stdio.h>   
#include <time.h>  
#include <opencv2/opencv.hpp>   
#include <iostream> 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2\imgproc\types_c.h>
#include "bits.h"
#include <string> 
#include <fstream> 

using namespace std;

bool decode(string filename,string& raw_data,int& code_count);
void ConvertIntoPoint(int  img[64][64][2], int height, int width);
void ConvertBatToText();