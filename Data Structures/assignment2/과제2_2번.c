#include<stdio.h>
#include<stdlib.h>

int floor = 3; //first axis of 3D array
int row = 3; //second axis of 3D array
int col = 3; //third axis of 3D array

double*** mem_alloc_3D_double() { //allocate 3D array using dynamic memory allocation
	
	double ***m = (double***)malloc(sizeof(double**) * floor);
	for (int i = 0; i < floor; i++) {
		m[i] = (double**)malloc(sizeof(double*) * row);
	}
	for (int i = 0; i < floor; i++) {
		for (int j = 0; j < row; j++) {
			m[i][j] = (double*)malloc(sizeof(double) * col);
		}
	}

	int count = 0;
	for (int i = 0; i < floor; i++) { 
		for (int j = 0; j < row; j++) {
			for (int k = 0; k < col; k++) {
				m[i][j][k] = ++count;
			}
		}
	}
	return m;

}

void printArray(double*** a) { //print a 3D array
	for (int i = 0; i < floor; i++) { 
		printf("%dth floor\n", i);
		for (int j = 0; j < row; j++) {
			for (int k = 0; k < col; k++) {
				printf("%f ", a[i][j][k]);
			}
			printf("\n");
		}
	}
}

double*** addition_3D(double*** a, double*** b) { //add A and B
	double*** n;
	n = (double***)malloc(sizeof(double**) * floor);
	for (int i = 0; i < floor; i++) {
		n[i] = (double**)malloc(sizeof(double*) * row);
	}
	for (int i = 0; i < floor; i++) {
		for (int j = 0; j < row; j++) {
			n[i][j] = (double*)malloc(sizeof(double) * col);
		}
	}

	for (int i = 0; i < floor; i++) {
		for (int j = 0; j < row; j++) {
			for (int k = 0; k < col; k++) {
				n[i][j][k] = a[i][j][k] + b[i][j][k];
			}
		}
	}
	return n;

}

int main() {
	
	double*** A = { 0, };
	double*** B = {0,};
	double*** C = {0,}; //we will store addition of array A and B in C

	//define two matrices A and B
	A=mem_alloc_3D_double();
	B=mem_alloc_3D_double();

	//perform addition of two matrices A and B
	C=addition_3D(A, B);

	//print A, B, and A+B
	printf("A\n");
	printArray(A);
	printf("\n");
	printf("B\n");
	printArray(B);
	printf("\n");
	printf("A+B\n");
	printArray(C);

	//deallocate A and B and C
	if (A != NULL) {
		
		for (int i = 0; i < floor; i++) {
			for (int j = 0; j < row; j++) {
				free(A[i][j]);
			}
		}
		for (int i = 0; i < floor; i++) {
			free(A[i]);
		}
		free(A);

	}

	if (B != NULL) {

		for (int i = 0; i < floor; i++) {
			for (int j = 0; j < row; j++) {
				free(B[i][j]);
			}
		}
		for (int i = 0; i < floor; i++) {
			free(B[i]);
		}
		free(B);

	}

	if (C != NULL) {

		for (int i = 0; i < floor; i++) {
			for (int j = 0; j < row; j++) {
				free(C[i][j]);
			}
		}
		for (int i = 0; i < floor; i++) {
			free(C[i]);
		}
		free(C);

	}

	return 0;
}