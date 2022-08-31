*salt_pepper_noise.cpp*
1. Mat Add_salt_pepper_Noise(const Mat input, float ps, float pp)
: generating an image with the salt-and-pepper noise

parameters
-input: intensity matrix of the input image 
-ps: density of salt noise(0~1)
-pp: density of pepper noise(0~1)

variables
-output: noised image
-amount1: # of pepper pixels
-amount2: # of salt pixels

2. Mat Salt_pepper_noise_removal_Gray(const Mat input, int n, const char* opt)
: removing salt and pepper noise in grayscale image

parameters
-input: intensity matrix of the noised image
-n: filter kernel size is (2n+1)(2n+1)
-opt: boundary processing method

variables
-median: index of median value
-idx: index at the filter kernel

3. Mat Salt_pepper_noise_removal_RGB(const Mat input, int n, const char* opt)
: removing salt and pepper noise in color image

parameters
-input: intensity matrix of the noised image
-n: filter kernel size is (2n+1)(2n+1)
-opt: boundary processing method

variables
-median: index of median value
-idx: index at the filter kernel
-channel: # of channels in input image

4. int main()
-input: intensity matrix of input image
-input_gray: intensity matrix of converted grayscale image
-output: intensity matrix of output image
-noise_Gray: noised gray image
-noise_RGB: noised color image
-Denoised_Gray: denoised gray image
-Denoised_RGB: denoised color image



*gaussian_nosie_gaussian.cpp*
1. Mat Add_Gaussian_noise(const Mat input, double mean, double sigma)
: add gaussian noise to input
 
parameters
-input: intensity matrix of input image 
-mean: mean of the gaussian function 
-sigma: standard deviation

variables
-NoiseArr: noise array with random numbers


2. Mat Gaussianfilter_Gray(const Mat input, int n, double sigma_t, double sigma_s, const char* opt)
: removing gaussian noise with simple average filtering (gaussian filter) in grayscale image

parameters
-input: intensity matrix of noised image 
-n: filter kernel size is (2n+1)(2n+1) 
-sigma_t/sigma_s: standard deviation for x/y coordinate
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)

variables
-kernel: it is a kernel matrix of size (kernel_size * kernel_size)x(1). 
          Intensity values of image is saved in 'kernel' to find the median value.
-kernelvalue: element of filter kernel that we will multiply to I(i+a, j+b) -> kernel.at<float>(a + n, b + n)
-tempa, tempb: for the mirroring method
-output: return value
-denom: It is sum of all elements in (2n+1)*(2n+1) kernel matrix.
            We divide kernel elements with denominator to normalize the filter kernel.


3. Mat Gaussianfilter_RGB(const Mat input, int n, double sigma_t, double sigma_s, const char* opt)
: removing gaussian noise with simple average filtering (gaussian filter) in color image

parameters
-input: intensity matrix of noised image 
-n: filter kernel size is (2n+1)(2n+1) 
-sigma_t/sigma_s: standard deviation for x/y coordinate
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)

variables
-kernel: gaussian kernel matrix
-kernelvalue: element of filter kernel that we will multiply to I(i+a, j+b) -> kernel.at<float>(a + n, b + n)
-tempa, tempb: for the mirroring method
-output: return value
-denom: It is sum of all elements in (2n+1)*(2n+1) kernel matrix.
            We divide kernel elements with denominator to normalize the filter kernel.


4. int main()
-input: intensity matrix of input image
-input_gray: intensity matrix of converted grayscale image
-output: intensity matrix of output image
-noise_Gray: noised gray image
-noise_RGB: noised color image
-Denoised_Gray: denoised gray image
-Denoised_RGB: denoised color image



*gaussian_noise_bilateral.cpp*
1. Mat Add_Gaussian_noise(const Mat input, double mean, double sigma)
: add gaussian noise to input
 
parameters
-input: intensity matrix of input image 
-mean: mean of the gaussian function 
-sigma: standard deviation

variables
-NoiseArr: noise array with random numbers


2. Mat Bilateralfilter_Gray(const Mat input, int n, double sigma_t, double sigma_s, double sigma_r, const char* opt)
: removing gaussian noise with bilateral filtering in grayscale image

parameters
-input: intensity matrix of noised image 
-n: filter kernel size is (2n+1)(2n+1) 
-sigma_t/sigma_s: standard deviation for x/y coordinate
-sigma_r: standard deviation for intensity
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)

variables
-denom: W(i , j). total sum of gaussian function values
-kernel: gaussian kernel matrix
-kernelvalue: element of filter kernel that we will multiply to I(i+a, j+b) -> kernel.at<float>(a + n, b + n)
-tempa, tempb: for the mirroring method
-output: return value


3. Mat Bilateralfilter_RGB(const Mat input, int n, double sigma_t, double sigma_s, double sigma_r, const char* opt)
: removing gaussian noise with bilateral filtering(color image)

parameters
-input: intensity matrix of noised image 
-n: filter kernel size is (2n+1)(2n+1) 
-sigma_t/sigma_s: standard deviation for x/y coordinate
-sigma_r: standard deviation for intensity
-opt: type of boundary processing(mirroring / zero-padding / adjusting filter kernel)

variables
-denom: W(i , j). total sum of gaussian function values
-kernel: gaussian kernel matrix
-kernelvalue: element of filter kernel that we will multiply to I(i+a, j+b) -> kernel.at<float>(a + n, b + n)
-tempa, tempb: for the mirroring method
-output: return value


4. int main()
-input: intensity matrix of input image
-input_gray: intensity matrix of converted grayscale image
-output: intensity matrix of output image
-noise_Gray: noised gray image
-noise_RGB: noised color image
-Denoised_Gray: denoised gray image
-Denoised_RGB: denoised color image 