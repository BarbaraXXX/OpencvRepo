#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;
int main_basic_function()
{
	std::string path = "C:\\Users\\26310\\source\\repos\\OpencvLearning\\OpencvLearning\\Resources\\cards.jpg";
	cv::Mat img = cv::imread(path);
	cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
	
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);		//ת�Ҷ�ͼ

	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);		//��˹ģ��

	Canny(imgBlur, imgCanny, 25, 75);		//�߽�

	//����	dilate����ǿ����
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	//��ʴ  erode�� ��������
	erode(imgDil, imgErode, kernel);

	//imshow("color", img);
	//imshow("Gray", imgGray);
	//imshow("GaussianBlur", imgBlur);
	imshow("Canny", imgCanny);
	imshow("dilate", imgDil);
	imshow("erode", imgErode);
	waitKey(0);
	return 0;
}