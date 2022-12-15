#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// 定义画板
	Mat painter = Mat(512, 512, CV_8UC3, Scalar(255, 255, 255));

	// opencv BGR 
	// blue
	Mat painter_blue = Mat(512, 512, CV_8UC3, Scalar(255, 0, 0));
	// green
	Mat painter_green = Mat(512, 512, CV_8UC3, Scalar(0, 255, 0));
	// red
	Mat painter_red = Mat(512, 512, CV_8UC3, Scalar(0, 0, 255));

	// 定义圆
	//circle(输入图像, 中心点：Point(256, 256), 半径：
	// 160, Scalar(255, 0, 255), 线的厚度：5, 线平滑：LINE_AA);
	/*circle(painter, Point(256, 256), 160, Scalar(255, 0, 255), 5, LINE_AA);*/
	circle(painter, Point(256, 256), 160, Scalar(255, 0, 255), -1, LINE_AA);

	// 矩形
	// rectangle(input, 矩形的区域：Rect(206, 206, 100, 100), Scalar(255, 90, 100), 5, LINE_AA);
	rectangle(painter, Rect(206, 206, 100, 100), Scalar(255, 90, 100), 5, LINE_AA);

	// 线条
	//line(painter, 左边的点：Point(100, 350), 右边的点：Point(412, 350), Scalar(125, 250, 110), 5, LINE_AA);
	line(painter, Point(100, 350), Point(412, 350), Scalar(125, 250, 110), 5, LINE_AA);

	// 文本
	/*putText(输入：painter, 文本："OpenCV", 位置：Point(50, 50),
		字体的样式：FONT_HERSHEY_SCRIPT_SIMPLEX, 字体的大小：2, Scalar(125, 200, 255), 4, LINE_AA);*/
	/*putText(painter, "OpenCV", Point(50, 50),
		FONT_HERSHEY_SCRIPT_SIMPLEX, 2, Scalar(125, 200, 255), 4, LINE_AA);*/

	putText(painter, "OpenCV", Point(50, 50),
		FONT_HERSHEY_COMPLEX, 2, Scalar(125, 200, 255), 4, LINE_AA);


	imshow("painter", painter);
	imshow("painter_blue", painter_blue);
	imshow("painter_green", painter_green);
	imshow("painter_red", painter_red);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
