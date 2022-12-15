#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// 读取apple图像
	string apple_P = "Resources/apple.jpg";
	string orange_P = "Resources/orange.jpg";
	Mat apple = imread(apple_P);
	Mat orange = imread(orange_P);

	if (apple.empty() || orange.empty())
	{
		cout << "图像不存在或路径错误！" << endl;
		return -1;
	}

	// 融合图像
	// 图像的大小要相同（长、宽相等）
	int apple_w = apple.rows; //高
	int apple_h = apple.cols;//宽

	// 将orange图像定义为与apple图像相同
	resize(orange, orange, Size(apple_w, apple_h));
	
	// 打印apple和orange图像的大小
	cout << endl;
	cout << apple.size()<< endl;
	cout << orange.size() << endl;

	// 融合图像
	Mat imgBit;
	//bitwise_and(融合图像1, 融合图像2, 融合后的图像， mask遮罩);
	bitwise_and(apple,orange,imgBit);

	// mask
	Mat mask = Mat(512, 512, CV_8UC1, Scalar(0, 0, 0));

	// Rect 矩形类型声明 rect（名）（x,y,width,height）
	Rect rect(150, 150, 200, 200);

	// Scalar() 颜色函数
	// 将我们选择矩形的区域进行颜色赋值
	mask(rect) = Scalar(255, 255, 255); // 白色
	
	Mat imgMask;
	bitwise_and(apple, orange, imgMask, mask);

	// 1.先要指定矩形区域
	// 2.提取图像中的矩形区域
	Mat imgRoi = imgBit(rect);

	imshow("apple", apple);
	imshow("orange", orange);
	imshow("imgBit", imgBit);
	imshow("mask", mask);
	imshow("imgMask", imgMask);
	imshow("imgRoi", imgRoi);

	// 保存
	string imgname = "Roi.jpg";
	//imwrite(imgname, 保存图像);
	imwrite(imgname, imgRoi);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
