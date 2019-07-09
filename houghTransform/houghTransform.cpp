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
	Mat src = imread("H:\\my-reports\\Task_009\\Images\\Image (13).jpg", 1);
	imshow("src", src);

	cvtColor(src, gray, COLOR_BGR2GRAY);

	cv::blur(gray, blur, cv::Size(5, 5));
	imshow("blur", blur);
	imwrite("results\\blur.jpg", blur);

	equalizeHist(blur, hist);
	imshow("histogram equalization", hist);
	imwrite("results\\histEq.jpg", hist);

	Sobel(hist, edges, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
	imshow("sobel", edges);
	imwrite("results\\sobel.jpg", edges);

	threshold(edges, edges, 0, 255, cv::THRESH_OTSU);
	imshow("thereshold", edges);
	imwrite("results\\thereshold.jpg", edges);

	medianBlur(edges, edges, (11, 11));
	imshow("medianBlur", edges);
	imwrite("results\\medianBlur.jpg", edges);

	erode(edges, edges, 5);
	imshow("erode", edges);
	imwrite("results\\erode.jpg", edges);
	
	vector<Vec4i> linesP; 
	HoughLinesP(edges, linesP, 1, CV_PI / 180, 200, 0, 100);

	for (size_t i = 0; i < linesP.size(); i++) {
		Vec4i l = linesP[i];
		line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}

	imshow("result", src);
	imwrite("results\\result.jpg", src);
	waitKey();

}


