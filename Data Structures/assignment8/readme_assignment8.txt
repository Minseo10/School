hw8_1.cpp
(Visual studio 2019)

1) typedef struct element, HeapType
:use this data structure to build max/min heap

2) void init(HeapType* h)
: initialize the heap

3) void insert_min_heap(HeapType* h, element item)
: inset 'item' into min-heap

4) void decrease_key(HeapType* h, int i, element item)
: decrease the value of ith element's value to the new value 'item'
-h: heaptype
-i: index of node that we will change
-item: we will change ith node into item
-implementation is similar with the insert operation of min heap

5) void increase_key(HeapType* h, int i, element item)
: increase the value of ith element's value to the new value 'item'
-h: heaptype
-i: index of node that we will change
-item: we will change ith node into item
-implementation is similar with the delete operation of min heap

6) int main()
-build min heap
-print elements of initial min heap in order
-implement increase_key, decrease_key operation
-print the changed heap in order


hw8_2.cpp
(Visual studio 2019)

1) typedef struct element
-dist: instead of unsorted array 'dist'
-num: index number representing vertex(a->0, b->1, ...)

2) typedef struct Vertex
:structure in order to specify the parent-child relation
- parent: pointer of parent vertex

3) void init(HeapType* h)
: initialize the heap

4) int find_index(HeapType* h, int a)
: find the index of node in heap 'h' which 'num' is a
e.g) if h->heap[x].num == a then return x

5) void insert_min_heap(HeapType* h, element item)
: inset 'item' into min-heap

6) void decrease_key_min_heap(HeapType* h, int i, element item)
: decrease the value of ith element's value to the new value 'item'
-> same with function 4) int- hw8_1.cpp

7) element delete_min_heap(HeapType* h)
: delete the root node in min heap

8) void build_min_heap(HeapType* h)
: sort the nodes in heap into order and build min heap

9) void prim(int s, int n)
: prim algorithm function using min heap
-s: starting vertex
-n: the number of vertices on the graph

