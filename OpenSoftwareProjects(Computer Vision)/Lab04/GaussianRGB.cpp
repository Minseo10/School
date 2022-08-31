#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>       /* exp */
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
	output = gaussianfilter(input, 5, 1, 1, "zero-paddle"); //Boundary process: zero-paddle, mirroring, adjustkernel
	end = clock(); //시간 측정 끝
	result = (double)(end - start); //result: ms 단위의 시간차
	cout << "Gaussian Filter(RGB) time: "<<result<<"ms";


	namedWindow("Gaussian Filter", WINDOW_AUTOSIZE);
	imshow("Gaussian Filter", output);


	waitKey(0);

	return 0;
}

//gaussian filter function
//parameters
//input: intensity matrix of input image , n: filter kernel size is (2n+1)(2n+1) , sigmaT/sigmaS: standard deviation for x/y coordinate
//opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)
Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt) {

	Mat kernel;

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);
	int tempa;
	int tempb;
	float denom;
	float kernelvalue;

	// Initialiazing Kernel Matrix (w)
	kernel = Mat::zeros(kernel_size, kernel_size, CV_32F);

	denom = 0.0;
	for (int a = -n; a <= n; a++) {  // compute denominator value and elements of kernel
		for (int b = -n; b <= n; b++) {
			float value1 = exp(-(pow(a, 2) / (2 * pow(sigmaS, 2))) - (pow(b, 2) / (2 * pow(sigmaT, 2))));
			kernel.at<float>(a + n, b + n) = value1;
			denom += value1;
		}
	}

	for (int a = -n; a <= n; a++) {  // divide kernel with Denominator 
		for (int b = -n; b <= n; b++) {
			kernel.at<float>(a + n, b + n) /= denom;
		}
	}

	Mat output = Mat::zeros(row, col, input.type());

	//R,G,B 각각의 intensity에 대해 filtering을 해준다.
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			if (!strcmp(opt, "zero-paddle")) {
				float sum1_r = 0.0;
				float sum1_g = 0.0;
				float sum1_b = 0.0;
				for (int a = -n; a <= n; a++) {
					for (int b = -n; b <= n; b++) {
						kernelvalue = kernel.at<float>(a + n, b + n);
						if ((i + a <= row - 1) && (i + a >= 0) && (j + b <= col - 1) && (j + b >= 0)) { //if the pixel is not a border pixel
							sum1_r += kernelvalue * (float)(input.at<C>(i + a, j + b)[0]); //0:R, 1:G, 2:B
							sum1_g += kernelvalue * (float)(input.at<C>(i + a, j + b)[1]);
							sum1_b += kernelvalue * (float)(input.at<C>(i + a, j + b)[2]);
						}
					}
				}
				output.at<C>(i, j)[0] = (G)sum1_r;
				output.at<C>(i, j)[1] = (G)sum1_g;
				output.at<C>(i, j)[2] = (G)sum1_b;
			}

			else if (!strcmp(opt, "mirroring")) {
				float sum1_r = 0.0;
				float sum1_g = 0.0;
				float sum1_b = 0.0;
				for (int a = -n; a <= n; a++) { // for each kernel window
					for (int b = -n; b <= n; b++) {
						kernelvalue = kernel.at<float>(a + n, b + n);

						if (i + a > row - 1) {  //mirroring for the border pixels
							tempa = i - a;
						}
						else if (i + a < 0) {
							tempa = -(i + a);
						}
						else {
							tempa = i + a;
						}
						if (j + b > col - 1) {
							tempb = j - b;
						}
						else if (j + b < 0) {
							tempb = -(j + b);
						}
						else {
							tempb = j + b;
						}
						sum1_r += kernelvalue * (float)(input.at<C>(tempa, tempb)[0]);
						sum1_g += kernelvalue * (float)(input.at<C>(tempa, tempb)[1]);
						sum1_b += kernelvalue * (float)(input.at<C>(tempa, tempb)[2]);
					}
				}
				output.at<C>(i, j)[0] = (G)sum1_r;
				output.at<C>(i, j)[1] = (G)sum1_g;
				output.at<C>(i, j)[2] = (G)sum1_b;

			}



			else if (!strcmp(opt, "adjustkernel")) {
				float sum1_r = 0.0;
				float sum1_g = 0.0;
				float sum1_b = 0.0;
				float sum2 = 0.0;
				for (int a = -n; a <= n; a++) {
					for (int b = -n; b <= n; b++) {
						//w'(s,t) = (0<=i+a<=H-1 && 0<=j+t<=W-1 ? w(s,t) : 0 )
						kernelvalue = kernel.at<float>(a + n, b + n);
						if ((i + a <= row - 1) && (i + a >= 0) && (j + b <= col - 1) && (j + b >= 0)) {
							sum1_r += kernelvalue * (float)(input.at<C>(i + a, j + b)[0]);
							sum1_g += kernelvalue * (float)(input.at<C>(i + a, j + b)[1]);
							sum1_b += kernelvalue * (float)(input.at<C>(i + a, j + b)[2]);
							sum2 += kernelvalue;
						}

					}
				}
				output.at<C>(i, j)[0] = (G)(sum1_r / sum2);
				output.at<C>(i, j)[1] = (G)(sum1_g / sum2);
				output.at<C>(i, j)[2] = (G)(sum1_b / sum2);
			}
		}
	}
	return output;
}