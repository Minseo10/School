#include <iostream>
#include <opencv2/opencv.hpp>

#define IM_TYPE	CV_8UC3
typedef uchar G;
typedef cv::Vec3b C;
using namespace cv;


// Note that this code is for the case when an input data is a color value.
//input: color+pos(r,g,b)
int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab06\\lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat output;


	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", input);


	Mat samples(input.rows * input.cols, 3, CV_32F); //3은 3개의 채널(R,G,B)를 나타낸다
	//각 채널의 intensity를 samples에 저장
	for (int y = 0; y < input.rows; y++)
		for (int x = 0; x < input.cols; x++)
			for (int z = 0; z < 3; z++)
				samples.at<float>(y + x * input.rows, z) = input.at<C>(y, x)[z];

	// Clustering is performed for each channel (RGB)
	// Note that the intensity value is not normalized here (0~1). You should normalize both intensity and position when using them simultaneously.
	int clusterCount = 10;
	Mat labels;
	int attempts = 5;
	Mat centers;


	//samples: data for culstering, clusterCount: number of clusters to split the set by, lables: Input/output integer array that stores the cluster indices for every sample
	//TermCriteria(int type, int maxCount, double epsilon): type is the type of termination criteria, maxCount is the maximum number of iterations/elements, and epsilon is the the desired accuracy
	//attempts: Flag to specify the number of times the algorithm is executed using different initial labellings
    //centers: Output matrix of the cluster centers,  one row per each cluster center.
	kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);

	Mat new_image(input.size(), input.type());
	for (int y = 0; y < input.rows; y++)
		for (int x = 0; x < input.cols; x++)
		{
			//Fill code that finds for each pixel of each channel of the output image the intensity of the cluster center.
			int cluster_idx = labels.at<int>(y + x * input.rows, 0);
			new_image.at<C>(y, x)[0] = centers.at<float>(cluster_idx, 0);
			new_image.at<C>(y, x)[1] = centers.at<float>(cluster_idx, 1);
			new_image.at<C>(y, x)[2] = centers.at<float>(cluster_idx, 2);
		}
	imshow("clustered image", new_image);

	waitKey(0);

	return 0;
}

