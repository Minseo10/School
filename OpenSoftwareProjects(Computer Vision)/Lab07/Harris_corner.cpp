// opencv_test.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

vector<Point2f> MatToVec(const Mat input);
Mat NonMaximum_Suppression(const Mat input, Mat corner_mat, int radius);
Mat Mirroring(const Mat input, int n);
void type2str(int type);


int main() {

	//Use the following three images.
	//Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab07\\checkerboard.png", CV_LOAD_IMAGE_COLOR);
	//Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab07\\checkerboard2.jpg", CV_LOAD_IMAGE_COLOR);
	  Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab07\\lena.jpg", CV_LOAD_IMAGE_COLOR);

		// check for validation
	if (!input.data) {
		printf("Could not open\n");
		return -1;
	}

	int row = input.rows;
	int col = input.cols;

	Mat input_gray, input_visual; //input_visual: corner를 표시한 input image
	Mat output, output_norm, corner_mat;
	vector<Point2f> points;

	corner_mat = Mat::zeros(row, col, CV_8U);//corner인 픽셀에는 1, 아니면 0 저장

	//Option for the non-maximum suppression
	//Compare the result when 'true' or 'false'
	bool NonMaxSupp = true;

	//Option for subpixel refinement in corner detection,
	//Compare the result when 'true' or 'false'
	bool Subpixel = true;


	cvtColor(input, input_gray, CV_RGB2GRAY);	// convert RGB to Grayscale	

	//Harris corner detection using 'cornerHarris'
	//Note that 'src' of 'cornerHarris' can be either 1) input single-channel 8-bit or 2) floating-point image.
	//Fill the code/////////////////////////////////////
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
	input_gray.convertTo(input_gray, CV_32FC1, 1.0/255);
	cornerHarris(input_gray, output, blockSize, apertureSize, k, BORDER_DEFAULT);
	////////////////////////////////////////////////////


	//Scale the Harris response map 'output' from 0 to 1.
	//This is for display purpose only.
	normalize(output, output_norm, 0, 1.0, NORM_MINMAX);
	namedWindow("Harris Response", WINDOW_AUTOSIZE);
	imshow("Harris Response", output_norm);


	//Threshold the Harris corner response.
	//corner_mat = 1 for corner, 0 otherwise.
	input_visual = input.clone();
	double minVal, maxVal;		Point minLoc, maxLoc; //value & location of global minimum and maximum
	minMaxLoc(output, &minVal, &maxVal, &minLoc, &maxLoc); //finds value & location of global minimum and maximum

	int corner_num = 0; //# of corners
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (output.at<float>(i, j) > 0.01 * maxVal) //if larger than threshold
			{
				//input_visual.at<Vec3b>(i, j)[0] = 0;		input_visual.at<Vec3b>(i, j)[1] = 0;	input_visual.at<Vec3b>(i, j)[2] = 255;
				circle(input_visual, Point(j, i), 2, Scalar(0, 0, 255), 1, 8, 0);	//You can also use this function of drawing a circle. For details, search 'circle' in OpenCV.

				corner_mat.at<uchar>(i, j) = 1;

				corner_num++;
			}

			else
				output.at<float>(i, j) = 0.0;
		}
	}
	printf("After cornerHarris, corner number = %d\n\n", corner_num);
	namedWindow("Harris Corner", WINDOW_AUTOSIZE);
	imshow("Harris Corner", input_visual);

	//Non-maximum suppression
	if (NonMaxSupp)
	{
		NonMaximum_Suppression(output, corner_mat, 2);

		//after non-maximum suppression, show corners
		corner_num = 0;
		input_visual = input.clone();
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (corner_mat.at<uchar>(i, j) == 1) {
					//input_visual.at<Vec3b>(i, j)[0] = 0;		input_visual.at<Vec3b>(i, j)[1] = 0;	input_visual.at<Vec3b>(i, j)[2] = 255;					
					circle(input_visual, Point(j, i), 2, Scalar(0, 0, 255), 1, 8, 0);	//You can also use this function of drawing a circle. For details, search 'circle' in OpenCV.
					corner_num++;
				}
			}
		}

		printf("After non-maximum suppression, corner number = %d\n\n", corner_num);
		namedWindow("Harris Corner (Non-max)", WINDOW_AUTOSIZE);
		imshow("Harris Corner (Non-max)", input_visual);
	}

	//Sub-pixel refinement for detected corners
	if (Subpixel)
	{
		Size subPixWinSize(3, 3); //sub-pixel window size is 7x7
		TermCriteria termcrit(TermCriteria::COUNT | TermCriteria::EPS, 20, 0.03);

		points = MatToVec(corner_mat);

		//Fill the code///////////////////////////////////////////////////////////
		output.convertTo(output, CV_8UC1);
		cornerSubPix(output, points, subPixWinSize, Size(-1, -1), termcrit);
		//////////////////////////////////////////////////////////////////////////

		//Display the set of corners
		input_visual = input.clone();
		for (int k = 0; k < points.size(); k++) {

			int x = points[k].x;
			int y = points[k].y;

			if (x<0 || x>col - 1 || y<0 || y>row - 1) //corner들이 image 영역 바깥에 있는 경우
			{
				points.pop_back();
				continue;
			}

			//input_visual.at<Vec3b>(i, j)[0] = 0;		input_visual.at<Vec3b>(i, j)[1] = 0;	input_visual.at<Vec3b>(i, j)[2] = 255;
			circle(input_visual, Point(x, y), 2, Scalar(0, 0, 255), 1, 8, 0);	//You can also use this function of drawing a circle. For details, search 'circle' in OpenCV.
		}

		printf("After subpixel-refinement, corner number = %d\n\n", points.size());
		namedWindow("Harris Corner (subpixel)", WINDOW_AUTOSIZE);
		imshow("Harris Corner (subpixel)", input_visual);
	}

	waitKey(0);

	return 0;
}

//change matrix into Point2f type vector
vector<Point2f> MatToVec(const Mat input)
{
	vector<Point2f> points;

	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			if (input.at<uchar>(i, j) == 1) {
				points.push_back(Point2f((float)j, (float)i));
			}
		}
	}

	return points;
}

//non-maximum suppression function
//input: input image, corner_mat: save 1 for corner and 0 otherwise.. , radius: window size for non-maximum suppression
Mat NonMaximum_Suppression(const Mat input, Mat corner_mat, int radius)
{
	int row = input.rows;
	int col = input.cols;

	Mat input_mirror = Mirroring(input, radius); //use mirroring method for boundary processing

	for (int i = radius; i < row + radius; i++) {
		for (int j = radius; j < col + radius; j++) {

			if (corner_mat.at<uchar>(i - radius, j - radius) == 1) {
				double max = 0.0;
				for (int a = -radius; a <= radius; a++) { // for each  window
					for (int b = -radius; b <= radius; b++) {
						if (input_mirror.at<float>(i + a, j + b) > max) max = input_mirror.at<float>(i + a, j + b);
					}
				}

				if (max == input_mirror.at<float>(i, j))
					corner_mat.at<uchar>(i - radius, j - radius) = 1;
				else
					corner_mat.at<uchar>(i - radius, j - radius) = 0;
			}
		}
	}

	return input;
}

//mirroring method for boundary processing
//input: input image, n: window radius
Mat Mirroring(const Mat input, int n)
{
	int row = input.rows;
	int col = input.cols;

	Mat input2 = Mat::zeros(row + 2 * n, col + 2 * n, input.type());
	int row2 = input2.rows;
	int col2 = input2.cols;

	for (int i = n; i < row + n; i++) {
		for (int j = n; j < col + n; j++) {
			input2.at<float>(i, j) = input.at<float>(i - n, j - n);
		}
	}
	for (int i = n; i < row + n; i++) {
		for (int j = 0; j < n; j++) {
			input2.at<float>(i, j) = input2.at<float>(i, 2 * n - j);
		}
		for (int j = col + n; j < col2; j++) {
			input2.at<float>(i, j) = input2.at<float>(i, 2 * col - 2 + 2 * n - j);
		}
	}
	for (int j = 0; j < col2; j++) {
		for (int i = 0; i < n; i++) {
			input2.at<float>(i, j) = input2.at<float>(2 * n - i, j);
		}
		for (int i = row + n; i < row2; i++) {
			input2.at<float>(i, j) = input2.at<float>(2 * row - 2 + 2 * n - i, j);
		}
	}

	return input2;
}


//If you want to know the type of 'Mat', use the following function
//For instance, for 'Mat input'
//type2str(input.type());
void type2str(int type) {
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	printf("Matrix: %s \n", r.c_str());
}