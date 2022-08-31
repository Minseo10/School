#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>       /* exp */
#define IM_TYPE	CV_8UC3

using namespace cv;

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

Mat laplacianfilter(const Mat input);

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab04\\lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;
	Mat output;


	cvtColor(input, input_gray, CV_RGB2GRAY);


	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);
	output = laplacianfilter(input_gray); 

	namedWindow("Laplacian Filter", WINDOW_AUTOSIZE);
	imshow("Laplacian Filter", output);


	waitKey(0);

	return 0;
}

//laplacian filter function
//parameters-input: intensity matrix of input image
Mat laplacianfilter(const Mat input) {

	Mat kernel;

	int row = input.rows;
	int col = input.cols;
	int n = 1; // Laplacian Filter Kernel N -> (2n+1)*(2n+1) size
	int kernel_size = (2 * n + 1);
	int tempa, tempb; //used in mirroring for the border pixels

	// Initialiazing a Laplacian filter L with 3x3 size 
	kernel = Mat::zeros(kernel_size, kernel_size, CV_32F);
	kernel.at<float>(0, 0) = 0;
	kernel.at<float>(0, 1) = 1;
	kernel.at<float>(0, 2) = 0;
	kernel.at<float>(1, 0) = 1;
	kernel.at<float>(1, 1) = -4;
	kernel.at<float>(1, 2) = 1;
	kernel.at<float>(2, 0) = 0;
	kernel.at<float>(2, 1) = 1;
	kernel.at<float>(2, 2) = 0;

	Mat output = Mat::zeros(row, col, input.type());


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			float sum1 = 0.0; //sum of 2nd derivatives

			for (int a = -n; a <= n; a++) {
				for (int b = -n; b <= n; b++) {
					// Use mirroring boundary process

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

					sum1 += kernel.at<float>(a + n, b + n) * (float)(input.at<G>(tempa, tempb));
					
				}
			}

			output.at<G>(i, j) = 7*(G)abs(sum1); //O(x,y) = | L*I |
		}
	}
	return output;
}