#include<stdio.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 8
#define INF 1000L

typedef struct {
	int dist; //instead of unsorted array 'dist'
	int num; //index number of vertex(a->0, b->1, ...)
}element;
typedef struct {
	element heap[MAX_VERTICES]; //store dist here
	int heap_size;
}HeapType;

//structure in order to specify the parent-child relation
typedef struct Vertex {
	struct Vertex* parent; //parent vertex
}Vertex;

int weight[MAX_VERTICES][MAX_VERTICES] =
{ { 0,3,INF,INF,INF,INF,INF,14 },
{ 3,0,8,INF,INF,INF,INF,10 },
{ INF,8,0,15,2,INF,INF,INF },
{ INF,INF,15,0,INF,INF,INF,INF },
{ INF,INF,2,INF,0,9,4,5 },
{ INF,INF,INF,INF,9,0,INF,INF },
{ INF,INF,INF,INF,4,INF,0,6 },
{ 14,10,INF,INF,5,INF,6,0 } };

HeapType Q; //priority queue(min heap)
int dist[MAX_VERTICES];
Vertex* ver[MAX_VERTICES];
int selected[MAX_VERTICES];


//initialize the heap
void init(HeapType* h) {
	h->heap_size = 0;
}

//find the index of node in heap 'h' which 'num' is a
int find_index(HeapType* h, int a) {
	int ans = 0;
	for (int i = 1;i <= h->heap_size;i++) {
		if (h->heap[i].num == a) {
			ans = i;
			break;
		}
	}
	return ans;
}

//inset 'item' into min-heap
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.dist < h->heap[i / 2].dist)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

//decrease the value of ith element's value to the new value 'item'
void decrease_key_min_heap(HeapType* h, int i, element item) {
	//print error
	if (item.dist > h->heap[i].dist) return;

	//same with insert operation in the min heap
	while (i > 1 && (item.dist < h->heap[i / 2].dist)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// Find a smaller child node
		if ((child < h->heap_size) &&
			(h->heap[child].dist) > h->heap[child + 1].dist)
			child++;
		if (temp.dist <= h->heap[child].dist) break;
		// Move down one level
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void build_min_heap(HeapType* h)
{
	int child; int parent; element temp;

	//walk backwards through the array from n/2 to 1, moving the element on each node until it meets the heap property
	//elements in index n/2+1 to n already met the heap property 
	for (int i = h->heap_size / 2;i >= 1;i--) {
		parent = i;
		child = 2 * i;
		temp = h->heap[i];

		//implement like delete_min_heap function
		while (child <= h->heap_size) {
			// Find a smaller child node
			if ((child < h->heap_size) &&
				(h->heap[child].dist) > h->heap[child + 1].dist)
				child++;
			if (temp.dist <= h->heap[child].dist) break;
			// Move down one level
			h->heap[parent] = h->heap[child];
			parent = child;
			child *= 2;
		}
		h->heap[parent] = temp; //define the position of element in heap[i]

	}
}


// n: the number of vertices on the graph
void prim(int s, int n)
{
	int u, v;
	int i;
	
	init(&Q);
	for (u = 0; u < n; u++){
		Q.heap[u+1].num= u;		
		Q.heap[u+1].dist = INF; 
		dist[u] = INF;
		ver[u]->parent = NULL; //u.parent=NULL
		selected[u] = FALSE;
	}
	Q.heap_size = n;
	Q.heap[s+1].dist = 0;
	
	//inset all vertiecs into the priority queue Q 
	build_min_heap(&Q);
	

	element e2;
	for (i = 0; i < n; i++) {
		e2 = delete_min_heap(&Q); //Extract_Min(Q)
		u = e2.num; int u_dist = e2.dist;

		printf("%d ", u);

		int idx = 0;
		for (v = 0; v <n; v++) {
			if (weight[u][v] != INF) {
				if (!selected[v] && weight[u][v] < dist[v] && u != v) {
					ver[v]->parent = ver[u]; //parent of v is u
					dist[v] = weight[u][v];
					//replace dist[v] into weight[u][v]
					element e3 = { weight[u][v],v };
					decrease_key_min_heap(&Q, find_index(&Q, v), e3); 
				}
			}
		}
		
	}
}

int main(){
	prim(0, MAX_VERTICES);

	return 0;

}