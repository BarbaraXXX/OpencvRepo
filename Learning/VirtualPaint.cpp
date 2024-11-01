#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

////////////////////////////Virtual Paint////////////////////////
vector<vector<int>> myColors{ {24, 26, 44, 74, 228, 134}	//Green
								};
vector<Scalar> myColorValues{ {0, 255, 0}				//The BGR code for Green
							};
const int MIN_AREA = 300;
vector<vector<int>> newPoints;			//存储每个点对应的位置以及要画的颜色

Point getContours(Mat mask, Mat img)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	
	
	findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	
	Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);

		if (area > MIN_AREA)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			
			boundRect[i] = boundingRect(conPoly[i]);

			//drawContours(img, conPoly, i, Scalar(255, 255, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(222, 24, 103), 2);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;
		}
	}
	return myPoint;
}

void drawOnCanvas(Mat img, vector<vector<int>> newPoints, vector<Scalar> myColorValues)
{
	for (int i = 0; i < newPoints.size(); i++)
	{
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 15, myColorValues[newPoints[i][2]], FILLED);
	}
}

vector<vector<int>> findColor(Mat img)
{
	Mat imgHSV, mask;

	//int hmin = 24, smin = 26, vmin = 44;
	//int hmax = 74, smax = 228, vmax = 134;

	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < myColors.size(); i++)		//确保每种颜色都画所以用循环
	{
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);

		inRange(imgHSV, lower, upper, mask);		//Get mask that have the wanted color
		//imshow(to_string(i), mask);
		Point myPoint;
		myPoint = getContours(mask, img);
		if (myPoint.x != 0 && myPoint.y != 0)
		{
			newPoints.push_back({ myPoint.x, myPoint.y, i });
		}
	}

	return newPoints;
	//找到对应的图形并画画
	//drawOnCanvas(img, newPoints, myColorValues);

	//imshow("img", img);
	//imshow("HSV", imgHSV);
	//imshow("mask", mask);
	//waitKey(1);

}


int main()
{
	VideoCapture cap(0);
	//string path = "resources/pen.png";
	//Mat img = imread(path);
	//imshow("img", img);
	//findColor(img);
	Mat img;
	while (true)
	{
		cap.read(img);

		newPoints = findColor(img);
		drawOnCanvas(img, newPoints, myColorValues);
		imshow("camera", img);
		waitKey(1);
	}
	waitKey(0);
	return 0;
}