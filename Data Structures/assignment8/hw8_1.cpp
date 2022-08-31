#include<stdio.h>
#define MAX_ELEMENT 20

typedef struct {
	int key;
}element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

//initialize the heap
void init(HeapType* h) { 
	h->heap_size = 0;
}

//inset 'item' into min-heap
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);
	
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; 
}

//decrease the value of ith element's value to the new value 'item'
void decrease_key(HeapType* h, int i, element item) { 
	//print error
	if (item.key > h->heap[i].key) printf("error: new key is not smaller than currnet key");

    //same with the insert operation of min heap
	while(i>1 && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

//increase the value of ith element's value to the new value 'item'
void increase_key(HeapType* h, int i, element item)
{
	//print error
	if (item.key < h->heap[i].key) printf("error: new key is not bigger than currnet key");

	int parent, child;
	element temp;
	
	temp = item;
	parent = i;
	child = 2*i;

	//same with delete operation in the min heap
	while (child <= h->heap_size) {
		// Find a smaller child node
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;

		if (temp.key <= h->heap[child].key) break;

		// Move down one level
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
}

int main() {
	//build min heap
	element e1 = { 1 };
	element e2 = { 4 }; 
	element e3 = { 2 };
	element e4 = { 7 };
	element e5 = { 5 };
	element e6 = { 3 };
	element e7 = { 3 };
	element e8 = { 7 };
	element e9 = { 8 };
	element e10 = { 9 };

	HeapType heap;
	init(&heap);
	insert_min_heap(&heap, e1);
	insert_min_heap(&heap, e2);
	insert_min_heap(&heap, e3);
	insert_min_heap(&heap, e4);
	insert_min_heap(&heap, e5);
	insert_min_heap(&heap, e6);
	insert_min_heap(&heap, e7);
	insert_min_heap(&heap, e8);
	insert_min_heap(&heap, e9);
	insert_min_heap(&heap, e10);

	//print elements of initial min heap in order
	printf("Initial min-heap\n");
	printf("  Index: ");
	for (int i = 1;i <= heap.heap_size;i++) {
		printf("%d ", i);
	}
	printf("\n");
	printf("Element: ");
	for (int i = 1;i <= heap.heap_size;i++) {
		printf("%d ", heap.heap[i].key);
	}
	printf("\n");
	printf("\n");

	//implement increase_key, decrease_key operation
	element item1 = { 3 };
	element item2 = { 10 };
	decrease_key(&heap, 4, item1);
	increase_key(&heap, 3, item2);

	//print the heap in order
	printf("After increase/decrease operation\n");
	printf("  Index: ");
	for (int i = 1;i <= heap.heap_size;i++) {
		printf("%d ",i);
	}
	printf("\n");
	printf("Element: ");
	for (int i = 1;i <= heap.heap_size;i++) {
		printf("%d ", heap.heap[i].key);
	}
	printf("\n");

	return 0;
}