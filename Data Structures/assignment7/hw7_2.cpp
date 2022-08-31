#include<iostream>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <random>
#define BUCKETS 64
#define DIGITS 4
#define n 1000
using namespace std;
std::random_device rng;
std::uniform_int_distribution<int> random_input(0, 16777215); //1677215=2^24-1

int input[1001] = { 0, }; //save random input data
int output[1001] = { 0, }; //save sorted output data

void RadixSort(int* A, int d) {
    int C[64]; //array for cumulative histogram
    int factor = 1; 
    for (int i = 1;i <= d;i++) {
        //Initialize array C
        for (int j = 0;j < BUCKETS;j++) {
            C[j] = 0;
        }

        //create histogram
        for (int j = 1;j <= n;j++) {
            C[(A[j] / factor) % BUCKETS] += 1;
        }

        //create cumulative histogram
        for (int j = 1;j < BUCKETS;j++) {
            C[j] = C[j] + C[j - 1];
        }

        //generate sorted output data
        for (int j = n;j >=1;j--) {
            output[C[(A[j] / factor) % BUCKETS]] = A[j];
            C[(A[j] / factor) % BUCKETS] -= 1;
        }

        factor *= BUCKETS; //process next digit
    }
}

int main()
{
    // generate 1000 random integer of range [0, 2^24-1]
    for (size_t i = 1; i <= 1000; ++i){
        input[i] = random_input(rng);
    }
   
    //radix sort(into 4 digits)
    RadixSort(input, 4);
    
    for (int i = 0;i < n;i++) {
        cout<<output[i]<<"\n";
    }

    return 0;
}