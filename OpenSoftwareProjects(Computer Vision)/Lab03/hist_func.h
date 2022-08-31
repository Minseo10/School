#pragma once
//PDF, CDF 구하는 함수가 있는 헤더 파일
#pragma once

#include <opencv2/opencv.hpp>
#include <stdio.h>

#define L 256		// # of intensity levels
#define IM_TYPE	CV_8UC3

using namespace cv;

// Image Type
// "G" for GrayScale Image, "C" for Color Image
#if (IM_TYPE == CV_8UC3)
typedef uchar G;
typedef cv::Vec3b C;
#elif (IM_TYPE == CV_16SC3)
typedef short G;
typedef Vec3s C;
#elif (IM_TYPE == CV_32SC3)
typedef int G;
typedef Vec3i C;
#elif (IM_TYPE == CV_32FC3)
typedef float G;
typedef Vec3f C;
#elif (IM_TYPE == CV_64FC3)
typedef double G;
typedef Vec3d C;
#endif

// generate PDF for single channel image
//histogram x축: intensity level y축: # of pixels / total # of pixels
float* cal_PDF(Mat& input) {

	int count[L] = { 0 };
	float* PDF = (float*)calloc(L, sizeof(float)); //동적할당: float 크기의 변수를 L개 저장할 수 있도록 할당

	// Count # of pixels
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			count[input.at<G>(i, j)]++;

	// Compute PDF -> total # of pixels로 나눈다
	for (int i = 0; i < L; i++)
		PDF[i] = (float)count[i] / (float)(input.rows * input.cols);

	return PDF;
}

// generate PDF for color image -> R, G, B에 대해 각각 histogram 1개씩
float** cal_PDF_RGB(Mat& input) {

	int count[L][3] = { 0 };// 0:R, 1:G, 2:B
	float** PDF = (float**)malloc(sizeof(float*) * L);

	for (int i = 0; i < L; i++)
		PDF[i] = (float*)calloc(3, sizeof(float));


	// Count
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			for (int k = 0; k < 3;k++) {
				count[input.at<C>(i, j)[k]][k]++;
			}
		}
	}


	// Compute PDF
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < 3;j++) {
			PDF[i][j] = (float)count[i][j] / (float)(input.rows * input.cols);
		}
	}

	return PDF;
}

// generate CDF for single channel image
float* cal_CDF(Mat& input) {

	int count[L] = { 0 };
	float* CDF = (float*)calloc(L, sizeof(float));

	// Count
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			count[input.at<G>(i, j)]++;

	// Compute CDF
	for (int i = 0; i < L; i++) {
		CDF[i] = (float)count[i] / (float)(input.rows * input.cols);

		if (i != 0)
			CDF[i] += CDF[i - 1];
	}

	return CDF;
}

// generate CDF for color image
float** cal_CDF_RGB(Mat& input) {

	int count[L][3] = { 0 };
	float** CDF = (float**)malloc(sizeof(float*) * L);

	for (int i = 0; i < L; i++)
		CDF[i] = (float*)calloc(3, sizeof(float));

	////////////////////////////////////////////////
	//											  //
	// How to access multi channel matrix element //
	//											  //
	// if matrix A is CV_8UC3 type,				  //
	// A(i, j, k) -> A.at<Vec3b>(i, j)[k]		  //
	//											  //
	////////////////////////////////////////////////

	// Count
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			for (int k = 0; k < 3;k++) {
				count[input.at<C>(i, j)[k]][k]++;
			}
		}
	}

	// Compute CDF
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < 3;j++) {
			CDF[i][j] = (float)count[i][j] / (float)(input.rows * input.cols);

			if (i != 0)
				CDF[i][j] += CDF[i - 1][j];
		}
	}

	return CDF;
}