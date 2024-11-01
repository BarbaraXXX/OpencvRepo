#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//int main_test_opencv()
//{
//	std::cout << "OpenCV test" << std::endl;
//
//	cv::Mat img = cv::imread("C:\\Users\\26310\\source\\repos\\OpencvLearning\\OpencvLearning\\Resources\\cards.jpg"); //更换为自己的图片地址
//
//	if (img.empty())
//	{
//		std::cerr << "Fail to open image." << std::endl;
//		return -1;
//	}
//
//	cv::imshow("img", img);
//	cv::waitKey();
//
//	return 0;
//}


//////////////////////////////////////////Chapter 1////////////////////////////////////////////////////////////

//Show Image
int main_show_image()
{
	std::string path = "C:\\Users\\26310\\source\\repos\\OpencvLearning\\OpencvLearning\\Resources\\test.png";
	cv::Mat img = cv::imread(path);
	cv::imshow("Image", img);
	cv::waitKey(0);
	return 0;
}


//Show Video
void main_show_video()
{
	std::string path = "C:\\Users\\26310\\source\\repos\\OpencvLearning\\OpencvLearning\\Resources\\test_video.mp4";
	cv::VideoCapture cap(path);
	cv::Mat img;
	while (true)
	{
		cap.read(img);
		cv::imshow("Video", img);
		cv::waitKey(3);
	}
}


//Show camera
int main_test_camera()
{
	cv::VideoCapture cap(0);
	cv::Mat img;
	while (true)
	{
		cap.read(img);
		cv::imshow("camera", img);
		cv::waitKey(5);
	}
}


//////////////////////////////////////////Chpater 2:basic function//////////////////////////////////////////////

