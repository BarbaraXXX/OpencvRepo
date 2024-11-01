#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat imgWarp;
Mat preProcessing(Mat imgOriginal)
{
	Mat imgThresh, imgBlur, imgDil, imgGray, imgCanny;
	cvtColor(imgOriginal, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(5, 5), 3, 0);
	Canny(imgBlur, imgCanny, 15, 45);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	imshow("Dil", imgDil);
	return imgDil;
}

vector<Point> getContours(Mat image)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	
	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	int maxArea = 0;
	vector<Point> biggest;
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);

		if (area > 250)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			if (area > maxArea && conPoly[i].size() == 4)
			{
				biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] }; 
				maxArea = area;
			}

		}
	}

	//如果没有检测到，随便画一个
	if (biggest.size() != 4)
	{
		biggest = { {0, 0}, {100, 0}, {0, 100}, {100, 100} };
		return biggest;
	}
	else
	{
		return biggest;
	}

}

void DrawPoints(Mat img, vector<Point> points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(img, points[i], 5, color, FILLED);
		putText(img, to_string(i), points[i], FONT_HERSHEY_PLAIN, 3, color, 5);
	}
}

vector<Point> reorder(vector<Point> points)
{
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;

	for (int i = 0; i < 4; i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}
	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); 
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
	
	return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h)
{
	Point2f src[4] = { points[0], points[1], points[2], points[3] };
	Point2f dst[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };
	Mat matrix = getPerspectiveTransform(src, dst);

	warpPerspective(img, imgWarp, matrix, Point(w, h));
	return imgWarp;
}


void UseCam()
{
	Mat imgOriginal, imgThresh, imgCrop;
	vector<Point> initialPoints, docPoints;
	float w = 420 * 1.5, h = 596 * 1.5;

	VideoCapture cap(0);

	while (true)
	{
		cap.read(imgOriginal);
		//resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
		//cout << "****************************" << imgOriginal.rows << "||" << imgOriginal.cols << endl;
		// camera definition: 640 * 480
		//preprocessing
		imgThresh = preProcessing(imgOriginal);

		//Get contours - Biggest
		initialPoints = getContours(imgThresh);
		//cout << initialPoints << endl;

		//DrawPoints(imgOriginal, initialPoints, Scalar(0, 0, 255));
		docPoints = reorder(initialPoints);
		DrawPoints(imgOriginal, docPoints, Scalar(0, 0, 255));

		//Warp
		imgWarp = getWarp(imgOriginal, docPoints, w, h);

		//Crop
		Rect roi(5, 5, w - 10, h - 10);
		imgCrop = imgWarp(roi);

		
		imshow("img", imgOriginal);
		imshow("imgWarp", imgWarp);
		imshow("imgCrop", imgCrop);
		waitKey(1);
	}
}

int main()
{
	//Mat imgOriginal, imgThresh, imgCrop;
	//vector<Point> initialPoints, docPoints;
	//float w = 420, h = 596;
	//string path = "Resources/paper.jpg";
	//imgOriginal = imread(path);
	////resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

	////preprocessing
	//imgThresh = preProcessing(imgOriginal);

	////Get contours - Biggest
	//initialPoints = getContours(imgThresh);
	//cout << initialPoints << endl;

	// //DrawPoints(imgOriginal, initialPoints, Scalar(0, 0, 255));
	//docPoints = reorder(initialPoints);
	////DrawPoints(imgOriginal, docPoints, Scalar(0, 0, 255));

	////Warp
	//imgWarp = getWarp(imgOriginal, docPoints, w, h);

	////Crop
	//Rect roi(5, 5, w - 10, h - 10);
	//imgCrop = imgWarp(roi);

	//imshow("img", imgOriginal);
	//imshow("imgWarp", imgWarp);
	//imshow("imgCrop", imgCrop);

	UseCam();

	waitKey(0);
	return 0;
}