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
	vector<KeyPoint>& keypoints2, Mat& descriptors2, vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool crossCheck, bool ratio_threshold);
template <typename T>
Mat cal_affine(vector<Point2f> ptl, vector<Point2f> ptr, int number_of_points);
void blend_stitching(const Mat I1, const Mat I2, Mat& I_f, int diff_x, int diff_y, float alpha);

int main() {

	Mat I1 = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab08\\input1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat I2 = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab08\\input2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat I1_gray, I2_gray;

	if (!I1.data || !I2.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	//resize(I1, I1, Size(I1.cols / 2, I1.rows / 2));
	//resize(I2, I2, Size(I2.cols / 2, I2.rows / 2));

	cvtColor(I1, I1_gray, CV_RGB2GRAY);
	cvtColor(I2, I2_gray, CV_RGB2GRAY);

	// 1.feature matching
	/****************************************************************************/
	FeatureDetector* detector = new SiftFeatureDetector(0, 4, 0.04, 10, 1.6);

	DescriptorExtractor* extractor = new SiftDescriptorExtractor();

	// Compute keypoints and descriptor from the source image in advance
	// KeyPoint class instance stores a keypoint found by keypoint detectors such as Harris Corner Detector, SIFT,... etc.
	vector<KeyPoint> keypoints1; //keypoints and descriptors in image 1
	Mat descriptors1;
	detector->detect(I1_gray, keypoints1); //detect keypoints in an image
	extractor->compute(I1_gray, keypoints1, descriptors1); //compute descriptors for a set of keypoint in an image
	printf("I1 : %d keypoints are found.\n", (int)keypoints1.size());

	vector<KeyPoint> keypoints2; //keypoints and descriptors in image2
	Mat descriptors2;
	detector->detect(I2_gray, keypoints2);
	extractor->compute(I2_gray, keypoints2, descriptors2);
	printf("I2 : %zd keypoints are found.\n", keypoints2.size());

	// Find nearest neighbor pairs (use cross-checking and ratio-based thresholding)
	vector<Point2f> srcPoints; //I1
	vector<Point2f> dstPoints; //I2
	bool crossCheck = true; //cross-checking method 여부
	bool ratio_threshold = true; //ratio-based thresholding 여부
	findPairs(keypoints2, descriptors2, keypoints1, descriptors1, srcPoints, dstPoints, crossCheck, ratio_threshold);
	printf("%zd keypoints are matched.\n", srcPoints.size());
	/****************************************************************************/

	// 2.affine transform estimation
	/****************************************************************************/
	I1.convertTo(I1, CV_32FC3, 1.0 / 255);
	I2.convertTo(I2, CV_32FC3, 1.0 / 255);

	// height(row), width(col) of each image
	const float I1_row = I1.rows;
	const float I1_col = I1.cols;
	const float I2_row = I2.rows;
	const float I2_col = I2.cols;

	// calculate affine Matrix A12, A21
	Mat A12 = cal_affine<float>(dstPoints, srcPoints, (int)dstPoints.size());
	Mat A21 = cal_affine<float>(srcPoints, dstPoints, (int)srcPoints.size());
	/****************************************************************************/

	// 3. Perform image stitching
	/****************************************************************************/
	// compute corners (p1, p2, p3, p4) using A21
	//A21.at<float>(0), ..., A21.at<float>(5)는 affine matrix A21의 a,b,c,d,e,f
	Point2f p1(A21.at<float>(0) * 0 + A21.at<float>(1) * 0 + A21.at<float>(2), A21.at<float>(3) * 0 + A21.at<float>(4) * 0 + A21.at<float>(5));
	Point2f p2(A21.at<float>(0) * 0 + A21.at<float>(1) * I2_row + A21.at<float>(2), A21.at<float>(3) * 0 + A21.at<float>(4) * I2_row + A21.at<float>(5));
	Point2f p3(A21.at<float>(0) * I2_col + A21.at<float>(1) * I2_row + A21.at<float>(2), A21.at<float>(3) * I2_col + A21.at<float>(4) * I2_row + A21.at<float>(5));
	Point2f p4(A21.at<float>(0) * I2_col + A21.at<float>(1) * 0 + A21.at<float>(2), A21.at<float>(3) * I2_col + A21.at<float>(4) * 0 + A21.at<float>(5));

	// compute boundary for merged image(I_f)
	int bound_u = (int)round(min(0.0f, min(p1.y, p4.y)));
	int bound_b = (int)round(max(I1_row - 1, max(p2.y, p3.y)));
	int bound_l = (int)round(min(0.0f, min(p1.x, p2.x)));
	int bound_r = (int)round(max(I1_col - 1, max(p3.x, p4.x)));


	// initialize merged image
	Mat I_f(bound_b - bound_u + 1, bound_r - bound_l + 1, CV_32FC3, Scalar(0));

	// inverse warping with bilinear interplolation using A12
	for (int i = bound_u; i <= bound_b; i++) {
		for (int j = bound_l; j <= bound_r; j++) {
			float x = A12.at<float>(0) * j + A12.at<float>(1) * i + A12.at<float>(2) - bound_l;
			float y = A12.at<float>(3) * j + A12.at<float>(4) * i + A12.at<float>(5) - bound_u;

			//nearest integer grid
			float y1 = floor(y);
			float y2 = ceil(y);
			float x1 = floor(x);
			float x2 = ceil(x);

			float mu = y - y1;
			float lambda = x - x1;

			if (x1 >= 0 && x2 < I2_col && y1 >= 0 && y2 < I2_row)
				I_f.at<Vec3f>(i - bound_u, j - bound_l) = lambda * (mu * I2.at<Vec3f>(y2, x2) + (1 - mu) * I2.at<Vec3f>(y1, x2)) +
				(1 - lambda) * (mu * I2.at<Vec3f>(y2, x1) + (1 - mu) * I2.at<Vec3f>(y1, x1));
		}
	}

	// image stitching with blend
	blend_stitching(I1, I2, I_f, bound_l, bound_u, 0.5);

	//show l1,l2, and stitched image
	namedWindow("Left Image(input1)");
	imshow("Left Image(input1)", I1);

	namedWindow("Right Image(input2)");
	imshow("Right Image(input2)", I2);

	namedWindow("result");
	imshow("result", I_f);

	//convert l_f into :l_f*alpha + beta 
	//alpha=255.0 , beta= 0.0(default parameter)
	I_f.convertTo(I_f, CV_8UC3, 255.0);
	imwrite("result.png", I_f);

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
	vector<KeyPoint>& keypoints2, Mat& descriptors2, vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool crossCheck, bool ratio_threshold) {
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
				if (euclidDistance(desc1, k1) < euclidDistance(desc1, v) < secondMinDist) {
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

//parameter: corresponding pixels, number of points
//return x= (M^T * M)^(−1) * M^T * b -> we can find a,b,c,d,e,f of affine matrix A
template <typename T>
Mat cal_affine(vector<Point2f> ptl, vector<Point2f> ptr, int number_of_points) {

	Mat M(2 * number_of_points, 6, CV_32F, Scalar(0));
	Mat b(2 * number_of_points, 1, CV_32F);

	Mat M_trans, temp, affineM;

	// initialize matrix
	for (int i = 0; i < number_of_points; i++) {
		M.at<T>(2 * i, 0) = ptl[i].x;		M.at<T>(2 * i, 1) = ptl[i].y;		M.at<T>(2 * i, 2) = 1;
		M.at<T>(2 * i + 1, 3) = ptl[i].x;		M.at<T>(2 * i + 1, 4) = ptl[i].y;		M.at<T>(2 * i + 1, 5) = 1;
		b.at<T>(2 * i) = ptr[i].x;		b.at<T>(2 * i + 1) = ptr[i].y;
	}

	// (M^T * M)^(−1) * M^T * b ( * : Matrix multiplication)
	transpose(M, M_trans);
	invert(M_trans * M, temp);
	affineM = temp * M_trans * b;

	return affineM;
}

//parameter: I1, I2 merge 할 image 2개 
//I_f: merge한 image를 저장 
//bound_l, bound_u: boundary for merged image(I_f)
//alpha: I1,I2를 blend할 때 alpha*I1 + (1-alpha)*I2 이용
void blend_stitching(const Mat I1, const Mat I2, Mat& I_f, int bound_l, int bound_u, float alpha) {

	int col = I_f.cols;
	int row = I_f.rows;

	// I2 is already in I_f by inverse warping
	for (int i = 0; i < I1.rows; i++) {
		for (int j = 0; j < I1.cols; j++) {
			bool cond_I2 = I_f.at<Vec3f>(i - bound_u, j - bound_l) != Vec3f(0, 0, 0) ? true : false;

			if (cond_I2) //if both l1, l2 are valid
				I_f.at<Vec3f>(i - bound_u, j - bound_l) = alpha * I1.at<Vec3f>(i, j) + (1 - alpha) * I_f.at<Vec3f>(i - bound_u, j - bound_l);
			else //if only l1 is valid
				I_f.at<Vec3f>(i - bound_u, j - bound_l) = I1.at<Vec3f>(i, j);

		}
	}
}