#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

////////////////////////////////////Shapes Dectection//////////////////////
void getContours(Mat imgDil, Mat img)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;


	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//findContours函数返回值为向量，其成员为Point的向量。{{Point(), Point(), ..}, {Point(), Point, ..}, {Point(), Point, ..}..}

	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
	//画出边界
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		cout << area << endl;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			cout << conPoly[i].size() << endl;

			//finding bounding box
			boundRect[i] = boundingRect(conPoly[i]);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);

			//int objCor = (int)conPoly[i].size();
			//aspRation:长宽比
		}
	}
}

int main()
{
	string path = "C:\\Users\\26310\\source\\repos\\OpencvLearning\\OpencvLearning\\Resources\\shapes.png";
	Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny, imgDil;

	//Canny计算边界，contour获取边界
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);

	imshow("img", img);
	imshow("Dil", imgDil);
	waitKey(0);
	return 0;
}