#include "../head/cTest.h"
Mat tmpImg, tmpImg2;
Mat grayImg;
vector<Point> largest_square;
static vector<vector<Point>> squaresExp, hullsExp;

double pointDist(Point pt1, Point pt2);
Point2f computeCorner(Vec4i line1, Vec4i line2);
void sortCorners(vector<Point>& points);

int RectSegmentation(const Mat& imgIn, Mat& output)
{
	tmpImg = imgIn;
	tmpImg2 = tmpImg.clone();
	PreOperation(tmpImg);
	InContours(grayImg, output);

	return 0;
}

int PreOperation(const Mat& imgIn)
{
	cvtColor(imgIn, grayImg, COLOR_BGR2GRAY);
	GaussianBlur(grayImg, grayImg, Size(3, 3), 0, 0, BORDER_DEFAULT);
	return 0;
}

int InContours(Mat& imgIn, Mat& output)
{
	Mat CannyImg;
	int threshLow = 35;
	Canny(imgIn, CannyImg, threshLow, 3 * threshLow, 3);

	dilate(CannyImg, CannyImg, Mat(), Point(-1, -1), 10, 1, Scalar(1));
	erode(CannyImg, CannyImg, Mat(), Point(-1, -1), 10, 1, Scalar(1));

	vector<vector<Point>> contoursExp;
	vector<Vec4i> hierarchyExp;
	findContours(CannyImg, contoursExp, hierarchyExp, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	Mat contourImg = tmpImg.clone();
	int i = 0;
	for (; i >= 0; i = hierarchyExp[i][0]) {
		drawContours(contourImg, contoursExp, i, Scalar(0, 255, 255), 2, 8, hierarchyExp);
	}
	vector<Point> hull, approx;
	for (size_t i = 0; i < contoursExp.size(); i++)
	{
		convexHull(contoursExp[i], hull);
		approxPolyDP(hull, approx, arcLength(hull, true)*0.02, true);

		if (approx.size() == 4 && fabs(contourArea(Mat(approx))) >= 40000 && isContourConvex(Mat(approx)))
		{
			double maxCosine = 0;
			for (int j = 2; j < 5; j++) {
				double tmpCosine = fabs(getAngle(approx[j % 4], approx[j - 2], approx[j - 1]));
				maxCosine = MAX(tmpCosine, maxCosine);
			}
			if (maxCosine <= 0.5) {
				squaresExp.push_back(approx);
				hullsExp.push_back(hull);
			}

		}

	}

	int index = largestSquare(squaresExp, largest_square);
	if (largest_square.size() == 0 || index == -1) return -1;
	hull = hullsExp[index];
	approxPolyDP(Mat(hull), approx, 3, true);
	vector<Point> newApprox;
	double maxDistance = arcLength(Mat(approx), true)*0.02;
	for (Point p : approx) {
		if (!(
			pointDist(p, largest_square[0]) > maxDistance&&
			pointDist(p, largest_square[1]) > maxDistance&&
			pointDist(p, largest_square[2]) > maxDistance&&
			pointDist(p, largest_square[3]) > maxDistance
			)) {
			newApprox.push_back(p);
		}

	}

	vector<Vec4i> lines;
	for (int i = 0; i < newApprox.size(); i++) {
		Point p1 = newApprox[i];
		Point p2 = newApprox[(i + 1) % newApprox.size()];
		if (pointDist(p1, p2) > 2 * maxDistance) {
			lines.push_back(Vec4i(p1.x, p1.y, p2.x, p2.y));

			line(grayImg, p1, p2, Scalar(255), 2, 8);
		}
	}

	vector<Point> corners1;
	for (int i = 0; i < lines.size(); i++) {
		Point corner = computeCorner(lines[i], lines[(i + 1) % lines.size()]);
		corners1.push_back(corner);
	}
	for (int i = 0; i < corners1.size(); i++) {
		circle(tmpImg2, corners1[i], 5, Scalar(255, 255, 255), -1);
		line(tmpImg2, corners1[i], corners1[(i + 1) % corners1.size()], Scalar(255, 0, 0), 1, 8);
	}

	//imshow("outPutImg", tmpImg2);//

	sortCorners(corners1);
	rectExtract(corners1, output);
	return 0;
}

double getAngle(Point pt0, Point pt1, Point pt2)
{
	double dx1 = pt0.x - pt2.x;
	double dy1 = pt0.y - pt2.y;
	double dx2 = pt1.x - pt2.x;
	double dy2 = pt1.y - pt2.y;
	double cos1 = (dx1*dx2 + dy1 * dy2) / sqrt((dx1*dx1 + dy1 * dy1)*(dx2*dx2 + dy2 * dy2) + 1e-10);
	return cos1;
}

int largestSquare(const vector<vector<Point>>& squares, vector<Point>& largest_square)
{
	if (!squares.size()) return -1;
	int maxWidth = 0;
	int maxHeight = 0;
	int maxIndex = 0;
	for (int i = 0; i < squares.size(); i++) {
		Rect rectangleIn = boundingRect(Mat(squares[i]));
		if ((rectangleIn.width >= maxWidth) && (rectangleIn.height >= maxHeight)) {
			maxWidth = rectangleIn.width;
			maxHeight = rectangleIn.height;
			maxIndex = i;
		}
	}
	largest_square = squares[maxIndex];
	return maxIndex;
}

double pointDist(Point pt1, Point pt2) {
	int a = pt1.x - pt2.x;
	int b = pt1.y - pt2.y;
	int c = a * a + b * b;
	return sqrt(c);
}

Point2f  computeCorner(Vec4i line1, Vec4i line2) {
	int x1 = line1[0], y1 = line1[1], x2 = line1[2], y2 = line1[3];
	int x3 = line2[0], y3 = line2[1], x4 = line2[2], y4 = line2[3];
	double d = ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
	if (d) {
		Point2f cornerIn;
		cornerIn.x = ((x1*y2 - x2 * y1)*(x3 - x4) - (x1 - x2)*(x3*y4 - x4 * y3)) / d;
		cornerIn.y = ((x1*y2 - x2 * y1)*(y3 - y4) - (y1 - y2)*(x3*y4 - x4 * y3)) / d;
		return cornerIn;
	}
	else
		return Point2f(-1, -1);
}

int rectExtract(vector<Point>& corners, Mat& output)
{
	sortCorners(corners);
	Point2f p0 = corners[0];
	Point2f p1 = corners[1];
	Point2f p2 = corners[2];
	Point2f p3 = corners[3];
	double space0 = pointDist(p0, p1);
	double space1 = pointDist(p1, p2);
	double space2 = pointDist(p2, p3);
	double space3 = pointDist(p3, p0);
	double imgWidth = space1 > space3 ? space1 : space3;
	double imgHeight = space0 > space2 ? space0 : space2;
	
	double paraFix1 = (space3 / space1) > 1 ? (space3 / space1) : (space1 / space3);
	double paraFix2 = (space2 / space0) > 1 ? (space2 / space0) : (space0 / space2);
	if (paraFix1 > paraFix2) imgHeight = imgHeight * paraFix1;
	else imgWidth = imgWidth * paraFix2;

	if (imgWidth < imgHeight) {
		double temp = imgWidth;
		imgWidth = imgHeight;
		imgHeight = temp;
		Point2f tempPoint = p0;
		p0 = p1;
		p1 = p2;
		p2 = p3;
		p3 = tempPoint;
	}

	vector<Point2f> cornersIn;
	cornersIn.push_back(p0);
	cornersIn.push_back(p1);
	cornersIn.push_back(p2);
	cornersIn.push_back(p3);
	Mat imgRect(imgHeight * 2, imgWidth * 2, CV_8UC3);
	vector<Point2f> rect_pts;
	rect_pts.push_back(Point2f(0, imgRect.rows));
	rect_pts.push_back(Point2f(0, 0));
	rect_pts.push_back(Point2f(imgRect.cols, 0));
	rect_pts.push_back(Point2f(imgRect.cols, imgRect.rows));

	Mat transmtx;
	transmtx = getPerspectiveTransform(cornersIn, rect_pts);
	warpPerspective(tmpImg, imgRect, transmtx, imgRect.size());
	//cout << "size" << (int)(imgRect.rows) << (int)(imgRect.cols) << endl;
	transpose(imgRect, imgRect);
	flip(imgRect, output, 1);
	//imshow("outPutimg", imgRect);
	return 0;
}

void sortCorners(vector<Point>& points) {
	if (points.size() == 0) return;
	Point pl = points[0];
	int index = 0;
	for (int i = 1; i < points.size(); i++)
	{
		Point point = points[i];
		if (pl.x > point.x)
		{
			pl = point;
			index = i;
		}
	}
	points[index] = points[0];
	points[0] = pl;
	Point lp = points[0];
	for (int i = 1; i < points.size(); i++)
	{
		for (int j = i + 1; j<points.size(); j++)
		{
			cv::Point point1 = points[i];
			cv::Point point2 = points[j];
			if ((point1.y - lp.y*1.0) / (point1.x - lp.x)>(point2.y - lp.y*1.0) / (point2.x - lp.x))
			{
				cv::Point temp = point1;
				points[i] = points[j];
				points[j] = temp;
			}
		}
	}

}