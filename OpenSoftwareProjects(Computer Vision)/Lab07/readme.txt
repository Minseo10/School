*LoG_gray.cpp*
1. get_Gaussian_Kernel(int n, double sigma_t, double sigma_s, bool normalize)
: returns gaussian filtering kernel

parameters
-n: kernel size is (2n+1)*(2n+1)
-sigma_t / sigma_s: standard deviation of x and y coordinate
-normalize: normalize 여부(true or false)

variables
-kernel: filtering kernel(return value)
-kernel_sum: sum of kernel elements(for normalization)


2. get_Laplacian_Kernel()
: returns laplacian filtering kernel 

vairables
-kernel: 3x3 laplacian filtering kernel


3. Gaussianfilter(const Mat input, int n, double sigma_t, double sigma_s)
: gaussian filtering function

parameters
-input: intensity matrix of input image
-n: kernel size is (2n+1)*(2n+1)
-sigma_t / sigma_s: standard deviation of x and y coordinate

variables
-kernel: gaussian kernel
-input_mirror: intermediate matrix for mirroring method
-output: gaussian smoothed image
-sum1: intensity value of (i, j) after filtering


4. Laplacianfilter(const Mat input)
: laplacian filter function

parameters
-input: intensity matrix of input image(in this code, 'input' will be gaussian smoothed image)

variables
-kernel: laplacian filter kernel
-input_mirror: intermediate matrix for mirroring method
-n: n is 1->laplacian kernel size is 3x3
-sum1: intensity value of (i, j) after filtering
-output: filtered image (return value)


5. Mirroring(const Mat input, int n)
: processing boundary of 'input' with mirroring method

parameters
-input: intensity matrix of input image

variables
-input2: fixed image with mirroring method
-row2, col2: # of rows and columns of input2 matrix


6. int main()
variables
-input_gray: grayscale image
-window_radius, sigma_t, sigma_s : gaussian smoothing parameters
-h_f: gaussian smoothed image
-Laplacian: image after laplacian filtering to 'h_f'



*LoG_RGB.cpp*
1. get_Gaussian_Kernel(int n, double sigma_t, double sigma_s, bool normalize)
: returns gaussian filtering kernel

parameters
-n: kernel size is (2n+1)*(2n+1)
-sigma_t / sigma_s: standard deviation of x and y coordinate
-normalize: normalize 여부(true or false)

variables
-kernel: filtering kernel(return value)
-kernel_sum: sum of kernel elements(for normalization)


2. get_Laplacian_Kernel()
: returns laplacian filtering kernel 

vairables
-kernel: 3x3 laplacian filtering kernel


3. Gaussianfilter(const Mat input, int n, double sigma_t, double sigma_s)
: gaussian filtering function

parameters
-input: intensity matrix of input image
-n: kernel size is (2n+1)*(2n+1)
-sigma_t / sigma_s: standard deviation of x and y coordinate

variables
-kernel: gaussian kernel
-input_mirror: intermediate matrix for mirroring method
-output: gaussian smoothed image
-sum1_r: intensity value of (i, j) in channel R after filtering
-sum1_g: intensity value of (i, j) in channel G after filtering
-sum1_b: intensity value of (i, j)i n channel B after filtering


4. Laplacianfilter(const Mat input)
: laplacian filter function

parameters
-input: intensity matrix of input image(in this code, 'input' will be gaussian smoothed image)

variables
-kernel: laplacian filter kernel
-input_mirror: intermediate matrix for mirroring method
-n: n is 1->laplacian kernel size is 3x3
-sum1_r: intensity value of (i, j) in channel R after filtering
-sum1_g: intensity value of (i, j) in channel G after filtering
-sum1_b: intensity value of (i, j)i n channel B after filtering
-output: output image matrix (maximum of sum1_r, sum1_g, sum1_b)

5. Mirroring(const Mat input, int n)
: processing boundary of 'input' with mirroring method

parameters
-input: intensity matrix of input image

variables
-input2: fixed image with mirroring method
-row2, col2: # of rows and columns of input2 matrix


6. int main()
variables
-window_radius, sigma_t, sigma_s : gaussian smoothing parameters
-h_f: gaussian smoothed image
-Laplacian: image after laplacian filtering to 'h_f'



*Canny.cpp*
1. void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize = 3, bool L2gradient = false )	
: this function finds edges in an image using the Canny edge detector

parameters
-image:         8-bit input image.
-edges:	  output edge map; single channels 8-bit image, which has the same size as image .
-threshold1:	  first threshold for the hysteresis procedure.
-threshold2:	  second threshold for the hysteresis procedure.
-apertureSize	:  aperture size for the Sobel operator.
-L2gradient:	  a flag, indicating whether L2 norm ={(dI/dx)^2+(dI/dy)^2}^0.5 should be used to calculate the image gradient magnitude ( L2gradient=true ), or whether L1 norm =|dI/dx|+|dI/dy| is enough ( L2gradient=false ).

2. int main()
variables
-input: intensity matrix of input image
-input_gray: grayscale version of input image
-output: edge detected image with canny edge detector



*Harris_corner.cpp*
1. vector<Point2f> MatToVec(const Mat input)
: change matrix into Point2f type vector
parameters
-input: input matrix

variables
-points: change 'input' into vector and save it here


2. Mat NonMaximum_Suppression(const Mat input, Mat corner_mat, int radius)
: non-maximum suppression function
parameters
-input: input image
-corner_mat: matrix that saves 1 for corner and 0 otherwise
-radius: window size for non-maximum suppression

variables
-input_mirror: boundary processed image with mirroring method
-max: maximum value of intensity in each (2*radius+1)*(2*radius+1) window


3. Mat Mirroring(const Mat input, int n)
: mirroring method for boundary processing
parameters
-input: input image
-n: window radius

variables
-input2: fixed image(return value)
-row2, col2: # of rows and cols of input2


4. void type2str(int type)
: If you want to know the type of 'Mat', use the following function
parameter
-type: type of matrix we will find out


5. int main()
variables
-input_gray: grayscale image
-input_visual: input image with corners marked-> we will show this as results
-output: harris corner detected image
-output_norm: normalize 'output' image from 0 to 1
-corner_mat: matrix that saves 1 when the pixel is corner, otherwise save 0
-NonMaxSupp, Subpixel: option for the non-maximum suppression / subpixel refinement in corner detection
- minVal, maxVal: values of global minimum and maximum
- minLoc, maxLoc: location of global minimum and maximum
- corner_num: # of corners
-points: vector which is converted from 'corner_mat'


6. void cv::cornerHarris(InputArray src, OutputArray dst, int 	blockSize, int ksize, double k, int borderType = BORDER_DEFAULT)	
: harris corner detection function

parameters
-src: input single-channel, 8-bit or floating-point
-dst: image with harris detector responses. It has the type CV_32FC1 and the same size as src .
-blockSize: neighborhood size 
-ksize:	aperture parameter for the Sobel filter
-k: harris detector free parameter. 
-borderType:	pixel extrapolation method. 


7. void cv::cornerSubPix(InputArray image, InputOutputArray corners, Size winSize, Size zeroZone, TermCriteria criteria)
: This function refines the corner locations. It iterates to find the sub-pixel accurate location of corners or radial saddle points	

parameters
-image: input single-channel, 8-bit or float image
-corners: initial coordinates of the input corners and refined coordinates provided for output.
-winSize: half of the side length of the search window. e.g) if winSize=Size(5,5) , then a (5∗2+1)×(5∗2+1)=11×11 search window is used.
-zeroZone: half of the size of the dead region in the middle of the search zone over which the summation in the formula below is not done. The value of (-1,-1) indicates that there is no such a size.
-criteria: criteria for termination of the iterative process of corner refinement. That is, the process of corner position refinement stops either after criteria.maxCount iterations or when the corner position moves by less than criteria.epsilon on some iteration.