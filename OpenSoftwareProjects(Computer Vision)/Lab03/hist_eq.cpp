#include "hist_func.h"

void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF);

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab03\\input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;

	cvtColor(input, input_gray, CV_RGB2GRAY);	// convert RGB to Grayscale

	Mat equalized = input_gray.clone(); //equalized image 저장할 matrix

	// PDF or transfer function txt files
	FILE* f_PDF;
	FILE* f_equalized_PDF_gray;
	FILE* f_trans_func_eq;

	//open txt files
	fopen_s(&f_PDF, "PDF.txt", "w+");
	fopen_s(&f_equalized_PDF_gray, "equalized_PDF_gray.txt", "w+");
	fopen_s(&f_trans_func_eq, "trans_func_eq.txt", "w+");

	float* PDF = cal_PDF(input_gray);	// PDF of Input image(Grayscale) : [L]
	float* CDF = cal_CDF(input_gray);	// CDF of Input image(Grayscale) : [L]

	G trans_func_eq[L] = { 0 };			// transfer function

	hist_eq(input_gray, equalized, trans_func_eq, CDF);	 // histogram equalization on grayscale image
	float* equalized_PDF_gray = cal_PDF(equalized);		 // equalized PDF (grayscale)

	for (int i = 0; i < L; i++) {
		// write PDF
		fprintf(f_PDF, "%d\t%f\n", i, PDF[i]);
		fprintf(f_equalized_PDF_gray, "%d\t%f\n", i, equalized_PDF_gray[i]);

		// write transfer functions
		fprintf(f_trans_func_eq, "%d\t%d\n", i, trans_func_eq[i]);
	}

	//plot histogram(PDF)
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / L);

	Mat histImage_PDF(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); //PDF 나타낼 image 초기화

	for (int i = 1;i < L;i++) { //line 함수를 이용해 이웃한 두 점을 연결하여 histogram을 그린다
		line(histImage_PDF, Point(bin_w * (i - 1), hist_h - cvRound(PDF[i - 1] * 16000)),
			Point(bin_w * i, hist_h - cvRound(PDF[i] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	} //그래프의 세로축을 0.025로 맞추기 위해 PDF에 400*40을 곱한다

	//plot histogram(stretched_PDF)
	Mat histImage_equalized_PDF(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); //CDF 나타낼 image 초기화

	for (int i = 1;i < L;i++) {
		line(histImage_equalized_PDF, Point(bin_w * (i - 1), hist_h - cvRound(equalized_PDF_gray[i - 1] * 16000)),
			Point(bin_w * i, hist_h - cvRound(equalized_PDF_gray[i] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	} //그래프의 세로축을 0.025로 맞추기 위해 PDF에 400*40을 곱한다


	// memory release
	free(PDF);
	free(CDF);
	fclose(f_PDF);
	fclose(f_equalized_PDF_gray);
	fclose(f_trans_func_eq);

	////////////////////// Show each image ///////////////////////

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	namedWindow("Equalized", WINDOW_AUTOSIZE);
	imshow("Equalized", equalized);

	//////////////////////////////////////////////////////////////

	//show histogram
	namedWindow("PDF", WINDOW_AUTOSIZE);
	imshow("PDF", histImage_PDF);

	namedWindow("PDF(hist_eq)", WINDOW_AUTOSIZE);
	imshow("PDF(hist_eq)", histImage_equalized_PDF);

	waitKey(0);

	return 0;
}

// histogram equalization
//parameters
//input: input matrix , equalized: matrix of equalized image , trans_func: s=trans_func(r)=(L-1)CDF(r) , CDF:Cumulative Distribution Function
void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF) {

	// compute transfer function
	for (int i = 0; i < L; i++)
		trans_func[i] = (G)((L - 1) * CDF[i]);

	// perform the transfer function
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			equalized.at<G>(i, j) = trans_func[input.at<G>(i, j)];
}