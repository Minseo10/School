#include<stdio.h>
#include<stdlib.h>
#define MAX 10

typedef struct ListNode {
	int data;
	struct ListNode* link;
}ListNode;

typedef struct ListHeader {
	int length;
	ListNode* head;
	ListNode* tail;
}ListHeader;

void error(const char* message) { //print a error message
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(ListHeader* list) { //initialize a list
	list->length = 0;
	list->head = list->tail=NULL;
}

void insert_node_last(ListHeader* list,int data ) { //insert a node at the last of the list
	
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));

	if (temp == NULL) error("Memory allocation error");
	
	
	temp->data = data;
	temp->link = NULL;

	if (list->tail == NULL) { //if the list is empty
		list->head = list->tail=temp;
		
	}
	else {
		list->tail->link = temp;
		list->tail = temp;
	}

	list->length++;
	
}

void merge(ListHeader* list1, ListHeader* list2, ListHeader* list3) { //merge list1 and list2 in ascending order and store it into list3
	
	ListNode* a = list1->head;
	ListNode* b = list2->head;

	while (a && b) {
		
		if (a->data == b->data) {
			insert_node_last(list3, a->data);
			insert_node_last(list3, b->data);
			a = a->link;
			b = b->link;
		}
		else if (a->data > b->data) {
			insert_node_last(list3, b->data);
			b = b->link;
		}
		else {
			insert_node_last(list3, a->data);
			a = a->link;
		}
	}

	for (;a != NULL;a = a->link) {
		insert_node_last(list3, a->data);
	}
	for (;b != NULL;b = b->link) {
		insert_node_last(list3, b->data);
	}
}

void print_list(ListHeader* list) { //print a list
	ListNode* p = list->head;
	for (;p;p = p->link) {
		printf("%d ", p->data);
	}
}

int main() {
	ListHeader list1, list2, list3;

	//initialize list a, b, and c
	init(&list1);
	init(&list2);
	init(&list3);

	int m, n; //number of nodes in list a and b
	int a_data[MAX] = { 0, }; //array to store the data of list a
	int b_data[MAX] = { 0, }; //array to store the data of list b

	printf("number of nodes in list a and b\n");
	scanf_s("%d %d", &m, &n);

	printf("list a\n");
	for (int i = 0; i < m;i++) {
		scanf_s("%d", &a_data[i]);
	}
	printf("list b\n");
	for (int i = 0; i < n;i++) {
		scanf_s("%d", &b_data[i]);
	}

	//generate list a
	for (int i = 0; i < m;i++) {
		insert_node_last(&list1, a_data[i]);
	}
	
	//generate list b
	for (int i = 0; i < n;i++) {
		insert_node_last(&list2, b_data[i]);
	}

	merge(&list1, &list2, &list3);
	printf("let's merge list a and b\n");
	print_list(&list3);
	
	return 0;
}

