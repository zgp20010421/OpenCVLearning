#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include <vector>

using namespace std;
using namespace cv;



////////////// Project 2 Document Scanner  ///////////////

Mat imgOriginal, imgGray, imgCanny, imgThre, imgBlur, imgDil, imgErode, imgWrap, imgCrop;
vector<Point> initialPoints, docPoints;

// 定义 A4 纸宽高
float w = 360, h = 580;

Mat Preprocessing(Mat img)
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	//高斯模糊
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	//Canny边缘检测器
	Canny(imgBlur, imgCanny, 25, 75);
	// only use odd (3,3) or (5,5)
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	//扩大
	dilate(imgCanny, imgDil, kernel);
	//腐蚀
	/*erode(imgDil, imgErode, kernel);*/

	return imgDil;
}

vector<Point> getContours(Mat image)
{

	// 二维向量列表
	vector<vector<Point>> contours;
	// 4个int类型向量
	vector<Vec4i> hierarchy;

	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	// 接收拟合后的轮廓点
	vector<vector<Point>> conPloy (contours.size());

	vector<Rect>boundRect(contours.size());
	// 返回点向量
	vector<Point> biggest;
	// 最大面积
	int maxArea = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		int Area = contourArea(contours[i]);
		// cout << Area << endl;
		if (Area > 1000)
		{
			// 获取弧长参数,闭合状态
			float peri = arcLength(contours[i], true);

			// 连续光滑曲线拟合多边形轮廓点
			approxPolyDP(contours[i], conPloy[i], 0.02 * peri, true);
			// cout << conPloy[i] << endl;

			if (Area > maxArea && conPloy[i].size() == 4)
			{
				// 绘制轮廓
				//drawContours(imgOriginal, conPloy, i, Scalar(255, 0, 255), 5, LINE_AA);
				// 轮廓将检测是否为最大轮廓
				biggest = { conPloy[i][0], conPloy[i][1] ,conPloy[i][2] ,conPloy[i][3] };
				maxArea = Area;
			}

			//// 绘制轮廓
			//drawContours(imgOriginal, conPloy, i, Scalar(255, 255, 20), 2, LINE_AA);
		}
	}
	return biggest;
}

// 
void drawPoints(vector<Point>points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOriginal, points[i], 10, color, FILLED);
		// 显示点的个数
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
	}
}

// 坐标点排序
vector<Point> reorder(vector<Point> points)
{
	/*
		
		(35,45)  80
		(40,60)  100
		(350,400)  750
		(310,200)  510
		
		{80,100,750,510}}
	*/
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;
	for (int i = 0; i < points.size(); i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}

	// 获得sumPoint向量中最小值的索引值 （index）
	// min_element(sumPoint.begin(), sumPoint.end()) - sumPoint.begin()

	// 获得sumPoint向量中最小值
	// *min_element(sumPoint.begin(), sumPoint.end())

	//min_element() 函数是算法头的库函数，
	//用于从范围中寻找最小的元素，它接受一个容器范围[开始，结束]，
	//并返回一个指向给定范围内具有最小值的元素的迭代器。


	// 获取点的索引
	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);	//0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);	//1
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);	//2
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);	//3

	return newPoints;
}

Mat getWrap(Mat image, vector<Point>points, float w, float h)
{
	Point2f src[4] = {points[0],points[1], points[2], points[3]};
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(imgOriginal, imgWrap, matrix, Point(w,h));

	return imgWrap;
}


int main()
{
	system("color F9");
	string path = "Resources/paper.jpg";
	imgOriginal = imread(path);
	
	// 缩小
	 resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
	// 找出其边缘，我们就知道纸张在哪，根据其纸张的坐标
	// 提取四个点或四个角


	//	1.	Preprocessing  图像预处理 （灰度，高斯过滤，边缘查找）
	imgThre = Preprocessing(imgOriginal);
	//	2.	Get contours - Biggest 查找轮廓，A4纸是我们图像中最大的矩阵
	initialPoints = getContours(imgThre);
	drawPoints(initialPoints,Scalar(0,255,20));
	// 需要定义一个新函数进行对点的排序
	docPoints = reorder(initialPoints);
	//drawPoints(docPoints, Scalar(255, 255, 20));
	//	3.	Wrap image 透视变换
	imgWrap = getWrap(imgOriginal,docPoints,w,h);

	// Crop
	int cropValue = 5;
	Rect roi(cropValue,cropValue,w - (2 * cropValue),h - (2 * cropValue));
	imgCrop = imgWrap(roi);

	imshow("image", imgOriginal);
	//imshow("image Dil", imgThre);
	//namedWindow("image Dil", WINDOW_FREERATIO);
	imshow("image warp", imgWrap);
	imshow("image Crop", imgCrop);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
