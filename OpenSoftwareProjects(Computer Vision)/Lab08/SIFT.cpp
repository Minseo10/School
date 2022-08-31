#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#define RATIO_THR 0.4 //ratio threshold

using namespace std;
using namespace cv;

double euclidDistance(Mat& vec1, Mat& vec2);
int nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors);
void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
	vector<KeyPoint>& keypoints2, Mat& descriptors2,
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool crossCheck, bool ratio_threshold);

int main() {

	Mat input1 = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab08\\input1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input2 = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab08\\input2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input1_gray, input2_gray;

	if (!input1.data || !input2.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	//resize(input1, input1, Size(input1.cols / 2, input1.rows / 2));
	//resize(input2, input2, Size(input2.cols / 2, input2.rows / 2));

	cvtColor(input1, input1_gray, CV_RGB2GRAY);
	cvtColor(input2, input2_gray, CV_RGB2GRAY);

	FeatureDetector* detector = new SiftFeatureDetector(
		0,		// nFeatures
		4,		// nOctaveLayers 
		0.04,	// contrastThreshold 
		10,		// edgeThreshold 
		1.6		// sigma
	);

	DescriptorExtractor* extractor = new SiftDescriptorExtractor();

	// Create a image for displaying mathing keypoints
	Size size = input2.size();
	Size sz = Size(size.width + input1_gray.size().width, max(size.height, input1_gray.size().height));
	Mat matchingImage = Mat::zeros(sz, CV_8UC3);

	input1.copyTo(matchingImage(Rect(size.width, 0, input1_gray.size().width, input1_gray.size().height)));
	input2.copyTo(matchingImage(Rect(0, 0, size.width, size.height)));

	// Compute keypoints and descriptor from the source image in advance
	// KeyPoint class instance stores a keypoint found by keypoint detectors such as Harris Corner Detector, SIFT,... etc.
	vector<KeyPoint> keypoints1; //keypoints and descriptors in image 1
	Mat descriptors1;

	detector->detect(input1_gray, keypoints1); //detect keypoints in an image
	extractor->compute(input1_gray, keypoints1, descriptors1); //compute descriptors for a set of keypoint in an image
	printf("input1 : %d keypoints are found.\n", (int)keypoints1.size());

	vector<KeyPoint> keypoints2; //keypoints and descriptors in image2
	Mat descriptors2;

	// Detect keypoints
	detector->detect(input2_gray, keypoints2);
	extractor->compute(input2_gray, keypoints2, descriptors2);

	printf("input2 : %zd keypoints are found.\n", keypoints2.size());

	//visualize each keypoints at image1 and image2
	for (int i = 0; i < keypoints1.size(); i++) {
		KeyPoint kp = keypoints1[i];
		kp.pt.x += size.width; //kp.pt.x 는 keypoint의 x coordinate
		circle(matchingImage, kp.pt, cvRound(kp.size * 0.25), Scalar(255, 255, 0), 1, 8, 0);
	}

	for (int i = 0; i < keypoints2.size(); i++) {
		KeyPoint kp = keypoints2[i];
		circle(matchingImage, kp.pt, cvRound(kp.size * 0.25), Scalar(255, 255, 0), 1, 8, 0);
	}

	// Find nearest neighbor pairs
	vector<Point2f> srcPoints;
	vector<Point2f> dstPoints;
	bool crossCheck = true; //cross-checking method 여부
	bool ratio_threshold = true; //ratio-based thresholding 여부
	findPairs(keypoints2, descriptors2, keypoints1, descriptors1, srcPoints, dstPoints, crossCheck, ratio_threshold); 
	printf("%zd keypoints are matched.\n", srcPoints.size());

	// Draw line between nearest neighbor pairs
	for (int i = 0; i < (int)srcPoints.size(); ++i) {
		Point2f pt1 = srcPoints[i]; 
		Point2f pt2 = dstPoints[i]; 
		Point2f from = pt1;
		Point2f to = Point(size.width + pt2.x, pt2.y);
		line(matchingImage, from, to, Scalar(0, 0, 255)); //draw line
	}

	// Display matching image
	namedWindow("Matching");
	imshow("Matching", matchingImage);

	waitKey(0);

	return 0;
}


//Calculate euclid distance
//vec1, vec2: two matrices. we will calculate euclid distance between them
double euclidDistance(Mat& vec1, Mat& vec2) {
	double sum = 0.0;
	int dim = vec1.cols;
	for (int a = 0; a < dim; a++) {
		sum += (vec1.at<float>(0, a) - vec2.at<float>(0, a)) * (vec1.at<float>(0, a) - vec2.at<float>(0, a));
	}

	return sqrt(sum);
}

// Find the index of nearest neighbor point from keypoints.
// vec: descriptor for fi, keypoints: g1~gm, descriptors: descriptors of g
int nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors) {
	int neighbor = -1;
	double minDist = 1e6; //minimum distance between fi and gj

	for (int i = 0; i < descriptors.rows; i++) {
		Mat v = descriptors.row(i);		// each row of descriptor
		if (euclidDistance(vec, v) < minDist) {
			minDist = euclidDistance(vec, v);
			neighbor = i;
		}

	}

	return neighbor;
}


//Find pairs of points with the smallest distace between them and save them in srcPoints, dstPoints
void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
	vector<KeyPoint>& keypoints2, Mat& descriptors2,
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool crossCheck, bool ratio_threshold) {
	for (int i = 0; i < descriptors1.rows; i++) {
		KeyPoint pt1 = keypoints1[i];
		Mat desc1 = descriptors1.row(i);
		
		int nn = nearestNeighbor(desc1, keypoints2, descriptors2);

		// Refine matching points using ratio_based thresholding
		if (ratio_threshold) {
			int neighbor = -1;
			double secondMinDist = 1e6; //second minimum distance between fi and gj

			for (int j = 0; j < descriptors2.rows; j++) {
				Mat v = descriptors2.row(j);		// each row of descriptor
				Mat k1 = descriptors2.row(nn); //row that has minimum distance
				if (euclidDistance(desc1, k1)<euclidDistance(desc1, v) < secondMinDist) {
					secondMinDist = euclidDistance(desc1, v);
					neighbor = j;
				}

			}
			int nn2 = neighbor; //index of second nearest neighbor point

			Mat k1 = descriptors2.row(nn); Mat k2 = descriptors2.row(nn2);
			if ((double)(euclidDistance(desc1, k1) / euclidDistance(desc1, k2)) >= RATIO_THR) //if ratio < threshold then it is reliable match, otherwise unreliable
				continue;
		}

		// Refine matching points using cross-checking
		if (crossCheck) {
			Mat desc2 = descriptors2.row(nn);
			int l = nearestNeighbor(desc2, keypoints1, descriptors1);

			if (i != l) //if unreliable match- 해당 match를 저장하지 않고 다음 pair 로 넘어간다
				continue;
		}

		KeyPoint pt2 = keypoints2[nn];
		srcPoints.push_back(pt1.pt);
		dstPoints.push_back(pt2.pt);
	}
}