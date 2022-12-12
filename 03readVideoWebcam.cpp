#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// 控制变成白色，蓝色字体
	system("color F9");
	
	// 1.读取视频
	// 视频路径
	//string path = "Resources/test_video.mp4";

	// 视频捕获类型
	//VideoCapture video(path);

	// 调用摄像头
	// 电脑自带摄像头
	int index = 0;
	VideoCapture webCam(index);


	// 判断是否成功读取视频
	if (!webCam.isOpened())
	{
		cout << "路径出错或视频不存在！" << endl;
		return 1;
	}

	//// 打印
	//cout << endl;
	//// CAP_PROP_FRAME_COUNT 视频的总帧数
	//cout << "视频的总帧数:" << video.get(CAP_PROP_FRAME_COUNT) << endl;
	//// CAP_PROP_FPS 视频一秒钟播放的帧数
	//cout << "视频一秒钟播放的帧数:" << video.get(CAP_PROP_FPS) << endl;
	//// CAP_PROP_FRAME_HEIGHT 视频的高度
	//cout << "视频的高度:" << video.get(CAP_PROP_FRAME_HEIGHT) << endl;
	//// CAP_PROP_FRAME_WIDTH 视频的宽度
	//cout << "视频的宽度:" << video.get(CAP_PROP_FRAME_WIDTH) << endl;
	//cout << endl;
	//// 计算视频时长
	//// 总帧数/每一秒钟的帧数
	//cout << "视频的总时长:" << video.get(CAP_PROP_FRAME_COUNT) / video.get(CAP_PROP_FPS) << " s" << endl;
	//cout << endl;


	// 定义一个矩阵类型
	Mat img;

	// 用while循环去一帧一帧（一张一张图像）的读取视频
	while (true)
	{
		// 读取每一帧，img矩阵进行存储每一帧
		webCam.read(img);

		// 图像翻转函数 
		//flip(输入图像，输出图像，1：左右翻转/-1：上下翻转)
		int code = 1;
		flip(img, img, code);

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
	webCam.release();
	return 0; 
}