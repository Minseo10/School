#include "hist_func.h"

int main() {

	Mat input = imread("C:\\Users\\MIN\\Desktop\\�ǹμ�\\�б�\\2022-1\\������\\Lab03\\input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;

	cvtColor(input, input_gray, CV_RGB2GRAY);	// RGB�� Grayscale�� ��ȯ �� input_gray�� ����

	// PDF, CDF txt files
	FILE* f_PDF, * f_CDF;

	//open file: ���� ����, ���ϸ�, ���� ���(w�� write mode)
	fopen_s(&f_PDF, "PDF.txt", "w+");
	fopen_s(&f_CDF, "CDF.txt", "w+");

	// each histogram
	float* PDF = cal_PDF(input_gray);		// PDF of Input image(Grayscale) : [L]
	float* CDF = cal_CDF(input_gray);		// CDF of Input image(Grayscale) : [L]

	for (int i = 0; i < L; i++) {
		// write PDF, CDF
		fprintf(f_PDF, "%d\t%f\n", i, PDF[i]);
		fprintf(f_CDF, "%d\t%f\n", i, CDF[i]);
	}

	//plot histogram(PDF)
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / L);

	Mat histImage_PDF(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); //PDF ��Ÿ�� image �ʱ�ȭ

	for (int i = 1;i < L;i++) { //line �Լ��� �̿��� �̿��� �� ���� �����Ͽ� histogram�� �׸���
		line(histImage_PDF, Point(bin_w * (i - 1), hist_h - cvRound(PDF[i - 1] * 16000)),
			Point(bin_w * i, hist_h - cvRound(PDF[i] * 16000)), Scalar(255, 0, 0), 2, 8, 0);
	} //�׷����� �������� 0.025�� ���߱� ���� PDF�� 400*40�� ���Ѵ�

	//plot histogram(CDF)
	Mat histImage_CDF(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); //CDF ��Ÿ�� image �ʱ�ȭ

	for (int i = 1;i < L;i++) {
		line(histImage_CDF, Point(bin_w * (i - 1), hist_h - cvRound(CDF[i - 1] * 400)),
			Point(bin_w * i, hist_h - cvRound(CDF[i] * 400)), Scalar(255, 0, 0), 2, 8, 0);
	} //�׷����� �������� 1�� ���߱� ���� CDF�� 400�� ���Ѵ�

	// memory release
	free(PDF);
	free(CDF);
	fclose(f_PDF);
	fclose(f_CDF);


	//show RGB, grayscale 
	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	//show histogram
	namedWindow("PDF", WINDOW_AUTOSIZE);
	imshow("PDF", histImage_PDF);

	namedWindow("CDF", WINDOW_AUTOSIZE);
	imshow("CDF", histImage_CDF);

	waitKey(0);

	return 0;
}