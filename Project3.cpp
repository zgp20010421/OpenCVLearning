#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//////	Project 3  detect vehicle number plates///////////////////


int main() {

	VideoCapture cap(0);
	Mat img;

	// 编写级联分类器
	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");
	// 检测是否正确加载
	if (plateCascade.empty())
	{
		cout << "XML file not loaded" << endl;
	}

	// 定义矩形向量，保存车牌边界框
	vector<Rect> plates;
	/*
	我们使用车牌级联点检测多尺度方法
	*/

	while (true)
	{
		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10);
		// 遍历所有车牌，检测到，一一画出
		for (int i = 0; i < plates.size(); i++)
		{
			Mat imgCrop = img(plates[i]);
			Point point(plates[i].x, plates[i].y-10);
			//imwrite("Resources/plates/" + to_string(i) + ".png", imgCrop);
			putText(img, "license plate", point, FONT_HERSHEY_COMPLEX_SMALL, 1.5, Scalar(255,255,0), 2, LINE_AA);
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 5, LINE_AA);
		}

		imshow("Image", img);
		int c =	waitKey(10);
		if (c == 27)
		{
			break;
		}

	}
	destroyAllWindows();
	cap.release();
	return 0;
} 