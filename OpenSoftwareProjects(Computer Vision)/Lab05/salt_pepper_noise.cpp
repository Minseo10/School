#include <opencv2/opencv.hpp>
#include <stdio.h>
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

Mat Add_salt_pepper_Noise(const Mat input, float ps, float pp);
Mat Salt_pepper_noise_removal_Gray(const Mat input, int n, const char* opt);
Mat Salt_pepper_noise_removal_RGB(const Mat input, int n, const char* opt);

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\�ǹμ�\\�б�\\2022-1\\������\\Lab04\\lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;

	// check for validation
	if (!input.data) {
		printf("Could not open\n");
		return -1;
	}

	cvtColor(input, input_gray, CV_RGB2GRAY);	// convert RGB to Grayscale

	// Add noise to original image
	Mat noise_Gray = Add_salt_pepper_Noise(input_gray, 0.1f, 0.1f);
	Mat noise_RGB = Add_salt_pepper_Noise(input, 0.1f, 0.1f);

	// Denoise, using median filter
	int window_radius = 2;
	Mat Denoised_Gray = Salt_pepper_noise_removal_Gray(noise_Gray, window_radius, "zero-padding");
	Mat Denoised_RGB = Salt_pepper_noise_removal_RGB(noise_RGB, window_radius, "adjustkernel");

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("Impulse Noise (Grayscale)", WINDOW_AUTOSIZE);
	imshow("Impulse Noise (Grayscale)", noise_Gray);

	namedWindow("Impulse Noise (RGB)", WINDOW_AUTOSIZE);
	imshow("Impulse Noise (RGB)", noise_RGB);

    namedWindow("Denoised (Grayscale)", WINDOW_AUTOSIZE);
	imshow("Denoised (Grayscale)", Denoised_Gray);

	namedWindow("Denoised (RGB)", WINDOW_AUTOSIZE);
	imshow("Denoised (RGB)", Denoised_RGB);

	waitKey(0);

	return 0;
}

//generating an image with the salt-and-pepper noise
//parameters
//input: intensity matrix of the input image , ps: density of salt noise(0~1), pp: density of pepper noise(0~1)
Mat Add_salt_pepper_Noise(const Mat input, float ps, float pp)
{
	Mat output = input.clone();
	RNG rng; //random number

	int amount1 = (int)(output.rows * output.cols * pp); //# of pepper pixels
	int amount2 = (int)(output.rows * output.cols * ps); //# of salt pixels

	int x, y;

	// Grayscale image
	if (output.channels() == 1) {
		//rng.uniform(a,b) : returns uniformly distributed random integer in [a, b)
		for (int counter = 0; counter < amount1; ++counter)
			output.at<G>(rng.uniform(0, output.rows), rng.uniform(0, output.cols)) = 0; //generating pepper noises(in random position)

		for (int counter = 0; counter < amount2; ++counter)
			output.at<G>(rng.uniform(0, output.rows), rng.uniform(0, output.cols)) = 255; //generating salt noises(in random position)
	}

	// Color image	
	else if (output.channels() == 3) {
		for (int counter = 0; counter < amount1; ++counter) { //generating pepper noises (in random position)
			x = rng.uniform(0, output.rows);
			y = rng.uniform(0, output.cols);
			output.at<C>(x, y)[0] = 0;

			x = rng.uniform(0, output.rows);
			y = rng.uniform(0, output.cols);
			output.at<C>(x, y)[1] = 0;

			x = rng.uniform(0, output.rows);
			y = rng.uniform(0, output.cols);
			output.at<C>(x, y)[2] = 0;
		}

		for (int counter = 0; counter < amount2; ++counter) { //generating salt noises (in random position)
			x = rng.uniform(0, output.rows);
			y = rng.uniform(0, output.cols);
			output.at<C>(x, y)[0] = 255;

			x = rng.uniform(0, output.rows);
			y = rng.uniform(0, output.cols);
			output.at<C>(x, y)[1] = 255;

			x = rng.uniform(0, output.rows);
			y = rng.uniform(0, output.cols);
			output.at<C>(x, y)[2] = 255;
		}
	}

	return output;
}

//removing salt and pepper noise in grayscale image
//parameters
//input: intensity matrix of the noised image , n: filter kernel size is (2n+1)(2n+1), opt: boundary processing method
Mat Salt_pepper_noise_removal_Gray(const Mat input, int n, const char* opt) {

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);
	int median = 0;		// index of median value
	int tempa;
	int tempb;

	// initialize median filter kernel
	Mat kernel = Mat::zeros(kernel_size * kernel_size, 1, input.type());

	Mat output = Mat::zeros(row, col, input.type());

	// convolution
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			if (!strcmp(opt, "zero-padding")) {
				int idx = 0; //index at the filter kernel

				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						if ((i + x <= row - 1) && (i + x >= 0) && (j + y <= col - 1) && (j + y >= 0))
							kernel.at<G>(idx++, 0) = input.at<G>(i + x, j + y);
						else kernel.at<G>(idx++, 0) = 0;
					}
				}
				median = kernel_size * kernel_size / 2;

			}

			else if (!strcmp(opt, "mirroring")) {
				int idx = 0; //index at the filter kernel

				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						
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
						//push mirrored elements to the kernel
						kernel.at<G>(idx++, 0) = input.at<G>(tempa, tempb);
					}
				}
				median = kernel_size * kernel_size / 2;
				
			}

			else if (!strcmp(opt, "adjustkernel")) {
				int idx = 0; //index at the filter kernel

				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						//image boudary���� �ִ� �ȼ��鿡 ���ؼ��� median filtering �� �Ѵ�
						if ((i + x <= row - 1) && (i + x >= 0) && (j + y <= col - 1) && (j + y >= 0))
							kernel.at<G>(idx++, 0) = input.at<G>(i + x, j + y);
					}
				} 
				median = idx / 2;

			}

			// Sort the kernels in ascending order
			sort(kernel, kernel, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);

			//median value of the kernel will be output intensity
			output.at<G>(i, j) = kernel.at<G>(median, 0);
			}
		}

		return output;
	}
	
//removing salt and pepper noise in color image
//parameters
//input: intensity matrix of the noised image , n: filter kernel size is (2n+1)(2n+1), opt: boundary processing method
Mat Salt_pepper_noise_removal_RGB(const Mat input, int n, const char* opt) {

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);
	int median;	// index of median value
	int channel = input.channels();
	int tempa; int tempb;

	// initialize ( (TypeX with 3 channel) - (TypeX with 1 channel) = 16 )
	// ex) CV_8UC3 - CV_8U = 16
	Mat kernel = Mat::zeros(kernel_size * kernel_size, channel, input.type() - 16);

	Mat output = Mat::zeros(row, col, input.type());

	// convolution
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			if (!strcmp(opt, "zero-padding")) {
				int idx = 0; //index at filter kernel

				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						if ((i + x <= row - 1) && (i + x >= 0) && (j + y <= col - 1) && (j + y >= 0)) {
							kernel.at<G>(idx, 0) = input.at<C>(i + x, j + y)[0];
							kernel.at<G>(idx, 1) = input.at<C>(i + x, j + y)[1];
							kernel.at<G>(idx, 2) = input.at<C>(i + x, j + y)[2];
							idx++;
						}
						else {
							kernel.at<G>(idx, 0) = 0;
							kernel.at<G>(idx, 1) = 0;
							kernel.at<G>(idx, 2) = 0;
							idx++;
						}
						
					}
				}
				median = kernel_size * kernel_size / 2;
			}

			else if (!strcmp(opt, "mirroring")) {
				int idx = 0; //index at filter kernel
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
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
						//push mirrored elements to the kernel
						kernel.at<G>(idx, 0) = input.at<C>(tempa, tempb)[0];
						kernel.at<G>(idx, 1) = input.at<C>(tempa, tempb)[1];
						kernel.at<G>(idx, 2) = input.at<C>(tempa, tempb)[2];
						idx++;
					}
				}
				median = kernel_size * kernel_size / 2;
			}

			else if (!strcmp(opt, "adjustkernel")) {
				int idx = 0; //index at filter kernel
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						
						if ((i + x <= row - 1) && (i + x >= 0) && (j + y <= col - 1) && (j + y >= 0)) {
							kernel.at<G>(idx, 0) = input.at<C>(i + x, j + y)[0];
							kernel.at<G>(idx, 1) = input.at<C>(i + x, j + y)[1];
							kernel.at<G>(idx, 2) = input.at<C>(i + x, j + y)[2];
							idx++;
						}
					}
				}
				//image boudary���� �ִ� �ȼ��鿡 ���ؼ��� median filtering �� �Ѵ�
				median = idx / 2;
			}

			// Sort the kernels in ascending order
			sort(kernel, kernel, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);

			output.at<C>(i, j)[0] = kernel.at<G>(median, 0);
			output.at<C>(i, j)[1] = kernel.at<G>(median, 1);
			output.at<C>(i, j)[2] = kernel.at<G>(median, 2);
		}
	}

		return output;
} 
		