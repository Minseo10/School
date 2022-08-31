// opencv_test.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab07\\lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray, output;

	// check for validation
	if (!input.data) {
		printf("Could not open\n");
		return -1;
	}

	cvtColor(input, input_gray, CV_RGB2GRAY);	// convert RGB to Grayscale
    input_gray.convertTo(input_gray, CV_8U);	//input must be 8 bit image

	//Fill the code using 'Canny' in OpenCV.
	Canny(input_gray, output, 50, 95, 3, true);

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	output.convertTo(output, CV_8U);
	namedWindow("Canny", WINDOW_AUTOSIZE);
	imshow("Canny", output);

	waitKey(0);

	return 0;
}



