/*!
* \brief        hough transform
* \details      finding lanes of a road with houghLinesP function
* \author       Nazanin Tafreshi
* \version      0.1
*/

#include "stdafx.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;

int main()
{
	Mat blur, edges, gray, hist;

	Mat src = imread("H:\\my-reports\\Task_009\\Images\\Image (54).jpg", 1);
	imshow("src", src);

	cvtColor(src, gray, COLOR_BGR2GRAY);

	cv::blur(gray, blur, cv::Size(5, 5));
	imshow("blur", blur);
	imwrite("results\\blur.jpg", blur);

	Sobel(blur, edges, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
	imshow("sobel", edges);
	imwrite("results\\sobel.jpg", edges);

	threshold(edges, edges, 0, 255, cv::THRESH_OTSU);
	imshow("threshold", edges);
	imwrite("results\\threshold.jpg", edges);

	medianBlur(edges, edges, (11, 7));
	imshow("medianBlur", edges);
	imwrite("results\\medianBlur.jpg", edges);

	int x = edges.cols / 6;
	int y = edges.rows / 2.2;
	int w = edges.cols / 1.5;
	int h = edges.rows - y;
	cv::Rect rect(x, y, w, h);
	cv::Mat roi = edges(rect).clone();
	cv::imshow("roi", roi);

	Mat and_img = Mat::zeros(edges.rows, edges.cols, CV_8U);
	for (int i = 0; i < roi.rows; i++) {
		for (int j = 0; j < roi.cols; j++) {
			if ((roi.at<uchar>(i, j) & edges.at<uchar>(i + y, j + x)) == 255) {
				and_img.at<uchar>(i + y, j + x) = 255;
			}
			else {
				and_img.at<uchar>(i + y, j + x) = 0;
			}
		}
	}

	imshow("bitwiseAND", and_img);

	vector<Vec4i> linesP;
	HoughLinesP(and_img, linesP, 1, CV_PI / 180, 100, 0, 50);

	for (int i = 0; i < linesP.size(); i++) {
		Vec4i l = linesP[i];
		line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}

	imshow("result", src);
	imwrite("results\\result.jpg", src);

	waitKey();

}


