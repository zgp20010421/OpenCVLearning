#include <opencv2\opencv.hpp>
#include <iostream>


using namespace std;
using namespace cv;

// 用HSV颜色空间进行颜色检测
/*
	Hue:颜色的饱和度
	Saturation: 颜色的亮度 
	Value: 颜色的值

	需要创建跟踪栏实时改变的HSV的值，寻找我们需要的颜色
	我们也可以通过颜色的检测来进行物体检测，例如:口罩检测
	HSV颜色空间对于计算机来说更容易进行感知颜色
*/


// 对HSV颜色值进行跟踪

// 定义HSV的颜色，最大值，最小值
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;


int main()
{
	system("color F9");
	String path = "Resources/shapes.png";
	Mat img = imread(path);
	if (img.empty())
	{
		cout << "image not opened !" << endl;
		return -1;
	}

	// 将图像转换为 HSV图像
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	
	// 创建我们的追踪栏
	namedWindow("TrackBar", WINDOW_AUTOSIZE); // 创建一个跟踪栏窗口
	// createTrackbar("跟踪条的名称", "窗口名称", 初始值, 跟踪栏的范围);
	createTrackbar("hmin", "TrackBar", &hmin, 179);
	createTrackbar("hmax", "TrackBar", &hmax, 179);
	createTrackbar("smin", "TrackBar", &smin, 255);
	createTrackbar("smax", "TrackBar", &smax, 255);
	createTrackbar("vmin", "TrackBar", &vmin, 255);
	createTrackbar("vmax", "TrackBar", &vmax, 255);

	imshow("img", img);
	imshow("imgHSV", imgHSV);

	while (true)
	{
		// 定义HSV颜色值的上下限
		// 下限
		Scalar lower(hmin, smin, vmin);
		// 上限
		Scalar upper(hmax, smax, vmax);

		// 同上下限的范围找到 mask(掩膜，白色)。白色区域就是我们找的颜色区域
		Mat mask;
		//inRange(HSV图像, HSV颜色值的下限, HSV颜色值的上限, mask（遮挡的区域为查找区域，白色）);
		inRange(imgHSV, lower, upper, mask);

		imshow("mask", mask);
		cout << hmin << "," << smin << "," << vmin << "," << hmax << "," << smax << "," << vmax << endl;
		int c = waitKey(10);
		// 按ESC退出
		if (c == 27)
		{
			break;
		}
	}

	destroyAllWindows();

	return 0;
}