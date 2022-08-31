***hist_func.h***
:PDF, CDF 구하는 함수가 있는 헤더 파일

1. float* cal_PDF(Mat& input)
:generate PDF for single channel image
-input: single channel image
-histogram x축: intensity level y축: # of pixels / total # of pixels
-return PDF array

2. float** cal_PDF_RGB(Mat& input)
: generate PDF for color image 
-input: color image
-PDF[L][3]: L is # of intensity levels and 3 is R,G,B(0->B, 1->G, 2->R)
-histogram x축: intensity level y축: # of pixels / total # of pixels
-return PDF array

3. float* cal_CDF(Mat& input)
:generate CDF for single channel image
-input: single channel image
-return CDF array

4. float** cal_CDF_RGB(Mat& input)
: generate PDF for color image 
-input: color image
-CDF[L][3]: L is # of intensity levels and 3 is R,G,B(0->B, 1->G, 2->R)
-return CDF array


***PDF_CDF.cpp***
1. int main()
-float* PDF :	PDF of Input image(Grayscale) : [L]
-float* CDF : CDF of Input image(Grayscale) : [L]
-FILE* f_PDF, * f_CDF :  PDF, CDF txt files
-histImage_PDF, histImage_CDF: histogram of PDF and CDF


***hist_stretching.cpp***
1. void linear_stretching(Mat& input, Mat& stretched, G* trans_func, G x1, G x2, G y1, G y2)
:  histogram stretching (linear method)
-input: input matrix 
-stretched: stretched matrix
-trans_func: stretching function(y = trans_func[x]), 
-x1~x2: range we will stretch 
-y1~y2: range after stretching

2. int main()
-input: input image
-input_gray: convert input into grayscale
-stretched: matrix of stretched image
-histImage_PDF: PDF histogram
-histImage_stretched_PDF: PDF histogram of stretched image

***hist_eq.cpp***
1. void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF)
:  histogram equalization on grayscale image
-input: input matrix 
-equalized: matrix of equalized image
-trans_func: s=trans_func(r)=(L-1)CDF(r) 
-CDF:Cumulative Distribution Function


***hist_eq_RGB.cpp***
1. void hist_eq_Color(Mat& input, Mat& equalized, G(*trans_func)[3], float** CDF)
: histogram equalization on 3 channel image
-input: input matrix 
-equalized: matrix of equalized image 
-trans_func: s=trans_func(r)=(L-1)CDF(r) for each RGB 
-CDF:Cumulative Distribution Function



***hist_eq_YUV.cpp*** 
1. void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF)
:  histogram equalization 
-input: input matrix 
-equalized: matrix of equalized image
-trans_func: s=trans_func(r)=(L-1)CDF(r) 
-CDF:Cumulative Distribution Function

2. split(equalized_YUV, channels)
:split each channel(Y, U, V)
Y = channels[0], U = channels[1], V = channels[2]

3. merge(channels, 3, equalized_YUV)
: merge Y, U, V channels



***hist_matching_gray***
1. void hist_eq(Mat& input, G* trans_func, float* CDF)
: histogram equalization(but only computing transfer function)
-input: input matrix 
-trans_func: s=trans_func(r)=(L-1)CDF(r) 
-CDF:Cumulative Distribution Function

2. void inverse_function(G* trans_func, G* trans_func_inv
: compute inverse function of trans_func and save it in trans_func_inv
-trans_func: input function 
-trans_func_inv: inverse function

3. void hist_matching(Mat& input,Mat& ref, Mat& matched, G* trans_func_ma, G* trans_func1, G* trans_func2, G* trans_func2_inv, float* CDF, float* ref_CDF)
: histogram matching function
-input:input image 
-ref: reference image
-matched: matched image
-trans_func_ma: transfer function of histogram matching
-trans_func1: s=T(r)-trans_func2: s=G(z) 
-trans_func2_inv: inverse of s=G(z)
-CDF: CDF of input image
-ref_CDf: CDF of reference image


***hist_matching_YUV***
1. void hist_eq(Mat& input, G* trans_func, float* CDF)
: histogram equalization(but only computing transfer function)
-input: input matrix 
-trans_func: s=trans_func(r)=(L-1)CDF(r) 
-CDF:Cumulative Distribution Function

2. void inverse_function(G* trans_func, G* trans_func_inv
: compute inverse function of trans_func and save it in trans_func_inv
-trans_func: input function 
-trans_func_inv: inverse function

3. void hist_matching(Mat& input,Mat& ref, Mat& matched, G* trans_func_ma, G* trans_func1, G* trans_func2, G* trans_func2_inv, float* CDF, float* ref_CDF)
: histogram matching function
-input:input image 
-ref: reference image
-matched: matched image
-trans_func_ma: transfer function of histogram matching
-trans_func1: s=T(r)-trans_func2: s=G(z) 
-trans_func2_inv: inverse of s=G(z)
-CDF: CDF of input image
-ref_CDf: CDF of reference image


