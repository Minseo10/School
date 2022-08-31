*stitching_case1.cpp*
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

4. template <typename T> Mat cal_affine(int ptl_x[], int ptl_y[], int ptr_x[], int ptr_y[], int number_of_points)
:function to obtain affine transform
-ptl_x[], ptl_y[], ptr_x[], ptr_y[]: corresponding pixels which will be used to calculate affine matrix
-number_of_points: number of points
->return x= (M^T * M)^(−1) * M^T * b , so we can find a,b,c,d,e,f of affine matrix A

5. void blend_stitching(const Mat I1, const Mat I2, Mat& I_f, int bound_l, int bound_u, float alpha)
:function to merge two images I1, I2 
-I1, I2: matrix of image to be blended
-I_f: merged image
-bound_l, bound_u: boundary for merged image(I_f)
-alpha: when blending I1 and I2 use alpha*I1 + (1-alpha)*I2

6. int main()
variables
-keypoints1, descriptors1, keypoints2, descriptors2: : keypoints and descriptors of "image1.jpg" & "image2.jpg"
-srcPoints, dstPoints: nearest neighbor pairs are saved in this vectors
-crossCheck: if cross-checking method is used, then 'true'. Otherwise, 'false'.
-ratio_threshold:  if ratio-based thresholding is used, then 'true'. Otherwise, 'false'.
-I1_row, I1_col, I2_row, I2_col: height(row), width(col) of each image
-p1, p2, p3, p4: corners of I2'
-bound_u, bound_b, bound_l, bound_r: compute boundary for merged image
-l_f: stitched image

7. void cv::FeatureDetector::detect(const cv::Mat &image, std::vector<cv::KeyPoint> &keypoints, const cv::Mat &mask = cv::Mat()) 
: detect keypoints in an image.

parameters
-image:	Image.
-keypoints:	The detected keypoints. In the second variant of the method keypoints[i] is a set of keypoints detected in images[i] .
-mask: 	Mask specifying where to look for keypoints (optional). It must be a 8-bit integer matrix with non-zero values in the region of interest.


8. void cv::DescriptorExtractor::compute(const cv::Mat &image, std::vector<cv::KeyPoint> &keypoints, cv::Mat &descriptors)
: Computes the descriptors for a set of keypoints detected in an image or image set 

parameters
-image:	Image.
-keypoints:	Input collection of keypoints. Keypoints for which a descriptor cannot be computed are removed. 
-descriptors:	Computed descriptors. Row j is the keypoints (or keypoints[i]) is the descriptor for keypoint j-th keypoint.


*stitching_case2.cpp*
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

4. template <typename T> Mat cal_affine(int ptl_x[], int ptl_y[], int ptr_x[], int ptr_y[], int number_of_points)
:function to obtain affine transform
-ptl_x[], ptl_y[], ptr_x[], ptr_y[]: corresponding pixels which will be used to calculate affine matrix
-number_of_points: number of points
->return x= (M^T * M)^(−1) * M^T * b , so we can find a,b,c,d,e,f of affine matrix A

5. vector<int> get_inliers(vector<Point2f> ptl, vector<Point2f> ptr, Mat& affineM, float threshold, int number_of_points);
: return inlier pairs satisfying |Tp-p'|^2 < threshold^2
parameters
-ptl, ptr: data from I1 and I2 
-affineM: affine transformation matrix(x from Mx=b) 
-threshold: inlier threshold 
-number_of_points: # of matching points in I1, I2

variables
-pl: p=(x,y,1)^T
-pr: p'=(x',y')^T 
-temp: T*p
-affineT: affine transformation T
-inlier_idx: vector which contains index of inliers satisfying |Tp-p'|^2 < threshold^2

6. void blend_stitching(const Mat I1, const Mat I2, Mat& I_f, int bound_l, int bound_u, float alpha)
:function to merge two images I1, I2 
-I1, I2: matrix of image to be blended
-I_f: merged image
-bound_l, bound_u: boundary for merged image(I_f)
-alpha: when blending I1 and I2 use alpha*I1 + (1-alpha)*I2

7. int main()
variables
-keypoints1, descriptors1, keypoints2, descriptors2: : keypoints and descriptors of "input1.jpg" & "input2.jpg"
-srcPoints, dstPoints: nearest neighbor pairs are saved in this vectors
-crossCheck: if cross-checking method is used, then 'true'. Otherwise, 'false'.
-ratio_threshold:  if ratio-based thresholding is used, then 'true'. Otherwise, 'false'.
-I1_row, I1_col, I2_row, I2_col: height(row), width(col) of each image

-k: # of randomly sampled points
-S: # of trials
-inliers12, inliers21: vector which contaions indices of inlier points for each trial when computing A12(A21)
-A12, A21: best affine transformation
-max_in: maximum # of inlier pairs
-best_idx: index of best affine transformation
-random_dst, random_src: randomly sampled k points of left(right) image
-T: affine transformation computed by k points
-inlier_pairs_src, inlier_pairs_dst: vector which contains inlier pairs of best affine transformation

-p1, p2, p3, p4: corners of I2'(right image)
-bound_u, bound_b, bound_l, bound_r: compute boundary for merged image
-l_f: stitched image

8. detect(), compute()
: same with *stitching_case1.cpp*


*Hough.cpp*
1. void cv::HoughLines(InputArray image, OutputArray lines,double rho,double theta,
int threshold,double srn = 0,double stn = 0,double min_theta = 0,double max_theta = CV_PI)	
: Finds lines in a binary image using the standard Hough transform

parameters
-image	:  image matrix
-lines:	output vector of lines. Each line is represented by a 2 or 3 element vector (ρ,θ) or (ρ,θ,votes) . 
          ρ = distance from the coordinate origin (0,0) / θ = line rotation angle in radians ( 0∼vertical line,π/2∼horizontal line ) / votes = value of accumulator.
-rho:	distance resolution of the accumulator in pixels
-theta:	angle resolution of the accumulator in radians
-threshold:	accumulator threshold parameter. Only those lines are returned that get enough votes ( >threshold ).
-srn:	divisor for the distance resolution rho(for the multi-scale Hough transform) . 
-stn:    divisor for the distance resolution theta.(for the multi-scale Hough transform)
-min_theta:	 minimum angle to check for lines(for standard and multi-scale Hough transform) -> range: between 0 and max_theta.
-max_theta:	 maximum angle to check for lines(for standard and multi-scale Hough transform) -> range: between min_theta and CV_PI.

2. void cv::HoughLinesP(InputArray image, OutputArray lines,double rho,double theta,
int threshold,double srn = 0,double minLineLength = 0,double maxLineGap = 0)
: Finds line segments in a binary image using the probabilistic Hough transform.

-image	:  image matrix
-lines:	output vector of lines. Each line is represented by a 4-element vector (x1,y1,x2,y2) , (x1,y1) and (x2,y2) are the ending points of each detected line segment.
-rho:	distance resolution of the accumulator in pixels
-theta:	angle resolution of the accumulator in radians
-threshold:	accumulator threshold parameter. Only those lines are returned that get enough votes ( >threshold ).
-minLineLength:	Minimum line length. Line segments shorter than that are rejected.
-maxLineGap:	Maximum allowed gap between points on the same line to link them.

3. int main()
variables
-src: image matrix
-dst: canny edge detected image
-color_dst: convert edge detection result to color image