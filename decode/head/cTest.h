#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

extern Mat extractedRect;
int RectSegmentation(const Mat& imgIn, Mat&);
int PreOperation(const Mat& imgIn);
int InContours(Mat& imgIn, Mat&);
int largestSquare(const vector<vector<Point>>& squares, vector<Point>& largest_square);
int rectExtract(vector<Point>& corners, Mat&);
double getAngle(Point pt0, Point pt1, Point pt2);