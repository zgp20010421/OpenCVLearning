#include <opencv2\opencv.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 颜色选择
void colorPicker(Mat img) {
	Mat imgHSV;
	// 转换为 HSV 色彩空间
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	// 定义HSV颜色空间的起始和末尾值
	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 179, smax = 255, vmax = 255;

	// 创建窗口
	namedWindow("TrackBar",WINDOW_FREERATIO);
	// 创建跟踪栏，查找我们需要的颜色及其所对应的HSV的颜色值
	createTrackbar("Hua Min", "TrackBar", &hmin, 179);
	createTrackbar("Hua Max", "TrackBar", &hmax, 179);
	createTrackbar("Sat Min", "TrackBar", &smin, 255);
	createTrackbar("Sat Max", "TrackBar", &smax, 255);
	createTrackbar("Val Min", "TrackBar", &vmin, 255);
	createTrackbar("Val Max", "TrackBar", &vmax, 255);

	imshow("imgHSV", imgHSV);

	while (true)
	{
		//定义上下限
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		// 对查找颜色进行遮挡（mask掩膜）
		// 基于图像的颜色检测，可以进行物体检测
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		imshow("mask", mask);
		cout << hmin << "," << smin << "," << vmin << endl;
		cout << hmax << "," << smax << "," << vmax << endl;
		int c = waitKey(2);
		if (c == 27)
		{
			break;
		}
	}
}

// 存储口罩颜色
vector<vector<int>> maskColor = {
	{17,0,0,127,11,255},	 // white 
	{0,0,98,179,28,207},	 // gray
	{20,42,163,105,255,255}, // blue
};

// 存储颜色label
vector<string> mask_label = {
	"white","gray","blue"
};

// 矩阵值和口罩颜色index
vector<vector<int>> rect_ColorId;

// mask矩阵信息
Rect Maskrect;

// 获得口罩区域
Rect findMaskRect(Mat mask,Mat faceRoi)
{
	// 定义轮廓点存储向量
	vector<vector<Point>> contours;
	// 定义轮廓点的等级（先后）
	vector<Vec4i> hierarchy;
	// 查找轮廓
	findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// 存储轮廓区域向量
	vector<Rect> boundRect(contours.size());
	// 接收拟合后的多边形轮廓点
	vector <vector<Point>> conPloy(contours.size());
	

	// 计算每个轮廓的面积
	for (int i = 0; i < contours.size(); i++)
	{
		int contoursArea = contourArea(contours[i]);
		cout << "Area:" << contoursArea << endl;
		if (contoursArea > 2000)
		{
			// 获取弧长
			float peri = arcLength(contours[i], true);
			// 进行mask图形拟合
			approxPolyDP(contours[i], conPloy[i], peri * 0.02, true);
			// 找到mask区域，转化为矩形
			boundRect[i] = boundingRect(conPloy[i]);
			Maskrect.x = boundRect[i].x;
			Maskrect.y = boundRect[i].y;
			Maskrect.width = boundRect[i].width;
			Maskrect.height = boundRect[i].height;

			/*rectangle(faceRoi, Rect(boundRect[i].x,boundRect[i].y,boundRect[i].width,boundRect[i].height), 
				Scalar(11,255,66),2, LINE_AA);*/
		}
	}
	return Maskrect;
}

// 查找口罩颜色的索引值index
vector<vector<int>> findMaskColorIdx(Mat faceRoi, vector<vector<int>> maskColor) {
	
	Mat imgHSV,mask;
	// 转化为HSV
	cvtColor(faceRoi, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < maskColor.size(); i++)
	{
		// 定义HSV颜色空间的上下限
		Scalar lower(maskColor[i][0], maskColor[i][1], maskColor[i][2]);
		Scalar upper(maskColor[i][3], maskColor[i][4], maskColor[i][5]);
		// 对口罩区域进行遮挡（mask掩膜）
		inRange(imgHSV, lower, upper, mask);
		/*imshow(to_string(i) + "mask", mask);*/
		int countNums = 0;
		int maxNums = 4600;
		for (int i = 0; i < mask.rows; i++)
		{
			for (int j = 0; j < mask.cols; j++)
			{
				if (mask.ptr<uchar>(i)[j] == 255)
				{
					countNums++;
				}
			}
		}
		
		if (countNums > maxNums)
		{
			/*imshow("mask", mask);*/
			// 获取口罩区域的矩形
			Rect rect = findMaskRect(mask, faceRoi);
			if (!rect.empty())
			{
				rect_ColorId.push_back({ rect.x,rect.y,rect.width,rect.height,i });
			}

		}

		//// 获取口罩区域的矩形
		//vector<Rect> rect = findMaskRect(mask, faceRoi);
		/*if (!rect.empty())
		{
			rect_ColorId.push_back({ rect[i].x,rect[i].y,rect[i].width,rect[i].height,i });
		}*/
	}
	
	return rect_ColorId;
}

// 绘制
void drawCavans(vector<vector<int>> rect_ColorId,Mat faceRoi){
	for (int i = 0; i < rect_ColorId.size(); i++)
	{
		// 矩形
		Rect rect(rect_ColorId[i][0], rect_ColorId[i][1], rect_ColorId[i][2], rect_ColorId[i][3]);
		// 绘制矩形
		rectangle(faceRoi, rect, Scalar(255, 0, 255), 2, LINE_AA);
		// 绘制口罩颜色
		putText(faceRoi, mask_label[rect_ColorId[i][4]],
			Point(rect_ColorId[i][0]+30, rect_ColorId[i][1] - 20), 
			FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2, LINE_AA);
	}
	imshow("Mask", faceRoi);
}



int main()
{
	system("color F9");
	string path = "Resources/Mask02.webp";
	Mat img = imread(path);
	Mat imgOriginal;
	img.copyTo(imgOriginal);

	if (img.empty())
	{
		cout << "img not find or path not exit" << endl;
		return -1;
	}


	// 模型的路径
	string root_dir = "D:/APP/OpenCV/opencv/sources/samples/dnn/face_detector/";
	// 读取模型
	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");
	Mat blob = dnn::blobFromImage(img, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
	net.setInput(blob);// NCHW，设置网络输入值
	Mat probs = net.forward(); // 网络预测，特征返回
	// probs.size[2]:长        probs.size[3]:宽
	Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());

	for (int i = 0; i < detectionMat.rows; i++) {
		float confidence = detectionMat.at<float>(i, 2);
		if (confidence > 0.5) {
			//获取矩阵坐标（第3，4，5，6参数）
			/*
				static_cast<new_type>(expression)，强制转换
				new_type为目标数据类型，expression为原始数据类型变量或表达式
			*/
			int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * img.cols);
			int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * img.rows);
			int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * img.cols);
			int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * img.rows);
			Rect box(x1, y1, x2 - x1, y2 - y1);
			rectangle(imgOriginal, box, Scalar(188, 125, 0), 3, 8, 0);
			Mat faceRoi = img(box);
			imshow("img", img);
			imshow("face" + to_string(i), faceRoi);
			imshow("original", imgOriginal);
			// 选择颜色口罩
			/*colorPicker(faceRoi);*/
			
			findMaskColorIdx(faceRoi,maskColor);
			drawCavans(rect_ColorId, faceRoi);
		}
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}