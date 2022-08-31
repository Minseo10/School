*adaptive_threshold.cpp*

1. Mat adaptive_thres(const Mat input, int n, float bnumber)
: adaptive thresholding function with uniform mean filter

parameters
-input: intensity matrix of input image
-n: filter kernel size if (2n+1)(2n+1)
-bnumber: weight

variables
-kernel: uniform mean filter kernel
-kernelvalue: element value of 'kerenel'. (All elements of the kernel value are same)
-sum1: mean intensity
-temp: thresold for each pixel
-output: output matrix

2. int main()

variables
-input: intensity matrix of input image
-input_gray: intensity matrix of grayscale image
-output: image after adaptive thresholding



*kmeans.cpp*

1. kmeans(InputArray data, int K, InputOutputArray bestLabels, TermCriteria criteria,
    int 	attempts, int flags, OutputArray centers = noArray() )
: k-means clustering function provided by OpenCv

parameters
-data: 	data for culstering
-K:  number of clusters to split the set by
-bestLabels: Input/output integer array that stores the cluster indices for every sample
-criteria: the maximum number of iterations and/or the desired accuracy. 
          The accuracy is specified as criteria.epsilon. As soon as each of the cluster centers moves by less than criteria.epsilon on some iteration, the algorithm stops.
-attempts: Flag to specify the number of times the algorithm is executed using different initial labellings
-centers: output matrix intensity of the cluster centers,  one row per each cluster center.

2. int main()

variables
-input: intensity matrix of input image
-samples: save intensity of all 3 channels
-clusterCount: this will be parameter 'K' in kmeans()
-labels: this will be parameter 'bestLables' in kmeans()
-new_image: image after clustering



*mean_shift_convert2gray.cpp*

1. int main()
-input: intensity matrix of input image
-input_gray: intensity matrix of grayscale image