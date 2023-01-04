#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void getContours(Mat imgOriginal, Mat imgDilate)
{
	// 定义向量存储contours
	// {{{56，23},{52，22},{32，36}}}
	vector<vector<Point>> contours;

	// 定义向量存储 hierarchy（等级制度），轮廓的优先级
	// {{1,2,3,4},{5,6,7,8}}
	vector<Vec4i> hierarchy;

	// 查找轮廓
	//findContours(输入图像（二值化图像）, 轮廓, 轮廓的优先级, 定义轮廓的检索模式, 定义轮廓的近似方式);
	findContours(imgDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// 绘制轮廓
	// drawContours(输入图像, 轮廓, -1：绘制所有的轮廓, Scalar(255, 0, 0), 2, LINE_AA);
	/*drawContours(imgOriginal, contours, -1, Scalar(255, 0, 0), 2, LINE_AA);*/

	// 定义向量存储多边形的角点信息
	// 容器的初始容量和contours的容量是一样的
	vector<vector<Point>> conPoly(contours.size());

	// 定义向量存储边界矩形
	vector<Rect> boundRect(contours.size());

	cout << contours.size() << endl;

	// 物体的类别
	string obj_name;

	// 根据每个轮廓信息计算图形的面积 
	for (int i = 0; i < contours.size(); i++)
	{
		// 计算图形的面积
		int Area = contourArea(contours[i]);
		cout << "Area " << i << ":" << Area << endl;
		if (Area > 1000)
		{
			// 计算多边形的弧长
			float peri = arcLength(contours[i], true);
			float epsilon = peri * 0.02;

			// 拟合多边形的角点
			approxPolyDP(contours[i],conPoly[i],epsilon,true);

			// 将每个图像的角点绘制出来
			drawContours(imgOriginal, conPoly, i, Scalar(255, 45, 100), 2, LINE_AA);

			// 将角点信息转换为矩形
			boundRect[i] = boundingRect(conPoly[i]);

			// 角点数
			int objCor = (int)conPoly[i].size();
			// 三角形
			if (objCor == 3)
			{
				obj_name = "Triangle";
			}
			// 矩形
			else if (objCor == 4)
			{
				float apsRatio = boundRect[i].width / boundRect[i].height;
				if (apsRatio > 0.98 && apsRatio < 1.02)
				{
					obj_name = "square";
				}
				else
				{
					obj_name = "rectangle";
				}
			}
			else if (objCor > 4)
			{
				obj_name = "circle";
			}

			Point point(boundRect[i].x-5, boundRect[i].y+5);
			putText(imgOriginal, obj_name, point, 
				FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 20), 1, LINE_AA);

			// 将边界矩形绘制出来
			/*rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 0, 200), 3, LINE_AA);*/
			imshow("imgOriginal", imgOriginal);
		}
	}
}


int main()
{
	system("color F9");
	string path = "Resources/shapes.png";
	Mat imgShapes = imread(path);
	Mat imgOriginal = imgShapes.clone();
	if (imgShapes.empty())
	{
		printf("img not opened !");
		return -1;
	}

	imshow("imgShapes", imgShapes);

	// 一、图像的预处理，把图像变成 Canny图像，得到边缘检测的图像
	Mat imgGray,imgBlur, imgCanny, imgDilate;
	// 1.将彩色图像变为灰色图像
	cvtColor(imgShapes, imgGray, COLOR_BGR2GRAY);
	// 2.灰色图像进行高斯模糊去噪
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	// 3.进行Canny边缘检测,输入图像只能为灰色图像
	Canny(imgBlur, imgCanny, 75, 125);
	// 4.将边缘检测的信息进行扩大，二值化图像输入
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDilate, kernel);

	// 二、查找轮廓信息
	getContours(imgOriginal, imgDilate);

	/*imshow("imgGray", imgGray);
	imshow("imgBlur", imgBlur);
	imshow("imgCanny", imgCanny);
	imshow("imgDilate", imgDilate);*/

	waitKey(0);
	destroyAllWindows();

	return 0;
}