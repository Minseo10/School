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
Mat UnsharpMask(const Mat input, int n, float sigmaT, float sigmaS, const char* opt, float k);

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab04\\lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;
	Mat output;

	//convert input image into grayscale
	cvtColor(input, input_gray, CV_RGB2GRAY);


	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	output = UnsharpMask(input_gray, 5, 5, 5, "mirroring",0.5); //Boundary process: zero-paddle, mirroring, adjustkernel
	

	namedWindow("Unsharp Masking", WINDOW_AUTOSIZE);
	imshow("Unsharp Masking", output);


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


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			if (!strcmp(opt, "zero-paddle")) {
				float sum1 = 0.0;
				for (int a = -n; a <= n; a++) {
					for (int b = -n; b <= n; b++) {
						kernelvalue = kernel.at<float>(a + n, b + n);
						if ((i + a <= row - 1) && (i + a >= 0) && (j + b <= col - 1) && (j + b >= 0)) { //if the pixel is not a border pixel
							sum1 += kernelvalue * (float)(input.at<G>(i + a, j + b));
						}
					}
				}
				output.at<G>(i, j) = (G)sum1;
			}

			else if (!strcmp(opt, "mirroring")) {
				float sum1 = 0.0;
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
						sum1 += kernelvalue * (float)(input.at<G>(tempa, tempb));
					}
				}
				output.at<G>(i, j) = (G)sum1;

			}

			else if (!strcmp(opt, "adjustkernel")) {
				float sum1 = 0.0;
				float sum2 = 0.0;
				for (int a = -n; a <= n; a++) {
					for (int b = -n; b <= n; b++) {
						//w'(s,t) = (0<=i+a<=H-1 && 0<=j+t<=W-1 ? w(s,t) : 0 )
						kernelvalue = kernel.at<float>(a + n, b + n);
						if ((i + a <= row - 1) && (i + a >= 0) && (j + b <= col - 1) && (j + b >= 0)) {
							sum1 += kernelvalue * (float)(input.at<G>(i + a, j + b));
							sum2 += kernelvalue;
						}

					}
				}
				output.at<G>(i, j) = (G)(sum1 / sum2);
			}
		}
	}
	return output;
}


//unsharp masking function
//parameters
//input: intensity matrix of input image , n: filter kernel size is (2n+1)(2n+1) , sigmaT/sigmaS: standard deviation for x/y coordinate
//opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel) , k: scaling constant(0<=k<=1)
//as the k increases, input image looks sharper
Mat UnsharpMask(const Mat input, int n, float sigmaT, float sigmaS, const char* opt, float k) {

	int row = input.rows;
	int col = input.cols;

	Mat L = Mat::zeros(row, col, input.type()); //Low-pass filtered image matrix
	L= gaussianfilter(input, n, sigmaT, sigmaS, opt); //Low-pass filtering with gaussian filter

	Mat output = Mat::zeros(row, col, input.type()); //output image with unsharp masking
	output = (input - k * L) / (1 - k);

	return output;
}