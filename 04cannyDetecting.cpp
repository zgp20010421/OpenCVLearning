#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	system("color F9");
	string path = "Resources/lena.jpg";
	
	Mat img;

	img = imread(path);
	
	// 1.将彩色的图像变为灰色图像(0,255)
	Mat imgGray;
	// cvtColor(输入图像，输出图像，改变成什么颜色)
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	// 2.将灰色图像进行高斯模糊,高斯滤波器
	Mat imgBlur;
	Size size(3, 3);
	// GaussianBlur（输入图像，输出图像，高斯模糊的大小，横向，纵向）
	GaussianBlur(imgGray, imgBlur, size, 3, 0);

	// 3.将高斯模糊的图像进行canny边缘检测
	Mat imgCanny;
	// Canny(输入图像（灰色图像，单通道的图像），输出图像，取值:0--255)
	// 找到图像的边缘处，过滤掉不需要的背景
	Canny(imgBlur, imgCanny, 75, 125);

	// 4.将canny边缘检测后的图像进行扩大
	// matrix 矩阵
	Mat imgDilate;
	
	// kerner 内核
	// size(3,3)，（5，5）。只能是奇数
	// getStructuringElement（矩形类型，扩大核的大小）
	Mat kerner = getStructuringElement(MORPH_RECT, size);

	// dilate（输入图像（Canny）,输出图像，内核）
	dilate(imgCanny, imgDilate, kerner);

	// 5.进行腐蚀 erode
	Mat imgErode;
	// erode(输入图像，输出图像，内核大小)
	erode(imgDilate, imgErode, kerner);

	// 图像重定义大小

	//resize(img,img,Size(0,0),0.5,0.5);
	/*int width = int(img.rows / 2); // 图像的宽
	int height = int(img.cols / 2); // 图像的高
	resize(img, img, Size(width, height));*/

	// reszie(输入图像，输出图像，图像大小（宽和高），宽，高）
	resize(img, img, Size(0, 0), 0.5, 0.5);
	resize(imgGray, imgGray, Size(0, 0), 0.5, 0.5);
	resize(imgBlur, imgBlur, Size(0, 0), 0.5, 0.5);
	resize(imgCanny, imgCanny, Size(0, 0), 0.5, 0.5);
	resize(imgDilate, imgDilate, Size(0, 0), 0.5, 0.5);
	resize(imgErode, imgErode, Size(0, 0), 0.5, 0.5);

	imshow("img", img);
	imshow("imgGray", imgGray);
	imshow("imgBlur", imgBlur);
	imshow("imgCanny", imgCanny);
	imshow("imgDilate", imgDilate);
	imshow("imgErode", imgErode);

	waitKey(0);
	destroyAllWindows();

	return 0;
}