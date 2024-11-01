#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


//////////////////////////////Draw shapes and text/////////////////////////////
int main()
{
	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));
	
	circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);

	//Rect参数：四个坐标，则表示长、宽、起点x,y;两个Point()则表示左上角右下角
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
	line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

	putText(img, "FoolZheng", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 69, 255), 2);
	imshow("White", img);
	waitKey(0);
	return 0;
}