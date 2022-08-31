#include "hist_func.h"

void hist_eq(Mat& input, G* trans_func, float* CDF);
void inverse_function(G* trans_func, G* trans_func_inv);
void hist_matching(Mat& input, Mat& ref, Mat& matched, G* trans_func_ma, G* trans_func1, G* trans_func2, G* trans_func2_inv, float* CDF, float* ref_CDF);
G trans_func2_inv[512 * 512] = { 0 };

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab03\\input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat ref_image = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab03\\lena.jpg", CV_LOAD_IMAGE_COLOR);//reference image
	Mat input_gray; Mat ref_image_gray;

	cvtColor(input, input_gray, CV_RGB2GRAY);	// convert RGB to Grayscale
	cvtColor(ref_image, ref_image_gray, CV_RGB2GRAY);	// convert RGB to Grayscale

	Mat matched = input_gray.clone(); //matched image 저장할 matrix

	// PDF or transfer function txt files
	FILE* f_PDF;
	FILE* f_matched_PDF_gray;
	FILE* f_trans_func_ma; //transfer function r to z
	
	//open txt files
	fopen_s(&f_PDF, "PDF.txt", "w+");
	fopen_s(&f_matched_PDF_gray, "equalized_PDF_gray.txt", "w+");
	fopen_s(&f_trans_func_ma, "trans_func_ma.txt", "w+");

	float* PDF = cal_PDF(input_gray);	// PDF of Input image(Grayscale) : [L]
	float* CDF = cal_CDF(input_gray);	// CDF of Input image(Grayscale) : [L]
	float* ref_PDF = cal_PDF(ref_image_gray); //PDF of reference image(Grayscale)
	float* ref_CDF = cal_CDF(ref_image_gray); //CDF of reference image(Grayscale)

	// transfer functions
	G trans_func_ma[L] = { 0 };			
	G trans_func1[L] = { 0 };
	G trans_func2[L] = { 0 };

	//histogram matching on a grayscale image
	hist_matching(input_gray, ref_image_gray, matched, trans_func_ma, trans_func1, trans_func2, trans_func2_inv, CDF, ref_CDF);

	float* matched_PDF_gray = cal_PDF(matched); //matched PDF(grayscale)
	
	
	for (int i = 0; i < L; i++) {
		// write PDF
		fprintf(f_PDF, "%d\t%f\n", i, PDF[i]);
		fprintf(f_matched_PDF_gray, "%d\t%f\n", i, matched_PDF_gray[i]);

		// write transfer functions
		fprintf(f_trans_func_ma, "%d\t%d\n", i, trans_func_ma[i]);
	}

	//plot histogram(PDF)
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / L);

	Mat histImage_PDF(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); //PDF 나타낼 image 초기화

	for (int i = 1;i < L;i++) { //line 함수를 이용해 이웃한 두 점을 연결하여 histogram을 그린다
		line(histImage_PDF, Point(bin_w * (i - 1), hist_h - cvRound(PDF[i - 1] * 16000)),
			Point(bin_w * i, hist_h - cvRound(PDF[i] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	} //그래프의 세로축을 0.025로 맞추기 위해 PDF에 400*40을 곱한다

	//plot histogram(matched_PDF)
	Mat histImage_matched_PDF(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); //CDF 나타낼 image 초기화

	for (int i = 1;i < L;i++) {
		line(histImage_matched_PDF, Point(bin_w * (i - 1), hist_h - cvRound(matched_PDF_gray[i - 1] * 16000)),
			Point(bin_w * i, hist_h - cvRound(matched_PDF_gray[i] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	} 


	// memory release
	free(PDF);
	free(CDF);
	fclose(f_PDF);
	fclose(f_matched_PDF_gray);
	fclose(f_trans_func_ma);

	////////////////////// Show each image ///////////////////////

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	namedWindow("Matched", WINDOW_AUTOSIZE);
	imshow("Matched", matched);

	//////////////////////////////////////////////////////////////

	//show histogram
	namedWindow("PDF", WINDOW_AUTOSIZE);
	imshow("PDF", histImage_PDF);

	namedWindow("PDF(hist_eq)", WINDOW_AUTOSIZE);
	imshow("PDF(hist_eq)", histImage_matched_PDF);

	waitKey(0);

	return 0;
}

// histogram equalization(에서 transfer function 계산만 한다)
//parameters
//input: input matrix , trans_func: s=trans_func(r)=(L-1)CDF(r) , CDF:Cumulative Distribution Function
void hist_eq(Mat& input, G* trans_func, float* CDF) {

	// compute transfer function
	for (int i = 0; i < L; i++)
		trans_func[i] = (G)((L - 1) * CDF[i]);

}

//trans_func의 inverse function을 구해서 trans_func_inv에 저장하는 함수
//parameters
//trans_func: input function , trans_func_inv: inverse function
void inverse_function(G* trans_func, G* trans_func_inv) {
	for (int i = 0; i < L; i++)
		trans_func_inv[trans_func[i]] = i;

	for (int i = 0; i < L; i++) { //역함수 값이 빈 경우 가장 근처 값으로 채워준다
		if (trans_func2_inv[i] == 0) {
			int j = i;
			while (trans_func2_inv[j] == 0 && j>=0)
				j--;
			trans_func2_inv[i] = trans_func2_inv[j];
		}
	}
}

//histogram matching 함수
//parameters
//input:input image , ref: reference image, matched: matched image, trans_func_ma: transfer function of histogram matching
//trans_func1: s=T(r) , trans_func2: s=G(z) , trans_func2_inv: inverse of s=G(z), CDF: CDF of input image, ref_CDf: CDF of reference image
void hist_matching(Mat& input,Mat& ref, Mat& matched, G* trans_func_ma, G* trans_func1, G* trans_func2, G* trans_func2_inv, float* CDF, float* ref_CDF) {
	hist_eq(input, trans_func1, CDF); //compute s=T(r)
	hist_eq(ref, trans_func2, ref_CDF); //compute s=G(z)
	inverse_function(trans_func2, trans_func2_inv); ////compute inverse function of s=G(z)

	for (int i = 0;i < L;i++) { //intensity mapping from r to z -> z=G-1(T(r))
		trans_func_ma[i] = trans_func2_inv[trans_func1[i]];
	}

	// perform the transfer function -> matched image를 구한다
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			matched.at<G>(i, j) = trans_func_ma[input.at<G>(i, j)];
}