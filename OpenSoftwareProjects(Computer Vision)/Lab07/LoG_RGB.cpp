// opencv_test.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include <iostream>
#include <algorithm>

using namespace cv;
using namespace std;

Mat get_Gaussian_Kernel(int n, double sigma_t, double sigma_s, bool normalize);
Mat get_Laplacian_Kernel();
Mat Gaussianfilter(const Mat input, int n, double sigma_t, double sigma_s);
Mat Laplacianfilter(const Mat input);
Mat Mirroring(const Mat input, int n);


int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab07\\lena.jpg", CV_LOAD_IMAGE_COLOR);

	// check for validation
	if (!input.data) {
		printf("Could not open\n");
		return -1;
	}

	//Gaussian smoothing parameters
	int window_radius = 2;
	double sigma_t = 2.0;
	double sigma_s = 2.0;


	//convert input_gray into : input_gray*alpha + beta
	//alpha=1.0/255 , beta= 0.0(default parameter)
	input.convertTo(input, CV_64FC3, 1.0 / 255);	// 8-bit unsigned char 3channel -> 64-bit floating point 3 channel

	Mat h_f = Gaussianfilter(input, window_radius, sigma_t, sigma_s);	// h(x,y) * f(x,y)

	Mat Laplacian = Laplacianfilter(h_f);

	//0: 변환 최소값, 1: 변환 최대값, CV_MINMAX: 변환 방식
	//Laplacain matrix를 0과 1 사이 값으로 normalize 한다
	normalize(Laplacian, Laplacian, 0, 1, CV_MINMAX);

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", input);

	namedWindow("Gaussian blur", WINDOW_AUTOSIZE);
	imshow("Gaussian blur", h_f);

	//Laplacina matrix의 값들을 0과 255사이 값들로 변환해준다
	Laplacian.convertTo(Laplacian, CV_8UC3, 255.0);
	namedWindow("Laplacian filter", WINDOW_AUTOSIZE);
	imshow("Laplacian filter", Laplacian);

	waitKey(0);

	return 0;
}


//gaussian filtering function
//input: input intensity matrix, n: kernel size is (2n+1)*(2n+1), sigma_t / sigma_s: standard deviation
Mat Gaussianfilter(const Mat input, int n, double sigma_t, double sigma_s) {

	int row = input.rows;
	int col = input.cols;

	// generate gaussian kernel
	Mat kernel = get_Gaussian_Kernel(n, sigma_t, sigma_s, true);
	Mat output = Mat::zeros(row, col, input.type());

	//Intermediate data generation for mirroring
	Mat input_mirror = Mirroring(input, n);

	for (int i = n; i < row + n; i++) {
		for (int j = n; j < col + n; j++) {

			double sum1_r = 0.0; //intensity value of each channel
			double sum1_g = 0.0;
			double sum1_b = 0.0;
			for (int a = -n; a <= n; a++) { // for each kernel window
				for (int b = -n; b <= n; b++) {
					sum1_r += input_mirror.at<Vec3d>(i + a, j + b)[0] * kernel.at<double>(a + n, b + n);
					sum1_g += input_mirror.at<Vec3d>(i + a, j + b)[1] * kernel.at<double>(a + n, b + n);
					sum1_b += input_mirror.at<Vec3d>(i + a, j + b)[2] * kernel.at<double>(a + n, b + n);
				}
			}

			output.at<Vec3d>(i - n, j - n)[0] = sum1_r;
			output.at<Vec3d>(i - n, j - n)[1] = sum1_g;
			output.at<Vec3d>(i - n, j - n)[2] = sum1_b;
		}
	}

	return output;
}

//laplacian filter function
//'input' will be gaussian smoothed image
Mat Laplacianfilter(const Mat input) {

	int row = input.rows;
	int col = input.cols;

	Mat kernel = get_Laplacian_Kernel();
	Mat output = Mat::zeros(row, col, input.type());

	int n = 1; //because laplacian kernel is 3x3 size
	Mat input_mirror = Mirroring(input, n);

	for (int i = n; i < row + n; i++) {
		for (int j = n; j < col + n; j++) {

			double sum1_r = 0.0; //intensity value of each channel
			double sum1_g = 0.0;
			double sum1_b = 0.0;
			for (int a = -n; a <= n; a++) { // for each kernel window
				for (int b = -n; b <= n; b++) {

					sum1_r += input_mirror.at<Vec3d>(i + a, j + b)[0] * kernel.at<double>(a + n, b + n);
					sum1_g += input_mirror.at<Vec3d>(i + a, j + b)[1] * kernel.at<double>(a + n, b + n);
					sum1_b += input_mirror.at<Vec3d>(i + a, j + b)[2] * kernel.at<double>(a + n, b + n);
				}
			}

			output.at<Vec3d>(i - n, j - n)[0] = (double)max(sum1_r, max(sum1_g, sum1_b));
			output.at<Vec3d>(i - n, j - n)[1] = (double)max(sum1_r, max(sum1_g, sum1_b));
			output.at<Vec3d>(i - n, j - n)[2] = (double)max(sum1_r, max(sum1_g, sum1_b));

		}
	}

	return output;
}

//boundary processing method is fixed with mirroring
//input: intensity matrix of image, n: window radius
Mat Mirroring(const Mat input, int n)
{
	int row = input.rows;
	int col = input.cols;

	Mat input2 = Mat::zeros(row + 2 * n, col + 2 * n, input.type()); //fixed image
	int row2 = input2.rows;
	int col2 = input2.cols;

	//3 channel image-> Vec3d type
	for (int i = n; i < row + n; i++) {
		for (int j = n; j < col + n; j++) {
			input2.at<Vec3d>(i, j) = input.at<Vec3d>(i - n, j - n);
		}
	}
	for (int i = n; i < row + n; i++) {
		for (int j = 0; j < n; j++) {
			input2.at<Vec3d>(i, j) = input2.at<Vec3d>(i, 2 * n - j);
		}
		for (int j = col + n; j < col2; j++) {
			input2.at<Vec3d>(i, j) = input2.at<Vec3d>(i, 2 * col - 2 + 2 * n - j);
		}
	}
	for (int j = 0; j < col2; j++) {
		for (int i = 0; i < n; i++) {
			input2.at<Vec3d>(i, j) = input2.at<Vec3d>(2 * n - i, j);
		}
		for (int i = row + n; i < row2; i++) {
			input2.at<Vec3d>(i, j) = input2.at<Vec3d>(2 * row - 2 + 2 * n - i, j);
		}
	}

	return input2;
}

//generates gaussian filtering kernel
// n: kernel size is (2n+1)*(2n+1), sigma_t / sigma_s: standard deviation , normalize: normalize 여부
Mat get_Gaussian_Kernel(int n, double sigma_t, double sigma_s, bool normalize) {

	int kernel_size = (2 * n + 1);
	Mat kernel = Mat::zeros(kernel_size, kernel_size, CV_64F);
	double kernel_sum = 0.0;

	for (int i = -n; i <= n; i++) {
		for (int j = -n; j <= n; j++) {
			kernel.at<double>(i + n, j + n) = exp(-((i * i) / (2.0 * sigma_t * sigma_t) + (j * j) / (2.0 * sigma_s * sigma_s)));
			kernel_sum += kernel.at<double>(i + n, j + n);
		}
	}

	if (normalize) {
		for (int i = 0; i < kernel_size; i++)
			for (int j = 0; j < kernel_size; j++)
				kernel.at<double>(i, j) /= kernel_sum;		// normalize
	}

	return kernel;
}

//generate laplacian filtering kernel 
Mat get_Laplacian_Kernel() {

	Mat kernel = Mat::zeros(3, 3, CV_64F);

	kernel.at<double>(0, 1) = 1.0;
	kernel.at<double>(2, 1) = 1.0;
	kernel.at<double>(1, 0) = 1.0;
	kernel.at<double>(1, 2) = 1.0;
	kernel.at<double>(1, 1) = -4.0;

	return kernel;
}