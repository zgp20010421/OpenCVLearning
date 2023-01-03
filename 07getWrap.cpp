#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	system("color F9");
	String path = "Resources/cards.jpg"; 
	Mat img = imread(path);
	if (img.empty())
	{
		cout <<"image not opened !" << endl;
		return -1;
	}

	// 定义透视变换后图像的长和宽(float)
	float width = 360 ,height = 540;

	// 找到K卡片的四个角点（坐标点）
	// 左上，右上，左下，右下
	Point2f srcK[4] = { {528,145},{769,190},{406,392},{675,455} };

	// 透视变换后图像的四个角点（坐标点）
	Point2f dstK[4] = { {0.0f,0.0f},{width,0.0f},{0.0f,height},{width,height} };

	// 找到透视变换的转换矩阵
	// getPerspectiveTransform(K卡片的四个角点, 透视变换后图像的四个角点);
	Mat matrixK = getPerspectiveTransform(srcK, dstK);

	cout << matrixK << endl;

	// 用扭曲变换得到变换后的图像
	Mat imgWrap;
	warpPerspective(img, imgWrap, matrixK, Size(width, height));

	// 缩小一半
	resize(img, img, Size(), 0.5, 0.5);
	imshow("img", img);
	imshow("imgWarp", imgWrap);


	waitKey(0);
	destroyAllWindows();

	return 0;
}