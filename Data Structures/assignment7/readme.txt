hw7_1.cpp
(Visual Studio 2019)

1) void selection_sort_stable(data* list, int n)
:selection sort function with stable result
-list: data we will sort
-n: size of list
-least: index of element which has minimum data and smallest id among minimum datas

2) rest of the code
same with the skeleton code



hw7_2.cpp
(Visual Studio 2019)

1) #define BUCKETS 64, #define DIGITS 4, #define n 1000
-BUCKETS: range of each digit
-DIGITS: number of digits
-n: number of input data

2) std::random_device rng; 
std::uniform_int_distribution<int> random_input(0, 16777215);
    for (size_t i = 1; i <= 1000; ++i){
        input[i] = random_input(rng);
    }

-> generate 1000 random integer of range [0, 2^24-1] (1677215=2^24-1)

3) int input[1001] , int output[1001] 
-input: save random input data
-output: save sorted output data

4) void RadixSort(int* A, int d)
: divide each data of array A into 4 digits and sort datas at each digit
-int* A: array we which will sort
-int d: number of digits
-int C[64]: array for cumulative histogram

