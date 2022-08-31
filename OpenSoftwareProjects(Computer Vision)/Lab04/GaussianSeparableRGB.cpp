#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>       /* exp */
#include <time.h>  //for clock() function
#define IM_TYPE	CV_8UC3

using namespace cv;
using namespace std;

// Image Type
// "G" for GrayScale Image, "C" for Color Image
#if (IM_TYPE == CV_8UC3)
typedef uchar G;
typedef cv::Vec3b C;
#elif (IM_TYPE == CV_16SC3)
typedef short G;
typedef Vec3s C;
#elif (IM_TYPE == CV_32SC3)
typedef int G;
typedef Vec3i C;
#elif (IM_TYPE == CV_32FC3)
typedef float G;
typedef Vec3f C;
#elif (IM_TYPE == CV_64FC3)
typedef double G;
typedef Vec3d C;
#endif

Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt);

int main() {
	clock_t start, end;
	double result;

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab04\\lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat output;


	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", input);
	start = clock(); //시간 측정 시작
	output = gaussianfilter(input, 5, 1, 1, "adjustkernel"); //Boundary process: zero-paddle, mirroring, adjustkernel

	end = clock(); //시간 측정 끝
	result = (double)(end - start); //result: ms 단위의 시간차
	cout << "Gaussian Separable Filter(RGB) time: " << result << "ms";

	namedWindow("Gaussian Separable Filter", WINDOW_AUTOSIZE);
	imshow("Gaussian Separable Filter", output);


	waitKey(0);

	return 0;
}

//gaussian separable filter function(RGB)
//parameters
//input: intensity matrix of input image , n: filter kernel size is (2n+1)(2n+1) , sigmaT/sigmaS: standard deviation for x/y coordinate
//opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)
Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt) {

	Mat kernel_s; Mat kernel_t;

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);
	int tempa;
	int tempb;
	float denom_s; float denom_t;
	float kernelvalue;

	// Initialiazing Kernel Matrix Ws(s)
	kernel_s = Mat::zeros(kernel_size, 1, CV_32F);

	denom_s = 0.0;
	for (int a = -n; a <= n; a++) {  // compute denominator value and elements of kernel
		float value1 = exp(-(pow(a, 2) / (2 * pow(sigmaS, 2))));
		kernel_s.at<float>(a + n, 0) = value1;
		denom_s += value1;
	}

	for (int a = -n; a <= n; a++) {  // divide kernel with Denominator 
		kernel_s.at<float>(a + n, 0) /= denom_s;
	}

	// Initialiazing Kernel Matrix Wt(t)
	kernel_t = Mat::zeros(1, kernel_size, CV_32F);

	denom_t = 0.0;
	for (int a = -n; a <= n; a++) {  // compute denominator value and elements of kernel
		float value2 = exp(-(pow(a, 2) / (2 * pow(sigmaT, 2))));
		kernel_t.at<float>(0, a + n) = value2;
		denom_t += value2;
	}

	for (int a = -n; a <= n; a++) {  // divide kernel with Denominator 
		kernel_t.at<float>(0, a + n) /= denom_t;
	}

	Mat output = Mat::zeros(row, col, input.type());
	Mat temp = Mat::zeros(row, col, input.type());

	if (!strcmp(opt, "zero-paddle")) {

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				float sum_r = 0.0;
				float sum_g = 0.0;
				float sum_b = 0.0;

				for (int b = -n; b <= n; b++) {
					if ((j + b <= col - 1) && (j + b >= 0)) { //if the pixel is not a border pixel
						sum_r += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i, j + b)[0]);
						sum_g += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i, j + b)[1]);
						sum_b += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i, j + b)[2]);
					}
				}
				temp.at<C>(i, j)[0] = (G)sum_r;
				temp.at<C>(i, j)[1] = (G)sum_g;
				temp.at<C>(i, j)[2] = (G)sum_b;
			}
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				float sum_r = 0.0;
				float sum_g = 0.0;
				float sum_b = 0.0;

				for (int a = -n; a <= n; a++) {
					if ((i + a <= row - 1) && (i + a >= 0)) {
						sum_r += kernel_s.at<float>(a + n, 0) * (float)temp.at<C>(i + a, j)[0];
						sum_g += kernel_s.at<float>(a + n, 0) * (float)temp.at<C>(i + a, j)[1];
						sum_b += kernel_s.at<float>(a + n, 0) * (float)temp.at<C>(i + a, j)[2];
					}
				}

				output.at<C>(i, j)[0] = (G)sum_r;
				output.at<C>(i, j)[1] = (G)sum_g;
				output.at<C>(i, j)[2] = (G)sum_b;
			}
		}
	}


	else if (!strcmp(opt, "mirroring")) {

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				float sum_r = 0.0;
				float sum_g = 0.0;
				float sum_b = 0.0;

				for (int b = -n; b <= n; b++) {

					if (j + b > col - 1) {
						tempb = j - b;
					}
					else if (j + b < 0) {
						tempb = -(j + b);
					}
					else {
						tempb = j + b;
					}
					sum_r += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i, tempb)[0]);
					sum_g += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i, tempb)[1]);
					sum_b += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i, tempb)[2]);
				}
				temp.at<C>(i, j)[0] = (G)sum_r;
				temp.at<C>(i, j)[1] = (G)sum_g;
				temp.at<C>(i, j)[2] = (G)sum_b;
			}
		}

		for (int i = 0;i < row;i++) {
			for (int j = 0;j < col;j++) {
				float sum_r = 0.0;
				float sum_g = 0.0;
				float sum_b = 0.0;

				for (int a = -n;a <= n;a++) {
					if (i + a > row - 1) {  //mirroring for the border pixels
						tempa = i - a;
					}
					else if (i + a < 0) {
						tempa = -(i + a);
					}
					else {
						tempa = i + a;
					}
					sum_r += kernel_s.at<float>(a + n, 0) * (float)temp.at<C>(tempa, j)[0];
					sum_g += kernel_s.at<float>(a + n, 0) * (float)temp.at<C>(tempa, j)[1];
					sum_b += kernel_s.at<float>(a + n, 0) * (float)temp.at<C>(tempa, j)[2];

				}
				output.at<C>(i, j)[0] = (G)sum_r;
				output.at<C>(i, j)[1] = (G)sum_g;
				output.at<C>(i, j)[2] = (G)sum_b;
			}
		}

	}



	else if (!strcmp(opt, "adjustkernel")) {

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				float sum_r = 0.0;
				float sum_g = 0.0;
				float sum_b = 0.0;
				float sum_kernel = 0.0;

				for (int b = -n; b <= n; b++) {
					//w'(s,t) = (0<=i+a<=H-1 && 0<=j+t<=W-1 ? w(s,t) : 0 )

					if ((j + b <= col - 1) && (j + b >= 0)) {
						sum_r += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i, j + b)[0]);
						sum_g += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i, j + b)[1]);
						sum_b += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i, j + b)[2]);
						sum_kernel += kernel_t.at<float>(0, b + n);
					}

				}

				temp.at<C>(i, j)[0] = (G)(sum_r / sum_kernel);
				temp.at<C>(i, j)[1] = (G)(sum_g / sum_kernel);
				temp.at<C>(i, j)[2] = (G)(sum_b / sum_kernel);
			}
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				float sum_r = 0.0;
				float sum_g = 0.0;
				float sum_b = 0.0;
				float sum_kernel = 0.0;

				for (int a = -n; a <= n; a++) {
					//w'(s,t) = (0<=i+a<=H-1 && 0<=j+t<=W-1 ? w(s,t) : 0 )

					if ((i + a <= row - 1) && (i + a >= 0)) {
						sum_r += kernel_s.at<float>(a + n, 0) * (float)temp.at<C>(i + a, j)[0];
						sum_g += kernel_s.at<float>(a + n, 0) * (float)temp.at<C>(i + a, j)[1];
						sum_b += kernel_s.at<float>(a + n, 0) * (float)temp.at<C>(i + a, j)[2];
						sum_kernel += kernel_s.at<float>(a + n, 0);
					}

				}

				output.at<C>(i, j)[0] = (G)(sum_r / sum_kernel);
				output.at<C>(i, j)[1] = (G)(sum_g / sum_kernel);
				output.at<C>(i, j)[2] = (G)(sum_b / sum_kernel);
			}
		}

	}
	return output;
}
