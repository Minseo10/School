#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab06\\lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;

	cvtColor(input, input_gray, CV_RGB2GRAY); // Converting image to gray

	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	imwrite("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab06\\lena_gray.jpg", input_gray);

	return 0;
}
