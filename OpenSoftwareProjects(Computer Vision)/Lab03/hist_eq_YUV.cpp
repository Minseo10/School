#include "hist_func.h"

void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF);

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\권민서\\학교\\2022-1\\오소프\\Lab03\\input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat equalized_YUV;

	// RGB -> YUV
	cvtColor(input, equalized_YUV, CV_RGB2YUV);

	// split each channel(Y, U, V)
	Mat channels[3];
	split(equalized_YUV, channels);
	Mat Y = channels[0];						// U = channels[1], V = channels[2]

	// PDF or transfer function txt files
	FILE* f_equalized_PDF_YUV, * f_PDF_RGB;
	FILE* f_trans_func_eq_YUV;

	float** PDF_RGB = cal_PDF_RGB(input);		// PDF of Input image(RGB) : [L][3]
	float* CDF_YUV = cal_CDF(Y);				// CDF of Y channel image

	fopen_s(&f_PDF_RGB, "PDF_RGB.txt", "w+");
	fopen_s(&f_equalized_PDF_YUV, "equalized_PDF_YUV.txt", "w+");
	fopen_s(&f_trans_func_eq_YUV, "trans_func_eq_YUV.txt", "w+");

	G trans_func_eq_YUV[L] = { 0 };			// transfer function

	// histogram equalization on Y channel
	hist_eq(Y, channels[0], trans_func_eq_YUV, CDF_YUV);

	// merge Y, U, V channels
	merge(channels, 3, equalized_YUV);

	// YUV -> RGB (use "CV_YUV2RGB" flag)
	cvtColor(equalized_YUV, equalized_YUV, CV_YUV2RGB);

	// equalized PDF (YUV)
	float** equalized_PDF_YUV = cal_PDF_RGB(equalized_YUV);

	for (int i = 0; i < 3; i++) {
		for (int j = 0;j < L;j++) {
			// write PDF
			fprintf(f_PDF_RGB, "%d\t%f\n", j, PDF_RGB[j][i]);
			fprintf(f_equalized_PDF_YUV, "%d\t%f\n", j, equalized_PDF_YUV[j][i]);

			// write transfer functions
			fprintf(f_trans_func_eq_YUV, "%d\t%d\n", j, trans_func_eq_YUV[j]);
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

	//plot histogram(equalized_PDF_YUV)
	Mat histImage_equalized_PDF_YUV_B(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); //Blue PDF histogram

	for (int i = 1;i < L;i++) {
		line(histImage_equalized_PDF_YUV_B, Point(bin_w * (i - 1), hist_h - cvRound(equalized_PDF_YUV[i - 1][0] * 16000)),
			Point(bin_w * i, hist_h - cvRound(equalized_PDF_YUV[i][0] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	}

	Mat histImage_equalized_PDF_YUV_G(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));//Green PDF histogram

	for (int i = 1;i < L;i++) {
		line(histImage_equalized_PDF_YUV_G, Point(bin_w * (i - 1), hist_h - cvRound(equalized_PDF_YUV[i - 1][1] * 16000)),
			Point(bin_w * i, hist_h - cvRound(equalized_PDF_YUV[i][1] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	}

	Mat histImage_equalized_PDF_YUV_R(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));//Red PDF histogram

	for (int i = 1;i < L;i++) {
		line(histImage_equalized_PDF_YUV_R, Point(bin_w * (i - 1), hist_h - cvRound(equalized_PDF_YUV[i - 1][2] * 16000)),
			Point(bin_w * i, hist_h - cvRound(equalized_PDF_YUV[i][2] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	}



	// memory release
	free(PDF_RGB);
	free(CDF_YUV);
	fclose(f_PDF_RGB);
	fclose(f_equalized_PDF_YUV);
	fclose(f_trans_func_eq_YUV);

	////////////////////// Show each image ///////////////////////

	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("Equalized_YUV", WINDOW_AUTOSIZE);
	imshow("Equalized_YUV", equalized_YUV);

	//////////////////////////////////////////////////////////////

	//show histogram
	namedWindow("PDF_R", WINDOW_AUTOSIZE);
	imshow("PDF_R", histImage_PDF_R);
	namedWindow("PDF_G", WINDOW_AUTOSIZE);
	imshow("PDF_G", histImage_PDF_G);
	namedWindow("PDF_B", WINDOW_AUTOSIZE);
	imshow("PDF_B", histImage_PDF_B);

	namedWindow("PDF_R(hist_eq_YUV)", WINDOW_AUTOSIZE);
	imshow("PDF_R(hist_eq_YUV)", histImage_equalized_PDF_YUV_R);
	namedWindow("PDF_G(hist_eq_YUV)", WINDOW_AUTOSIZE);
	imshow("PDF_G(hist_eq_YUV)", histImage_equalized_PDF_YUV_G);
	namedWindow("PDF_B(hist_eq_YUV)", WINDOW_AUTOSIZE);
	imshow("PDF_B(hist_eq_YUV)", histImage_equalized_PDF_YUV_B);

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