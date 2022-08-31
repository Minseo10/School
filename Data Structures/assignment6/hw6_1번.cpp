// heapsort.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

#define MAX_ELEMENT 2000
typedef struct element {
	int key;
} element;

typedef struct {
	element* heap;
	int heap_size;
} HeapType;

// Integer random number generation function between 0 and n-1
int random(int n)
{
	return rand() % n;
}

// Initialization
void init(HeapType* h) {
	h->heap_size = 0;
}

// Insert the item at heap h, (# of elements: heap_size)
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	// The process of comparing with the parent node as it traverses the tree
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // Insert new node
}

// Delete the root at heap h, (# of elements: heap_size)
element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// Find a bigger child node
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// Move down one level
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void build_max_heap(HeapType* h)
{
	int child; int parent; element temp;
	
	//walk backwards through the array from n/2 to 1, moving the element on each node until it meets the heap property
	//elements in index n/2+1 to n already met the heap property 
	for (int i = h->heap_size / 2;i >= 1;i--) { 
		parent = i;
		child = 2 * i;
		temp = h->heap[i]; 

		//implement like delete_max_heap function
		while (child <= h->heap_size) {
			// Find a bigger child node
			if ((child < h->heap_size) &&
				(h->heap[child].key) < h->heap[child + 1].key)
				child++;
			if (temp.key >= h->heap[child].key) break;
			// Move down one level
			h->heap[parent] = h->heap[child];
			parent= child;
			child *= 2;
		}
		h->heap[parent] = temp; //define the position of element in heap[i]
	
	}
}

//input: heap 'h'
//output: sorted element array 'a'
void heap_sort(HeapType* h, element* output, int n)
{
	int i;

	build_max_heap(h);
	for (i = (n - 1); i >= 0; i--) {
		output[i] = delete_max_heap(h);
	}
}

bool check_sort_results(element* output, int n)
{
	bool index = 1; //true
	for (int i = 0;i < n - 1;i++)
		if (output[i].key > output[i + 1].key)
		{
			index = 0; //false
			break;
		}
	return index;
}

int main()
{
	time_t t1;
	//Intializes random number generator 
	srand((unsigned)time(&t1));

	int input_size = 10;	//10, 100, 1000, 5000
	int data_maxval = 10000;

	HeapType* h1 = (HeapType*)malloc(sizeof(HeapType));
	// 'heap' is allocated according to 'input_size'.  heap starts with 1, so 'input_size+1' is used.
	h1->heap = (element*)malloc(sizeof(element) * (input_size + 1));

	// output: sorted result
	element* output = (element*)malloc(sizeof(element) * input_size);



	// Generate an input data randomly
	for (int i = 0; i < input_size; i++)
		h1->heap[i + 1].key = random(data_maxval);	// note) heap starts with 1.
	h1->heap_size = input_size;

	if (input_size) {
		printf("Input data\n");
		for (int i = 0; i < input_size; i++)	printf("%d\n", h1->heap[i + 1].key);
		printf("\n");
	}

	//measure running time
	double start, finish;
	double duration;
	start =(double) clock()/CLOCKS_PER_SEC;

	// Perform the heap sort
	heap_sort(h1, output, input_size);

	finish = (double)clock()/ CLOCKS_PER_SEC;
	duration = finish - start;

	if (input_size ) {
		printf("Sorted data\n");
		for (int i = 0; i < input_size; i++)	
			printf("%d\n", output[i].key);
		printf("\n");
	}

	// Your code should pass the following function (returning 1)
	if (check_sort_results(output, input_size))
		printf("Sorting result is correct.\n");
	else
		printf("Sorting result is wrong.\n");

	printf("\n");

	//print the runtime
	printf("Input size is %d, and the runtime is %.50f seconds\n",input_size, duration);

	return 0;
}