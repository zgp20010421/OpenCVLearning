#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////  Project 1   virtual painter //////////////////////

/*
首先使用HSV空间检测颜色，有了颜色
轮廓法找到轮廓所在的轮廓
找到轮廓，我们取 X 和 Y，在这些位置，我们将创建一个圆圈
在这一点上，首先必须找到颜色

我们将有多个mask，如果我们正在检测 green and purple 
我们将有green mask and purple mask

*/

// 创建向量，它将检测多种颜色，（如果有两种颜色）将检测到2.
// 一组大括号里包含一种颜色,使用颜色选择器来查找颜色
// 检测颜色
// hmin,smin,vmin,hmax,smax,vmax
vector<vector<int>> myColors{
	{141, 62, 175, 179, 255, 247},	//pink
	{97, 120, 74, 114, 234, 221}	//blue
};

//定义颜色，我们想要显示的颜色
vector<Scalar> myColorValues{
	{255,0,255},	//pink
	{255,255,50}	//blue
};

Mat img;
// { {x横坐标，y纵坐标，0 表示myClolor中的第一种颜色}，{x,y,1}}
vector<vector<int>> newPoints;


Point getContours(Mat imgDil)
{
	// contours is a vector向量就像是一个列表
	vector<vector<Point>> contours;
	// 没有结构，4个int类型
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 255, 20), 2, LINE_AA);

	// 接收拟合后的多边形轮廓
	vector<vector<Point>> conPoly(contours.size());
	// 存储围绕它的边界矩阵的坐标
	vector<Rect> boundRect(contours.size());

	// 定义Point
	Point myPoint;

	// 噪音，我们需要设置过滤面积，如果面积大于一定的范围，
	// loop all shapes area of contours 
	for (int i = 0; i < contours.size(); i++)
	{

		int area = contourArea(contours[i]);
		cout << area << endl;
		if (area > 1000)
		{
			// 找到区域过滤，找到参数，write here patty and 弧长
			// 使用轮廓找到弧长，
			// 找到角点或多边形具有的曲线数，
			// 若多边形具有四个曲线或四个角点，则为矩形，三个，三角形
			// 大于4个角点，circle

			// 获取曲线弧长参数，为闭合状态。float型
			float peri = arcLength(contours[i], true);

			// 把一个连续光滑曲线折线化，对图像轮廓点进行多边形拟合
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			cout << conPoly[i].size() << endl;

			// 找到周围的边界矩阵，如果我们只想要一个盒子，我们可以找到
			// 得到边界矩阵，只需传递我们的多边形轮廓
			// 这是我们得到角点数的近似值,我们将其传递进来，它将绘制一个边框，
			// 或者给我我们围绕它的边界矩阵的坐标
			boundRect[i] = boundingRect(conPoly[i]);

			// 从顶部中间位置绘画
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			// 绘制拟合后的多边形轮廓
			drawContours(img, conPoly, i, Scalar(255, 255, 20), 2);

			// tl()边界矩阵左上坐标点，br()边界矩阵右下坐标点
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 20), 1, LINE_AA);
		}

	}
	return myPoint;
}

vector<vector<int>> findColor(Mat img)
{
	Mat imgHSV,mask;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	// 一种颜色需要一个mask，so 我们需要进行循环
	for (int i = 0; i < myColors.size(); i++)
	{
		// HSV颜色空间颜色最低值-最高值
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		Point myPoint = getContours(mask);

		// 判断点是否存在
		if (myPoint.x != 0 && myPoint.y != 0)
		{
			newPoints.push_back({ myPoint.x, myPoint.y, i });	// i表示颜色
		}

	}

	return newPoints;
}

void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues)
{
	for (int i = 0; i < newPoints.size(); i++)
	{
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 20, myColorValues[newPoints[i][2]], FILLED, LINE_AA);
	}
}

int main() {
	system("color F9");
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cout << "摄像头没打开" << endl;
		return -1;
	}

	while (true)
	{
		cap.read(img);
		// 查找颜色，发送图像来查找颜色
		findColor(img);
		drawOnCanvas(newPoints, myColorValues);

		// 视频反转
		Mat imgFlip;
		flip(img, imgFlip, 1);
		

		imshow("Image", imgFlip);

		
		int c = waitKey(10);
		if (c == 27)
		{
			break;
		}
		else if (c == '6')
		{
			break;
		}
	}
	destroyAllWindows();
	cap.release();
	return 0;
}