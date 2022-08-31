#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

template <typename T>
Mat myrotate(const Mat input, float angle, const char* opt);

//for Nearest-neighbor interpolation
float R(float u) {
	if (u > -0.5 && u <= 0.5) return 1.0;
	else return 0.0;
}

int main()
{
	Mat input, rotated;

	// Read each image
	input = imread("C:\\Users\\MIN\\Desktop\\Lab02\\lena.jpg", IMREAD_COLOR);

	// Check for invalid input
	if (!input.data) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	//show original image
	namedWindow("image");
	imshow("image", input);

	//rotate the image
	rotated = myrotate<Vec3b>(input, 45, "bilinear");

	//show rotated image
	namedWindow("rotated");
	imshow("rotated", rotated);

	waitKey(0);

	return 0;
}

template <typename T>
Mat myrotate(const Mat input, float angle, const char* opt) {
	int row = input.rows;
	int col = input.cols;

	float radian = angle * CV_PI / 180;

	//size of a rectangle surrounding a rotated image
	float sq_row = ceil(row * sin(radian) + col * cos(radian));
	float sq_col = ceil(col * sin(radian) + row * cos(radian));

	//initialize output image-> sq_row행 sq_col열 input.type() 타입의 영행렬
	Mat output = Mat::zeros(sq_row, sq_col, input.type()); 

	//inverse warping with nearest neighbor / bilinear interpolation
	for (int i = 0; i < sq_row; i++) {
		for (int j = 0; j < sq_col; j++) {
			float x = (j - sq_col / 2) * cos(radian) - (i - sq_row / 2) * sin(radian) + col / 2;
			float y = (j - sq_col / 2) * sin(radian) + (i - sq_row / 2) * cos(radian) + row / 2;

			//nearset integer grid의 좌표를 구한다
			float y1 = floor(y);
			float y2 = ceil(y);
			float x1 = floor(x);
			float x2 = ceil(x);

			float mu = y - y1;
			float lambda = x - x1;
			
			if(y>=0 && y<=(row-1) && x>=0 && x <= (col-1)){
				//nearest neighbor interpolation -> use function R(u)
				if (!strcmp(opt, "nearest")) {

					output.at<T>(i, j) = R(lambda * (-1)) * (R(mu * (-1)) * input.at<T>(y1, x1) + R(1 - mu) * input.at<T>(y2, x1))
						+ R(1 - lambda) * (R(mu * (-1)) * input.at<T>(y1, x2) + R(1 - mu) * input.at<T>(y2, x2));

				}

				//bilinear interpolation
				else if (!strcmp(opt, "bilinear")) {

					output.at<T>(i, j) = lambda * (mu * input.at<T>(y2, x2) + (1 - mu) * input.at<T>(y1, x2)) +
						(1 - lambda) * (mu * input.at<T>(y2, x1) + (1 - mu) * input.at<T>(y1, x1)); 
		
				}
			}
		}
	}

	return output;
}
