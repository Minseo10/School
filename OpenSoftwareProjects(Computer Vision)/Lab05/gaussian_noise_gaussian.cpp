#include <opencv2/opencv.hpp>
#include <stdio.h>
#define IM_TYPE	CV_64FC3

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


Mat Add_Gaussian_noise(const Mat input, double mean, double sigma);
Mat Gaussianfilter_Gray(const Mat input, int n, double sigma_t, double sigma_s, const char* opt);
Mat Gaussianfilter_RGB(const Mat input, int n, double sigma_t, double sigma_s, const char* opt);

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab04\\lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;

	// check for validation
	if (!input.data) {
		printf("Could not open\n");
		return -1;
	}

	cvtColor(input, input_gray, CV_RGB2GRAY);	// convert RGB to Grayscale

	// 8-bit unsigned char -> 64-bit floating point
	input.convertTo(input, CV_64FC3, 1.0 / 255);
	input_gray.convertTo(input_gray, CV_64F, 1.0 / 255);

	// Add noise to original image
	Mat noise_Gray = Add_Gaussian_noise(input_gray, 0, 0.1);
	Mat noise_RGB = Add_Gaussian_noise(input, 0, 0.1);

	// Denoise, using gaussian filter
	Mat Denoised_Gray = Gaussianfilter_Gray(noise_Gray, 3, 10, 10, "adjustkernel");
	Mat Denoised_RGB = Gaussianfilter_RGB(noise_RGB, 3, 10, 10, "adjustkernel");

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("Gaussian Noise (Grayscale)", WINDOW_AUTOSIZE);
	imshow("Gaussian Noise (Grayscale)", noise_Gray);

	namedWindow("Gaussian Noise (RGB)", WINDOW_AUTOSIZE);
	imshow("Gaussian Noise (RGB)", noise_RGB);

	namedWindow("Denoised (Grayscale)", WINDOW_AUTOSIZE);
	imshow("Denoised (Grayscale)", Denoised_Gray);

	namedWindow("Denoised (RGB)", WINDOW_AUTOSIZE);
	imshow("Denoised (RGB)", Denoised_RGB);

	waitKey(0);

	return 0;
}

//add gaussian noise to input
//input: intensity matrix of input image , mean: mean of the gaussian function , sigma: standard deviation
Mat Add_Gaussian_noise(const Mat input, double mean, double sigma) {

	Mat NoiseArr = Mat::zeros(input.rows, input.cols, input.type());
	RNG rng;

	//fills array with random numbers -> generate noise
	//if distType=NORMAL then third parameter is mean value, and fourth parameter is standard deviation
	rng.fill(NoiseArr, RNG::NORMAL, mean, sigma); 

	//add clean image and noise
	add(input, NoiseArr, NoiseArr); //add two matrix(input, NoiseArr) and save the result in NoiseArr

	return NoiseArr;
}

//removing gaussian noise with simple average filtering (gaussian filter)
//input: intensity matrix of noised image , n: filter kernel size is (2n+1)(2n+1) , sigma_t/sigma_s: standard deviation for x/y coordinate
//opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)
Mat Gaussianfilter_Gray(const Mat input, int n, double sigma_t, double sigma_s, const char* opt) {

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);
	int tempa;
	int tempb;
	float denom;
	float kernelvalue;

	// Initialiazing Gaussian Kernel Matrix
	Mat kernel = Mat::zeros(kernel_size, kernel_size, CV_32F);

	denom = 0.0;
	for (int a = -n; a <= n; a++) {  // compute denominator value and elements of kernel
		for (int b = -n; b <= n; b++) {
			float value1 = exp(-(pow(a, 2) / (2 * pow(sigma_s, 2))) - (pow(b, 2) / (2 * pow(sigma_t, 2))));
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

	// convolution
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			if (!strcmp(opt, "zero-padding")) {
				float sum1 = 0.0;
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						kernelvalue = kernel.at<float>(x + n, y + n);
						if ((i + x <= row - 1) && (i + x >= 0) && (j + y <= col - 1) && (j + y >= 0)) { //if the pixel is not a border pixel
							sum1 += kernelvalue * (float)(input.at<G>(i + x, j + y));
						}
					}
				}

				output.at<G>(i, j) = (G)sum1;
			}

			else if (!strcmp(opt, "mirroring")) {
				float sum1 = 0.0;
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {

						kernelvalue = kernel.at<float>(x + n, y + n);

						if (i + x > row - 1) {  //mirroring for the border pixels
							tempa = i - x;
						}
						else if (i + x < 0) {
							tempa = -(i + x);
						}
						else {
							tempa = i + x;
						}
						if (j + y > col - 1) {
							tempb = j - y;
						}
						else if (j + y < 0) {
							tempb = -(j + y);
						}
						else {
							tempb = j + y;
						}
						sum1 += kernelvalue * (float)(input.at<G>(tempa, tempb));
					}
				}
				output.at<G>(i, j) = (G)sum1;
			}

			else if (!strcmp(opt, "adjustkernel")) {
				float sum1 = 0.0;
				float sum2 = 0.0;
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						//w'(s,t) = (0<=i+a<=H-1 && 0<=j+t<=W-1 ? w(s,t) : 0 )
						kernelvalue = kernel.at<float>(x + n, y + n);
						if ((i + x <= row - 1) && (i + x >= 0) && (j + y <= col - 1) && (j + y >= 0)) {
							sum1 += kernelvalue * (float)(input.at<G>(i + x, j + y));
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

//removing gaussian noise with simple average filtering (gaussian filter)
//input: intensity matrix of noised image , n: filter kernel size is (2n+1)(2n+1) , sigma_s/sigma_t: standard deviation for x/y coordinate
//opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)
Mat Gaussianfilter_RGB(const Mat input, int n, double sigma_t, double sigma_s, const char* opt) {

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);
	int tempa;
	int tempb;
	float denom;
	float kernelvalue;

	// Initialiazing Gaussian Kernel Matrix
	Mat kernel = Mat::zeros(kernel_size, kernel_size, CV_32F);

	denom = 0.0;
	for (int x = -n; x <= n; x++) {  // compute denominator value and elements of kernel
		for (int y = -n; y <= n; y++) {
			float value1 = exp(-(pow(x, 2) / (2 * pow(sigma_s, 2))) - (pow(y, 2) / (2 * pow(sigma_t, 2))));
			kernel.at<float>(x + n, y + n) = value1;
			denom += value1;
		}
	}

	for (int x = -n; x <= n; x++) {  // divide kernel with Denominator 
		for (int y = -n; y <= n; y++) {
			kernel.at<float>(x + n, y + n) /= denom;
		}
	}
	

	Mat output = Mat::zeros(row, col, input.type());

	// convolution
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			if (!strcmp(opt, "zero-padding")) {
				float sum1_r = 0.0;
				float sum1_g = 0.0;
				float sum1_b = 0.0;
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						kernelvalue = kernel.at<float>(x + n, y + n);
						if ((i + x <= row - 1) && (i + x >= 0) && (j + y <= col - 1) && (j + y >= 0)) { //if the pixel is not a border pixel
							sum1_r += kernelvalue * (float)(input.at<C>(i + x, j + y)[0]); //0:R, 1:G, 2:B
							sum1_g += kernelvalue * (float)(input.at<C>(i + x, j + y)[1]);
							sum1_b += kernelvalue * (float)(input.at<C>(i + x, j + y)[2]);
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
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						kernelvalue = kernel.at<float>(x + n, y + n);

						if (i + x > row - 1) {  //mirroring for the border pixels
							tempa = i - x;
						}
						else if (i + x < 0) {
							tempa = -(i + x);
						}
						else {
							tempa = i + x;
						}
						if (j + y > col - 1) {
							tempb = j - y;
						}
						else if (j + y < 0) {
							tempb = -(j + y);
						}
						else {
							tempb = j + y;
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
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						//w'(s,t) = (0<=i+a<=H-1 && 0<=j+t<=W-1 ? w(s,t) : 0 )
						kernelvalue = kernel.at<float>(x + n, y + n);
						if ((i + x <= row - 1) && (i + x >= 0) && (j + y <= col - 1) && (j + y >= 0)) {
							sum1_r += kernelvalue * (float)(input.at<C>(i + x, j + y)[0]);
							sum1_g += kernelvalue * (float)(input.at<C>(i + x, j + y)[1]);
							sum1_b += kernelvalue * (float)(input.at<C>(i + x, j + y)[2]);
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