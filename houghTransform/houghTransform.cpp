/*!
* \brief        hough transform
* \details      finding lanes of roads in the image with houghLinesP function
* \author       Nazanin Tafreshi
*/

#include "pch.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;

int main()
{
	Mat blur, edges, gray, hist;
	Mat src = imread("H:\\my-reports\\Task_009\\Images\\Image (22).jpg", 1);
	imshow("src", src);

	//Mat mask;
	//cv::Scalar lowerb = cv::Scalar(90, 80, 90);
	//cv::Scalar upperb = cv::Scalar(255, 255, 255);
	//cv::inRange(src, lowerb, upperb, mask);
	//imshow("mask", mask);

	cvtColor(src, gray, COLOR_BGR2GRAY);

	//equalizeHist(gray, hist);
	//bilateralFilter(gray, hist, 9, 75, 75);
	//cv::GaussianBlur(gray, hist, cv::Size(0, 0), 3);
    //cv::addWeighted(gray, 1.5, hist, -0.5, 0, hist);

	cv::blur(gray, blur, cv::Size(5, 5));
	imshow("blur", blur);
	imwrite("blur.jpg", blur);

	//equalizeHist(blur, hist);
	imshow("histogram equalization", blur);
	Sobel(blur, edges, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
	imshow("sobel", edges);
	Canny(edges, edges, 50, 150, 3);
	//medianBlur(edges, edges, (3, 3));
	dilate(edges, edges,11,Point(-1,-1),15);
	//Sobel(blur, edges, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
	imshow("canny", edges);
	imwrite("sobel.jpg", edges);

	//equalizeHist(edges, edges);
	//cv::blur(edges, edges, cv::Size(15, 15));
	//imshow("hist", edges);

	//threshold(edges, edges, 0, 255, cv::THRESH_OTSU);
	imshow("thereshold", edges);
	imwrite("thereshold.jpg", edges);

	//medianBlur(edges, edges, (11, 11));
	imshow("medianBlur", edges);
	imwrite("medianBlur.jpg", edges);

	//erode(edges, edges, 5);
	imshow("erode", edges);
	imwrite("erode.jpg", edges);
	/*cv::medianBlur(edges, edges, 11);
	imshow("medianBlur", edges);
	erode(edges, edges, 5);
	imshow("erode", edges);*/
	//dilate(edges, edges, 5);
	//cv::morphologyEx(edges, edges, cv::MORPH_ERODE, getStructuringElement(cv::MORPH_RECT, cv::Size(1, 1)), cv::Point(-1, -1));
	//imshow(" m", edges);
	/*
	cv::Mat horizontalStructure = getStructuringElement(cv::MORPH_RECT, cv::Size(edges.cols / 30, 1));
	cv::morphologyEx(edges, edges, cv::MORPH_CLOSE, horizontalStructure, cv::Point(-1, -1));
	imshow("horizontal morphology", edges);

	Mat output;
	cv::morphologyEx(edges, output, cv::MORPH_ERODE, getStructuringElement(cv::MORPH_RECT, cv::Size(1, edges.rows / 30)), cv::Point(-1, -1));
	imshow(" morphology", output);
	subtract(edges, output,output);
	imshow(" out", output);
	Mat o(src.rows,src.cols,CV_8U);
	medianBlur(output, o, (11, 11));*/

	//cv::morphologyEx(o, o, cv::MORPH_CLOSE, getStructuringElement(cv::MORPH_RECT, cv::Size(1, edges.rows / 30)), cv::Point(-1, -1));
	//imshow(" m", o);
	//subtract(o, mask, o);
	//imshow(" vm", o);
	/*int arr[] = { 320, 150, 400, 250,
		250, 350, 320, 150 };
	Mat mask = Mat::zeros(src.rows, src.cols, CV_8U);
	Mat vertices(1, 8, CV_8S,arr);
	vector<Point> pt;
	for (int i = 0; i < 8; i++) {
		pt.push_back(arr[i]);
	}

	fillPoly(mask, vertices, 255);
	Mat masked_edges;
	bitwise_and(edges, mask, masked_edges);*/

	vector<Vec4i> linesP; //150, 0, 50
	HoughLinesP(edges, linesP, 1, CV_PI / 180, 200, 0, 100);

	for (size_t i = 0; i < linesP.size(); i++) {
		Vec4i l = linesP[i];
		line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}

	imshow("result", src);
	imwrite("result.jpg", src);
	waitKey();

}


