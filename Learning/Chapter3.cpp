#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/////////////////////////////Resize and Crop/////////////////////////////////////////////////
int main_resize_and_crop()
{
	string path = "C:\\Users\\26310\\source\\repos\\OpencvLearning\\OpencvLearning\\Resources\\cards.jpg";
	Mat img = imread(path);
	Mat imgResize, imgCrop;

	//resize image
	cout << img.size() << endl;
	//img size: 1250 * 938
	//resize(img, imgResize, Size(640, 480));
	resize(img, imgResize, Size(), 0.5, 0.5);

	//crop image
	Rect roi(100, 100, 300, 250);
	imgCrop = img(roi);


	imshow("img", img);
	//imshow("resize", imgResize);
	imshow("crop", imgCrop);
	waitKey(0);
	return 0;
}