*MeanFilterGray.cpp*
1. Mat meanfilter(const Mat input, int n, const char* opt)
: uniform mean filter function(grayscale)

parameters
-input: intput matrix
-n: filter kernel size is (2n+1)(2n+1)
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)

variables
-kernelvalue: element value of the kernel filter(it's uniform filter: every element has the same value)
-output: return value
-tempa, tempb: for the mirroring method

2. int main()
-input: intensity matrix of input image
-input_gray: intensity matrix of converted grayscale image
-output: intensity matrix of output image


*MeanFilterRGB.cpp*
1. Mat meanfilter(const Mat input, int n, const char* opt)
: uniform mean filter function(colored)

parameters
-input: intput matrix
-n: filter kernel size is (2n+1)(2n+1)
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)

variables
-kernelvalue: element value of the kernel filter(it's uniform filter: every element has the same value)
-output: return value
-tempa, tempb: for the mirroring method
-sum1_r, sum1_g, sum1_b: intensity after filtering for each channel(R,G,B)


2. int main()
-input: intensity matrix of input image
-output: intensity matrix of output image



*GaussianGray.cpp*
1. Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt)
: gaussian filter function(graycale)

parameters
-input: intensity matrix of input image
-n: filter kernel size is (2n+1)(2n+1)
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)
-sigmaT/sigmaS: standard deviation for x/y coordinate

variables
-kernelvalue: element of filter kernel that we will multiply to I(i+a, j+b) -> kernel.at<float>(a + n, b + n)
-tempa, tempb: for the mirroring method
-output: return value
-denom: It is sum of all elements in (2n+1)*(2n+1) kernel matrix.
            We divide kernel elements with denominator to normalize the filter kernel.

2. int main()
-input: intensity matrix of input image
-input_gray: intensity matrix of converted grayscale image
-output: intensity matrix of output image
-start, end: start and end time of filter function
-result: how much time filter function takes (=end-start)



*GaussianRGB.cpp*
1. Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt)
: gaussian filter function(graycale)

parameters
-input: intensity matrix of input image
-n: filter kernel size is (2n+1)(2n+1)
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)
-sigmaT/sigmaS: standard deviation for x/y coordinate

variables
-kernelvalue: element of filter kernel that we will multiply to I(i+a, j+b) -> kernel.at<float>(a + n, b + n)
-tempa, tempb: for the mirroring method
-output: return value
-denom: It is sum of all elements in (2n+1)*(2n+1) kernel matrix.
            We divide kernel elements with denominator to normalize the filter kernel.
-sum1_r, sum1_g, sum1_b: intensity after filtering for each channel(R,G,B)

2. int main()
-input: intensity matrix of input image
-output: intensity matrix of output image
-start, end: start and end time of filter function
-result: how much time filter function takes (=end-start)



*SobelGray.cpp*
1. Mat sobelfilter(const Mat input)
: sobel filter function using filter kernel matrix Sx and Sy(Given in the lecture)

parameter
-input: intensity matrix of input image

variables
-kernel_Sx, kernel_Sy: filter kernel matrix Sx and Sy(Given in the lecture)
-n: sobel filter kernel size will be (2n+1)*(2n+1)
-tempa, tempb: used in mirroring for the border pixels
-sum1: filtering results of 'kernel_Sx' as filter kernel and 'input' as input 
-sum2: filtering results of 'kernel_Sy' as filter kernel and 'input' as input 
-output: return value <-  M(x,y) = sqrt( Ix^2 + Iy^2)

2. int main()
-input: intensity matrix of input image
-input_gray: intensity matrix of converted grayscale image
-output: intensity matrix of output image



*SobelRGB.cpp*
1. Mat sobelfilter(const Mat input)
: sobel filter function using filter kernel matrix Sx and Sy(Given in the lecture)

parameter
-input: intensity matrix of input image

variables
-kernel_Sx, kernel_Sy: filter kernel matrix Sx and Sy(Given in the lecture)
-n: sobel filter kernel size will be (2n+1)*(2n+1)
-tempa, tempb: used in mirroring for the border pixels
-sum1_r, sum1_g, sum1_b: filtering results of 'kernel_Sx' as filter kernel and 'input' as input 
-sum2_r, sum2_g, sum2_b: filtering results of 'kernel_Sy' as filter kernel and 'input' as input 
-output: return value<-  M(x,y) = sqrt( Ix^2 + Iy^2)

2. int main()
-input: intensity matrix of input image
-output: intensity matrix of output image



*LaplacianGray.cpp*
1. Mat laplacianfilter(const Mat input)
: laplacian filter function using laplacian matrix L(Given in the lecture)

parameter
-input: intensity matrix of input image

variables
-n:  Laplacian Filter Kernel size will be(2n+1)*(2n+1)
-kernel:  laplacian filter Kernel L(Given in the lecture)
-tempa, tempb: used in mirroring for the border pixels
-sum1: sum of 2nd derivatives ( I(x+1,y)+I(x-1,y)+I(x,y+1)+I(x,y-1)-4(x,y) )
-output: return value <- O(x,y) = | L*I |

2. int main()
-input: intensity matrix of input image
-input_gray: intensity matrix of converted grayscale image
-output: intensity matrix of output image


*LaplacianRGB.cpp*
1. Mat laplacianfilter(const Mat input)
: laplacian filter function using laplacian matrix L(Given in the lecture)

parameter
-input: intensity matrix of input image

variables
-n:  Laplacian Filter Kernel size will be(2n+1)*(2n+1)
-kernel:  laplacian filter Kernel L(Given in the lecture)
-tempa, tempb: used in mirroring for the border pixels
-sum1: sum of 2nd derivatives ( I(x+1,y)+I(x-1,y)+I(x,y+1)+I(x,y-1)-4(x,y) )
-output: return value <- O(x,y) = O(x,y) = (O_r(x,y)+O_g(x,y)+O_b(x,y))/3
-sum1_r: sum of 2nd-x-derivative and 2nd-y-derivative of channel R
-sum1_g: sum of 2nd-x-derivative and 2nd-y-derivative of channel G
-sum1_b: sum of 2nd-x-derivative and 2nd-y-derivative of channel B

2. int main()
-input: intensity matrix of input image
-output: intensity matrix of output image


*GaussianSeparableGray.cpp*
1. Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt)
: separable gaussian filter function

parameters
-input: intensity matrix of input image
-n: filter kernel size is (2n+1)(2n+1)
-sigmaT/sigmaS: standard deviation for x/y coordinate
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)

variables
-kernel_s: separated 1D kernel matrix Ws(s)
-kernel_t: separated 1D kernel matrix Wt(t)
-denom_s, denom_t: It is sum of all elements in (2n+1)*(2n+1) kernel matrix kernel_s and kernel_t.
            We divide kernel elements with denominator to normalize the filter kernel.
-temp: It is a temporary matrix. Filtering results of 'kernel_t' and 'input' will be saved in 'temp'.
          Next, comput filtering of 'kernel_s' and 'temp' and it will be saved in 'output'.
-output: return value



*GaussianSeparableRGB.cpp*
1. Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt)
: separable gaussian filter function

parameters
-input: intensity matrix of input image
-n: filter kernel size is (2n+1)(2n+1)
-sigmaT/sigmaS: standard deviation for x/y coordinate
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)

variables
-kernel_s: separated 1D kernel matrix Ws(s)
-kernel_t: separated 1D kernel matrix Wt(t)
-denom_s, denom_t: It is sum of all elements in (2n+1)*(2n+1) kernel matrix kernel_s and kernel_t.
            We divide kernel elements with denominator to normalize the filter kernel.
-temp: It is a temporary matrix. Filtering results of 'kernel_t' and 'input' will be saved in 'temp'.
          Next, comput filtering of 'kernel_s' and 'temp' and it will be saved in 'output'.
-sum_r, sum_g, sum_b: intensity after filtering for each channel(R,G,B)
-sum_kernel: sum of adjusted kernel element values
-output: return value

2. int main()
-input: intensity matrix of input image
-output: intensity matrix of output image
-start, end: start and end time of filter function
-result: how much time filter function takes (=end-start)


*UnsharpMaskingGray.cpp*
1. Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt)
: gaussian filter function(graycale)

parameters
-input: intensity matrix of input image
-n: filter kernel size is (2n+1)(2n+1)
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)
-sigmaT/sigmaS: standard deviation for x/y coordinate

variables
-kernelvalue: element of filter kernel that we will multiply to I(i+a, j+b) -> kernel.at<float>(a + n, b + n)
-tempa, tempb: for the mirroring method
-output: return value
-denom: It is sum of all elements in (2n+1)*(2n+1) kernel matrix.
            We divide kernel elements with denominator to normalize the filter kernel.

2. Mat UnsharpMask(const Mat input, int n, float sigmaT, float sigmaS, const char* opt, float k)
: unsharp masking function

parameters
-input: intensity matrix of input image
-n: filter kernel size is (2n+1)(2n+1)
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)
-sigmaT/sigmaS: standard deviation for x/y coordinate
-k: scaling constant(0<=k<=1) -> as the k increases, input image looks sharper

variables
-L: Low-pass filtered image matrix
-output: output image with unsharp masking

3. int main()
-input: intensity matrix of input image
-input_gray: intensity matrix of converted grayscale image
-output: intensity matrix of output image



*UnsharpMaskingRGB.cpp*
1. Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt)
: gaussian filter function(graycale)

parameters
-input: intensity matrix of input image
-n: filter kernel size is (2n+1)(2n+1)
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)
-sigmaT/sigmaS: standard deviation for x/y coordinate

variables
-kernelvalue: element of filter kernel that we will multiply to I(i+a, j+b) -> kernel.at<float>(a + n, b + n)
-tempa, tempb: for the mirroring method
-output: return value
-denom: It is sum of all elements in (2n+1)*(2n+1) kernel matrix.
            We divide kernel elements with denominator to normalize the filter kernel.
-sum1_r, sum1_g, sum1_b: intensity after filtering for each channel(R,G,B)

2. Mat UnsharpMask(const Mat input, int n, float sigmaT, float sigmaS, const char* opt, float k)
: unsharp masking function

parameters
-input: intensity matrix of input image
-n: filter kernel size is (2n+1)(2n+1)
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)
-sigmaT/sigmaS: standard deviation for x/y coordinate
-k: scaling constant(0<=k<=1) -> as the k increases, input image looks sharper

variables
-L: Low-pass filtered image matrix
-output: output image with unsharp masking

3. int main()
-input: intensity matrix of input image
-output: intensity matrix of output image