*SIFT.cpp*
1. double euclidDistance(Mat& vec1, Mat& vec2)
: Calculate euclid distance
parameters
-vec1, vec2: two matrices. we will calculate euclid distance between them

variables
-sum: sum of squared difference of each coordiante
-dim: # of columns of vec1(vec2)


2. int nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors)
: Find the index of nearest neighbor point from keypoints.
parameters
-vec: descriptor for fi (one keypoint in first image I1)
-keypoints: g1~gm(keypoints in second image I2)
-descriptors: descriptor for each keypoint in I2

variables
-neighbor: index of nearest neighbor point
-minDist: minimum euclidean distance between fi and each keypoint in g


3. void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
	vector<KeyPoint>& keypoints2, Mat& descriptors2,
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool crossCheck, bool ratio_threshold)
: Find pairs of points with the smallest distace between them and save them in srcPoints, dstPoints
parameters
-keypoints1, descriptors1: keypoints and descriptors of src image
-keypoints2, descriptors2: keypoints and descriptors of dst image
-srcPoints: pairs of points with the smallest distance in src image
-dstPoints: pairs of points with the smallest distance in dst image
-crossCheck: if cross-checking method is used, then 'true'. Otherwise, 'false'.
-ratio_threshold:  if ratio-based thresholding is used, then 'true'. Otherwise, 'false'.

variables
-desc1: descriptor of each keypoint in src image
-nn: index of nearest neighbor point in dst image from i-th keypoint of src image
-secondMinDist: second minimum distance between i-th keypoint in src image and each keypoint in dst image
-nn2:  index of second nearest neighbor point in dst image from ith keypoint of src image
-k1, k2: descriptors of nn-th and nn2-th keypoint
-desc2: descriptor of each keypoint in dst image
-l: ndex of nearest neighbor point in src image from nn-th keypoint of dst image
-pt1, pt2: each keypoints in keypoints1 and keypoints2.


4. int main()
variables
-matchingImage: result image
-keypoints1, descriptors1, keypoints2, descriptors2: : keypoints and descriptors of "image1.jpg" & "image2.jpg"
-srcPoints, dstPoints: nearest neighbor pairs are saved in this vectors
-crossCheck: if cross-checking method is used, then 'true'. Otherwise, 'false'.
-ratio_threshold:  if ratio-based thresholding is used, then 'true'. Otherwise, 'false'.


5. void cv::FeatureDetector::detect(const cv::Mat &image, std::vector<cv::KeyPoint> &keypoints, const cv::Mat &mask = cv::Mat()) 
: detect keypoints in an image.

parameters
-image:	Image.
-keypoints:	The detected keypoints. In the second variant of the method keypoints[i] is a set of keypoints detected in images[i] .
-mask: 	Mask specifying where to look for keypoints (optional). It must be a 8-bit integer matrix with non-zero values in the region of interest.


6. void cv::DescriptorExtractor::compute(const cv::Mat &image, std::vector<cv::KeyPoint> &keypoints, cv::Mat &descriptors)
: Computes the descriptors for a set of keypoints detected in an image or image set 

parameters
-image:	Image.
-keypoints:	Input collection of keypoints. Keypoints for which a descriptor cannot be computed are removed. 
-descriptors:	Computed descriptors. Row j is the keypoints (or keypoints[i]) is the descriptor for keypoint j-th keypoint.



*SURF_Homography.cpp*
1. int main(int argc, char** argv)
parameters
-argc: # of elements in 'argv'
-argv: 명령 인수. 

variables
-keypoints_object, keypoints_scene: keypoints of img_object and img_scene
-descriptors_object, descriptors_scene: descriptors of img_object and img_scene
-matcher: matched descriptor vectors
-matches: 
-min_dist, max_dist: max and min distances between keypoints
-good_matches: vectors of good matches
-img_matches: draw matches of keypoints from two images on 'img_matches'
-H: best-fit perspective transformation mapping obj to scene
-obj_corners: corners from the image_1


2. compute(), detect() : *SIFT.cpp*의 5번 6번 참고

3. void cv::DescriptorMatcher::match (InputArray queryDescriptors, 
InputArray trainDescriptors, std::vector< DMatch >& matches, InputArray mask = noArray() )
: finds the best match for each descriptor

parmeters
-queryDescriptors:	Query set of descriptors.
-trainDescriptors:	Train set of descriptors. 
-matches:	Matches. If a query descriptor is masked out in mask , no match is added for this descriptor. So, matches size may be smaller than the query descriptors count.
-mask: 	Mask specifying permissible matches between an input query and train matrices of descriptors.


4. Mat cv::findHomography (InputArray 	srcPoints, InputArray dstPoints,
int method = 0, double ransacReprojThreshold = 3, OutputArray mask = noArray(),
const int maxIters = 2000, const double confidence = 0.995 )
: finds a perspective transformation between two planes.

parameters
-srcPoints:	Coordinates of the points in the original plane, a matrix of the type CV_32FC2 or vector<Point2f> .
-dstPoints:	Coordinates of the points in the target plane, a matrix of the type CV_32FC2 or a vector<Point2f> .
-method:	Method used to compute a homography matrix. e.x) RANSAC
-ransacReprojThreshold:	Maximum allowed reprojection error to treat a point pair as an inlier (used in the RANSAC and RHO methods only). 
-mask	:Optional output mask set by a robust method ( RANSAC or LMeDS ). Note that the input mask values are ignored.
-maxIters:	The maximum number of RANSAC iterations.
-confidence:	Confidence level, between 0 and 1.


5. drawMatches()
: draw matches of keypoints from two images on 'img_matches'


6. void readme()
: print " Usage: ./SURF_Homography <img1> <img2>"
this function is called when main() parameter argc is not 3