#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// 背景：白色，字体蓝色
	system("color F9");


	// Mat类型 （matrix 矩阵）
	// 1.(行，列，type:CV_8UC1 /8个字节，U：uchar，
	// C：channel通道数  1：通道数为1)
	Mat a(512, 512, CV_8UC1);
	//cout << a << endl;

	// 2.Mat类型的定义,CV_8UC1
	Mat b = (Mat_<int>(3,3)<< 1,2,3,4,5,6,7,8,9);
	cout << b << endl;
	Mat c = (Mat_<int>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);
	
	// 矩阵相加
	Mat sum = b + c;
	Mat mut = c * 2;

	//打印 cout 输出
	cout << sum << endl;
	cout << mut << endl;

	// 3.定义全1或全0的矩阵
	Mat ones = Mat::ones(Size(512, 512), CV_8UC3);
	Mat zeros = Mat::zeros(Size(512, 512), CV_8UC3);
	// show ,只能显示最多为4通道的图像
	// 可以任意调节窗口,写在imshow这个函数前面

	namedWindow("ones", WINDOW_FREERATIO);
	namedWindow("zeros", WINDOW_FREERATIO);
	imshow("ones", ones);
	imshow("zeros", zeros);
	


	imshow("a", a);
	// 停留在当前一帧
	waitKey(0);
	destroyAllWindows();

	return 0;
}