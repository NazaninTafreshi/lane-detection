/*!
* \brief        hough transform
* \details      finding lanes of a road with houghLinesP function
* \author       Nazanin Tafreshi
* \version      0.2
*/

#include "stdafx.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <cmath>
#include <iostream>

using namespace std;

int main()
{
	cv::Mat blur, edges, gray, hist;

	cv::Mat src = cv::imread("H:\\my-reports\\Task_009\\Images\\Image (30).jpg", 1);

	imshow("src", src);

	cvtColor(src, gray, cv::COLOR_BGR2GRAY);

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
	imshow("roi", roi);

	cv::Mat and_img = cv::Mat::zeros(edges.rows, edges.cols, CV_8U);
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
	int size = and_img.rows * and_img.cols;

	vector<cv::Vec4i> linesP;
	HoughLinesP(and_img, linesP, 1, CV_PI / 180, 100, size / 24000, 50);

	cv::Point initial;
	cv::Point end;
	int theta_thresh_low = 25;
	int theta_thresh_high = 90;

	vector<cv::Vec4i> selected_lines;
	for (cv::Vec4i i : linesP) {
		initial = cv::Point(i[0], i[1]);
		end = cv::Point(i[2], i[3]);
		double theta = atan2(static_cast<double>(end.y) - static_cast<double>(initial.y), static_cast<double>(end.x) - static_cast<double>(initial.x)) * 180 / CV_PI;

		if (cv::abs(theta) > theta_thresh_low && abs(theta) <= theta_thresh_high) {
			selected_lines.push_back(i);
			cout << "theta for the line with initial point at (" + to_string(initial.x) + ", " + to_string(initial.y) + ") coordinate is " << theta << endl;
		}
		else {
			cout << "ELSE theta for the line with initial point at (" + to_string(initial.x) + ", " + to_string(initial.y) + ") coordinate is " << theta << endl;
		}
	}


	for (int i = 0; i < selected_lines.size(); i++) {
		cv::Vec4i l = selected_lines[i];
		line(src, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
	}

	imshow("result", src);
	imwrite("results\\result.jpg", src);

	cv::waitKey();

}