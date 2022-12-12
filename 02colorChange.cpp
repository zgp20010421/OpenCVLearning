#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{

	string path = "Resources/ml.png";
	Mat img = imread(path);
	Mat imgRGB, imgYUV, imgHSV, imgLab, imgGRAY;

	cvtColor(img, imgRGB, COLOR_BGR2RGB);

	// YUV模型是电视信号系统所采用的的颜色编码方式。
	// Y:表示亮度	U：表示红色与亮度的差值 V：表示蓝色与亮度的差值
	cvtColor(img, imgYUV, COLOR_BGR2YUV);

	/*
	HSV是色度（Hua），饱和度（Saturation），亮度（Value）
	*/

	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	/*
	Lab颜色模型就是补足RGB模型的不足，是一种设备无关的颜色模型
	L表示亮度  a，b两通道值
	*/

	cvtColor(img, imgLab, COLOR_BGR2Lab);

	/*
		灰度图像
	*/

	cvtColor(img, imgGRAY, COLOR_BGR2GRAY);

	imshow("img", img);
	imshow("imgRGB", imgRGB);
	imshow("imgYUV", imgYUV);
	imshow("imgHSV", imgHSV);
	imshow("imgLab", imgLab);
	imshow("imgGRAY", imgGRAY);



	waitKey(0);
	destroyAllWindows();

	return 0;
}