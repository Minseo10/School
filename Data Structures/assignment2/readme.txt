1. 과제2_1번.cpp

1) typedef struct element
: to store only non-zero elements of a matrix
-value: value of an element
-row, col: index of an element

2) typedef struct SparseMatrix
-data: value and location of non-zero elements
-rows: number of rows in a sparsematrix
-cols: number of columns in a sparse matrix 
-terms: number of non-zero terms in a sparse matrix 

3) bool compare(element a, element b)
: this function sorts 'data' array into ascending order

data 배열에서 row가 큰 element가 뒤로 가도록 한다. 
if a,b의 row가 같으면 col이 더 큰 element가 뒤로 간다.

4) int main()
-BT: transpose matrix of B
-sort(BT.data, BT.data + 7, compare): this function sorts 'data' array of BT into ascending order. it is in algorithm header
-matrixB: store all elements of matrix B in 2D array form(including zero elements)
-matrixBT: store all elements of transpose of B in 2D array form(including zero elements)



2. 과제2_2반.c

1) int floor = 3; //first axis of 3D array
int row = 3; //second axis of 3D array
int col = 3; //third axis of 3D array

2) double*** mem_alloc_3D_double() 
: allocate 3D array(m) using dynamic memory allocation, and return m

3) void printArray(double*** a) 
: print a 3D array
parameter
-a: a 3D array to print

4) double*** addition_3D(double*** a, double*** b) 
: add 3D array A and B, store the result into double*** type variable n, and then return n
paramter
-a, b: two 3D arrays. we will add a and b in this function

5) int main()
-A, B: 3D array of double type
-C: 3D array of double type, we will store addition of array A and B in C
