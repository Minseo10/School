#include<iostream>
#include<algorithm>
#define ROWS 6
#define COLS 6
#define MAX_TERMS 10
using namespace std;

typedef struct { 
	int row;
	int col;
	int value;
}element;

typedef struct {
	element data[MAX_TERMS];
	int rows; //number of rows in the sparsematrix
	int cols; //number of columns in the sparse matrix
	int terms; //number of non-zero terms
}SparseMatrix;

bool compare(element a, element b) { //compare function to sort the data array in ascending order
	if (a.row == b.row) return a.col < b.col;
	else return a.row < b.row;
}


int main() {

	//Add B as an input
	SparseMatrix B = {
		{{0,3,7},{1,0,9},{1,5,8},{3,0,6},{3,1,5},{4,5,1},{5,2,2}},
		ROWS, COLS, 7
	};
	SparseMatrix BT = {0,}; //transpose matrix of B

	//transpose operation
	BT.rows = COLS;
	BT.cols = ROWS;
	BT.terms = B.terms;

	for (int i = 0; i < B.terms; i++) { //swap row and col of each data
		BT.data[i].row = B.data[i].col;
		BT.data[i].col = B.data[i].row;
		BT.data[i].value = B.data[i].value;
	}
	sort(BT.data, BT.data + 7, compare); //sort the data array in ascending order


	int matrixB[ROWS][COLS] = { 0, }; //store all elements of matrix B in 2D array form
	int matrixBT[COLS][ROWS] = { 0, }; //store all elements of transpose of B in 2D array form

	for (int i = 0; i < B.terms; i++) {
			matrixB[B.data[i].row][B.data[i].col] = B.data[i].value;
	}
	for (int i = 0; i < BT.terms; i++) {
		matrixBT[BT.data[i].row][BT.data[i].col] = BT.data[i].value;
	}

	//print B and transpose of B in a dense matrix form
	cout << "B\n";
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			cout << matrixB[i][j];
		}
		cout << "\n";
	}
	cout << "transpose of B\n";
	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < ROWS; j++) {
			cout << matrixBT[i][j];
		}
		cout << "\n";
	}

	return 0;
}