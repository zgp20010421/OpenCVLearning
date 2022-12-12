#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	system("color F9");
	
	// 1.读取视频
	// 视频路径
	string path = "Resources/test_video.mp4";

	VideoCapture video(path);
	// 判断是否成功读取视频
	if (!video.isOpened())
	{
		cout << "路径出错或视频不存在！" << endl;
		return 1;
	}
	Mat img;
	// 用while循环去一帧一帧（一张一张图像）的读取视频
	while (true)
	{
		// 读取每一帧，img矩阵进行存储每一帧
		video.read(img);


		imshow("video", img);
		int c = waitKey(30);
		// 27代表的是键盘上ESC
		if (c == 27)
		{
			break;
		}
	}

	destroyAllWindows();
	// 释放视频读取资源
	video.release();
	return 0; 
}