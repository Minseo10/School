#include "hist_func.h"

void hist_eq_Color(Mat& input, Mat& equalized, G(*trans_func)[3], float** CDF);

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab03\\input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat equalized_RGB = input.clone();

	// PDF or transfer function txt files
	FILE* f_equalized_PDF_RGB, * f_PDF_RGB;
	FILE* f_trans_func_eq_RGB;

	fopen_s(&f_PDF_RGB, "PDF_RGB.txt", "w+"); //histograms of the original image
	fopen_s(&f_equalized_PDF_RGB, "equalized_PDF_RGB.txt", "w+"); //histograms of the output image
	fopen_s(&f_trans_func_eq_RGB, "trans_func_eq_RGB.txt", "w+"); //transfer functions for RGB

	float** PDF_RGB = cal_PDF_RGB(input);	// PDF of Input image(RGB) : [L][3]
	float** CDF_RGB = cal_CDF_RGB(input);	// CDF of Input image(RGB) : [L][3]

	G trans_func_eq_RGB[L][3] = { 0 };		// transfer function

	// histogram equalization on RGB image
	hist_eq_Color(input, equalized_RGB, trans_func_eq_RGB, CDF_RGB);

	// equalized PDF (RGB)
	float** equalized_PDF_RGB = cal_PDF_RGB(equalized_RGB);

	for (int i = 0; i < 3; i++) {
		for (int j = 0;j < L;j++) {
			// write PDF
			fprintf(f_PDF_RGB, "%d\t%f\n", j, PDF_RGB[j][i]);
			fprintf(f_equalized_PDF_RGB, "%d\t%f\n", j, equalized_PDF_RGB[j][i]);

			// write transfer functions
			fprintf(f_trans_func_eq_RGB, "%d\t%d\n", j, trans_func_eq_RGB[j][i]);
		}
	}


	//plot histogram(PDF)
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / L);

	Mat histImage_PDF_B(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); //Blue PDF histogram

	for (int i = 1;i < L;i++) { //line 함수를 이용해 이웃한 두 점을 연결하여 histogram을 그린다
		line(histImage_PDF_B, Point(bin_w * (i - 1), hist_h - cvRound(PDF_RGB[i - 1][0] * 16000)),
			Point(bin_w * i, hist_h - cvRound(PDF_RGB[i][0] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	} //그래프의 세로축을 0.025로 맞추기 위해 PDF에 400*40을 곱한다

	Mat histImage_PDF_G(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); //Green PDF histogram

	for (int i = 1;i < L;i++) {
		line(histImage_PDF_G, Point(bin_w * (i - 1), hist_h - cvRound(PDF_RGB[i - 1][1] * 16000)),
			Point(bin_w * i, hist_h - cvRound(PDF_RGB[i][1] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	}

	Mat histImage_PDF_R(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); //Red PDF histogram

	for (int i = 1;i < L;i++) {
		line(histImage_PDF_R, Point(bin_w * (i - 1), hist_h - cvRound(PDF_RGB[i - 1][2] * 16000)),
			Point(bin_w * i, hist_h - cvRound(PDF_RGB[i][2] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	}

	//plot histogram(equalized_PDF_RGB)
	Mat histImage_equalized_PDF_RGB_B(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); //Blue PDF histogram

	for (int i = 1;i < L;i++) {
		line(histImage_equalized_PDF_RGB_B, Point(bin_w * (i - 1), hist_h - cvRound(equalized_PDF_RGB[i - 1][0] * 16000)),
			Point(bin_w * i, hist_h - cvRound(equalized_PDF_RGB[i][0] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	}

	Mat histImage_equalized_PDF_RGB_G(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));//Green PDF histogram

	for (int i = 1;i < L;i++) {
		line(histImage_equalized_PDF_RGB_G, Point(bin_w * (i - 1), hist_h - cvRound(equalized_PDF_RGB[i - 1][1] * 16000)),
			Point(bin_w * i, hist_h - cvRound(equalized_PDF_RGB[i][1] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	}

	Mat histImage_equalized_PDF_RGB_R(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));//Red PDF histogram

	for (int i = 1;i < L;i++) {
		line(histImage_equalized_PDF_RGB_R, Point(bin_w * (i - 1), hist_h - cvRound(equalized_PDF_RGB[i - 1][2] * 16000)),
			Point(bin_w * i, hist_h - cvRound(equalized_PDF_RGB[i][2] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	}



	// memory release
	free(PDF_RGB);
	free(CDF_RGB);
	fclose(f_PDF_RGB);
	fclose(f_equalized_PDF_RGB);
	fclose(f_trans_func_eq_RGB);

	////////////////////// Show each image ///////////////////////

	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("Equalized_RGB", WINDOW_AUTOSIZE);
	imshow("Equalized_RGB", equalized_RGB);

	//////////////////////////////////////////////////////////////

	//show histogram
	namedWindow("PDF_R", WINDOW_AUTOSIZE);
	imshow("PDF_R", histImage_PDF_R);
	namedWindow("PDF_G", WINDOW_AUTOSIZE);
	imshow("PDF_G", histImage_PDF_G);
	namedWindow("PDF_B", WINDOW_AUTOSIZE);
	imshow("PDF_B", histImage_PDF_B);

	namedWindow("PDF_R(hist_eq_RGB)", WINDOW_AUTOSIZE);
	imshow("PDF_R(hist_eq_RGB)", histImage_equalized_PDF_RGB_R);
	namedWindow("PDF_G(hist_eq_RGB)", WINDOW_AUTOSIZE);
	imshow("PDF_G(hist_eq_RGB)", histImage_equalized_PDF_RGB_G);
	namedWindow("PDF_B(hist_eq_RGB)", WINDOW_AUTOSIZE);
	imshow("PDF_B(hist_eq_RGB)", histImage_equalized_PDF_RGB_B);

	waitKey(0);

	return 0;
}

// histogram equalization on 3 channel image
//parameters
//input: input matrix , equalized: matrix of equalized image , trans_func: s=trans_func(r)=(L-1)CDF(r) for each RGB , CDF:Cumulative Distribution Function
void hist_eq_Color(Mat& input, Mat& equalized, G(*trans_func)[3], float** CDF) {

	// compute transfer function=
	//0:B, 1:G, 2:R
	for (int i = 0; i < L; i++) {
		for (int j = 0;j < 3;j++) {
			trans_func[i][j] = (G)((L - 1) * CDF[i][j]);
		}
	}

	// perform the transfer function
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			for (int k = 0;k < 3;k++) {
				equalized.at<C>(i, j)[k] = trans_func[input.at<C>(i, j)[k]][k];
			}
		}
	}
}