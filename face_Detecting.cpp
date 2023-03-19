#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	system("color F9");
	string path = "Resources/painting.jpg";
	Mat imgPeople = imread(path);
	Mat imgDraw = imgPeople.clone();
	if (imgPeople.empty())
	{
		cout << "img not open or find !" << endl;
		return -1;
	}
	CascadeClassifier Face;
	Face.load("Resources/haarcascade_frontalface_default.xml");
	if (Face.empty())
	{
		cout << "xml file not load" << endl;
		return 1;
	}

	vector<Rect> faces;
	Face.detectMultiScale(imgPeople, faces, 1.1, 2);

	cout << "检测到的人脸数量：" << endl;
	cout << faces.size() << endl;

	for (int i = 0; i < faces.size(); i++)
	{
		Point point(faces[i].x, faces[i].y - 15);

		rectangle(imgDraw, faces[i].tl(), faces[i].br(), Scalar(216, 255, 86),
			2, LINE_AA);

		putText(imgDraw, to_string(i), point, FONT_HERSHEY_SIMPLEX,
			1, Scalar(0, 0, 255), 2, LINE_AA);

		Rect rect(faces[i].tl(), faces[i].br());
		Mat faceRoi = imgPeople(rect);

		imshow("faceRoi"+to_string(i), faceRoi);
	}


	imshow("imgPeople", imgPeople);
	imshow("imgDraw", imgDraw);
	waitKey(0);
	destroyAllWindows();

	return 0;
}