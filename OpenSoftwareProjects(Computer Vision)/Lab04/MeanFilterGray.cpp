#include <iostream>
#include <opencv2/opencv.hpp>

#define IM_TYPE	CV_8UC3

using namespace std;
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

Mat meanfilter(const Mat input, int n, const char* opt);

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab04\\lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;
	Mat output;

	cvtColor(input, input_gray, CV_RGB2GRAY); // Converting image to gray


	if (!input.data)
	{
		cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);
	output = meanfilter(input_gray, 3, "adjustkernel"); //Boundary process: zero-paddle, mirroring, adjustkernel

	namedWindow("Mean Filter", WINDOW_AUTOSIZE);
	imshow("Mean Filter", output);


	waitKey(0);

	return 0;
}


//parameters
//input: intput matrix , n: filter kernel size is (2n+1)(2n+1) , opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)
Mat meanfilter(const Mat input, int n, const char* opt) {

	Mat kernel;

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1); //s=[-n, n] , t=[-n, n]
	int tempa;
	int tempb;

	// Initialiazing Kernel Matrix 
	//ones(rows, cols, type): rows행 cols열의 type 타입 모든 원소가 1인 행렬 반환
	kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size * kernel_size); 
	float kernelvalue = kernel.at<float>(0, 0);  // To simplify, as the filter is uniform. All elements of the kernel value are same.(kernel의 모든 원소 값 same)

	Mat output = Mat::zeros(row, col, input.type());


	for (int i = 0; i < row; i++) { //for each pixel in the output
		for (int j = 0; j < col; j++) {

			if (!strcmp(opt, "zero-paddle")) {
				float sum1 = 0.0;
				for (int a = -n; a <= n; a++) { // for each kernel window(a,b는 시그마에서의 s,t)
					for (int b = -n; b <= n; b++) {
						
						// (i,j)가 image boundary에 있을 경우: (2n+1)(2n+1)window에 있는 픽셀 중 image boundary 밖에 있는 픽셀은 
						// 곱해지는 kernal element가 어차피 0이라 고려할필요x
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
				for (int a = -n; a <= n; a++) { // for each kernel window
					for (int b = -n; b <= n; b++) { 
						//w'(s,t) = (0<=i+a<=H-1 && 0<=j+t<=W-1 ? w(s,t) : 0 )
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