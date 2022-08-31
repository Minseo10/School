#include "hist_func.h"

void linear_stretching(Mat& input, Mat& stretched, G* trans_func, G x1, G x2, G y1, G y2);

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab03\\input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;

	cvtColor(input, input_gray, CV_RGB2GRAY);	//convert RGB to Grayscale

	Mat stretched = input_gray.clone(); //stretched image 저장할 matrix

	// PDF or transfer function txt files
	FILE* f_PDF;
	FILE* f_stretched_PDF;
	FILE* f_trans_func_stretch;

	//open txt files
	fopen_s(&f_PDF, "PDF_for_stretching.txt", "w+");
	fopen_s(&f_stretched_PDF, "stretched_PDF.txt", "w+");
	fopen_s(&f_trans_func_stretch, "trans_func_stretch.txt", "w+");

	G trans_func_stretch[L] = { 0 };

	//generate PDF
	float* PDF = cal_PDF(input_gray);

	// histogram stretching (x1 ~ x2 -> y1 ~ y2)
	linear_stretching(input_gray, stretched, trans_func_stretch, 50, 110, 10, 110);
	float* stretched_PDF = cal_PDF(stretched);	// stretched PDF

	for (int i = 0; i < L; i++) {
		// write PDF
		fprintf(f_PDF, "%d\t%f\n", i, PDF[i]);
		fprintf(f_stretched_PDF, "%d\t%f\n", i, stretched_PDF[i]);

		// write transfer functions
		fprintf(f_trans_func_stretch, "%d\t%d\n", i, trans_func_stretch[i]);
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
	Mat histImage_stretched_PDF(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); //CDF 나타낼 image 초기화

	for (int i = 1;i < L;i++) {
		line(histImage_stretched_PDF, Point(bin_w * (i - 1), hist_h - cvRound(stretched_PDF[i - 1] * 16000)),
			Point(bin_w * i, hist_h - cvRound(stretched_PDF[i] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	} //그래프의 세로축을 0.025로 맞추기 위해 PDF에 400*40을 곱한다

	// memory release
	free(PDF);
	free(stretched_PDF);
	fclose(f_PDF);
	fclose(f_stretched_PDF);
	fclose(f_trans_func_stretch);

	////////////////////// Show each image ///////////////////////

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	namedWindow("Stretched", WINDOW_AUTOSIZE);
	imshow("Stretched", stretched);

	//////////////////////////////////////////////////////////////

	//show histogram
	namedWindow("PDF", WINDOW_AUTOSIZE);
	imshow("PDF", histImage_PDF);

	namedWindow("PDF(Stretching)", WINDOW_AUTOSIZE);
	imshow("PDF(Stretching)", histImage_stretched_PDF);

	waitKey(0);

	return 0;
}

// histogram stretching (linear method)
// parameters
// input: input matrix , stretched: stretched matrix, trans_func: stretching function(y = trans_func[x]), x1~x2: stretching할 범위, y1~y2: stretch한 범위
void linear_stretching(Mat& input, Mat& stretched, G* trans_func, G x1, G x2, G y1, G y2) {

	float constant = (y2 - y1) / (float)(x2 - x1);

	// compute transfer function
	for (int i = 0; i < L; i++) {
		if (i >= 0 && i <= x1)
			trans_func[i] = (G)(y1 / x1 * i);
		else if (i > x1 && i <= x2)
			trans_func[i] = (G)(constant * (i - x1) + y1);
		else
			trans_func[i] = (G)((L - 1 - x2) / (L - 1 - y2) * (i - x2) + y2);
	}

	// perform the transfer function
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			stretched.at<G>(i, j) = trans_func[input.at<G>(i, j)];
}