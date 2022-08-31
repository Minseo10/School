**rotation.cpp**
Visual Studio2019

Purpose of the code: perform image rotation using inverse warping and interpolation(both nearest neighbor and bilinear interpolation)

1. template <typename T> Mat myrotate(const Mat input, float angle, const char* opt)
-input: input matrix to be rotated
-angle: rotation angle
-opt: interpolation method (if nearest-neighbor method then "nearest", else if bilinear method then "bilinear") 
-> use inverse warping and return rotated output matrix

2. float R(float u)
:function for nearest-neighbor interpolation
-> 1 if -0.5<u<=0.5 otherwise 0

3. int main()
-input: read "lena.jpg" using imread() function
-rotated: rotated image matrix


**stitching.cpp**
Visual Studio2019

Purpose of the code: perform image stitching with two images "Img01.jpg" and "Img02.jpg" using affine transformation 

1. template <typename T> Mat cal_affine(int ptl_x[], int ptl_y[], int ptr_x[], int ptr_y[], int number_of_points)
:function to obtain affine transform
-ptl_x[], ptl_y[], ptr_x[], ptr_y[]: corresponding pixels which will be used to calculate affine matrix
-number_of_points: number of points
->return x= (M^T * M)^(−1) * M^T * b , so we can find a,b,c,d,e,f of affine matrix A

2. void blend_stitching(const Mat I1, const Mat I2, Mat& I_f, int bound_l, int bound_u, float alpha)
:function to merge two images I1, I2 
-I1, I2: matrix of image to be blended
-I_f: merged image
-bound_l, bound_u: boundary for merged image(I_f)
-alpha: when blending I1 and I2 use alpha*I1 + (1-alpha)*I2

3. int main()
   1) I1.convertTo(I1, CV_32FC3, 1.0 / 255);
       I2.convertTo(I2, CV_32FC3, 1.0 / 255);
      -> convert l1(l2) into : l1*alpha + beta (l2*alpha + beta )
      -> alpha=1.0/255 , beta= 0.0(default parameter)
   2) I1_row, I1_col, I2_row, I2_col: height(row), width(col) of each image
   3) bound_u, bound_b, bound_l, bound_r: compute boundary for merged image
   4) I_f.convertTo(I_f, CV_8UC3, 255.0) 
      -> convert l_f into :l_f*alpha + beta 
      -> alpha=255.0 , beta= 0.0(default parameter)