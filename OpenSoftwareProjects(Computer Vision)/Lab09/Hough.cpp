// opencv_test.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main() {

	Mat src = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab09\\building.jpg", CV_LOAD_IMAGE_COLOR);
	Mat dst, color_dst;

	// check for validation
	if (!src.data) {
		printf("Could not open\n");
		return -1;
	}

	Canny(src, dst, 50, 200, 3); //run the canny edge detector->dst
	cvtColor(dst, color_dst, COLOR_GRAY2BGR); //convert edge detection result to color image

	//Standard Hough transform (using 'HoughLines')
#if 0
	vector<Vec2f> lines;
	HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0); // runs the actual detection

	for (size_t i = 0; i < lines.size(); i++)
	{
		//rho, theta: parameters
		//x*cos(theta)+y*cos(theta)=r
		float rho = lines[i][0]; 
		float theta = lines[i][1]; 
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		//(0,0)과의 거리가 rho이고 원점에서 수직으로 내렸을 때 각도가 theta인 직선을 그린다
		Point pt1(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * (a)));
		Point pt2(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * (a)));
		line(color_dst, pt1, pt2, Scalar(0, 0, 255), 3, 8);
	}

	//Probabilistic Hough transform (using 'HoughLinesP')
#else
	vector<Vec4i> lines;
	HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection
	//line: each line is represented by a 4-element vector (x1,y1,x2,y2) , where (x1,y1) and (x2,y2) are the ending points of each detected line segment.

	for (size_t i = 0; i < lines.size(); i++)
	{
		line(color_dst, Point(lines[i][0], lines[i][1]),
			Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
	}
#endif
	namedWindow("Source", 1);
	imshow("Source", src);
	namedWindow("Detected Lines", 1);
	imshow("Detected Lines", color_dst);
	waitKey(0);

	return 0;
}

