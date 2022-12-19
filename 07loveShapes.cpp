#include <opencv2\opencv.hpp>
#include <iostream>
#include <cmath>


using namespace std;
using namespace cv;

// 写一个判断坐标点是否在爱心的里面
bool check(double x, double y)
{
	//pow(x * x + y * y + 1, 3.0) + x * x * y * y * y < 0
	//这个是爱心曲线公式
	return pow(x * x + y * y - 1, 3.0) + x * x *x * y * y < 0;
}

// 定义BGR 通道矩阵

const int M = 600, N = 600;
double B[M][N], G[M][N], R[M][N];


int main()
{
	system("color F9");
	// 给BGR三通道的矩阵进行赋值
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// 坐标点在爱心里面的取值范围
			// {[-1.5,1.5],[-1.5,1.5]}
			if (check((double)i/M*3-1.5,(double)j/N*3-1.5))
			{
				B[i][j] = abs(50 -i/6);
				G[i][j] = abs(56 -i/6);
				R[i][j] = abs(255-i/6-j/6);
			}
			else
			{
				// 不在爱心区域内赋值为白色
				B[i][j] = G[i][j] = R[i][j] = 255;
			}
		}
	}

	// 创建矩阵类型，对矩阵类型进行颜色值的赋值
	Mat Love = Mat(M, N, CV_8UC3);
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Love.ptr<uchar>(i)[j * 3] = B[i][j];
			Love.ptr<uchar>(i)[j * 3 + 1] = G[i][j];
			Love.ptr<uchar>(i)[j * 3 + 2] = R[i][j];
		}
	}
	imshow("Love", Love);

	string savePath = "love.jpg";
	imwrite(savePath, Love);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
