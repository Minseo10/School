#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

typedef struct {
	ListNode* head;
	ListNode* tail;
	int length;
}ListType;

void error(const char* message) { //print a error message
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(ListType* list) { //initialize a list
	list->length = 0;
	list->head = list->tail = NULL;
}

int is_empty(ListType *list) { //check if the list is empty
	if (list->head == NULL ) return 1;
	else return 0;
}

int get_length(ListType *list) { //return the length of the list
	return list->length;
}

void insert_node(ListNode* head, ListNode* p, ListNode* new_node) { //insert 'new_node' right after node 'p' in the list whose pointer of head pointer is phead
	if (head == NULL) {
		new_node->link = NULL;
	}
	else {
		if (p == NULL) {
			printf("The preceding node cannot be NULL\n");
		}
		else {
			new_node->link = p->link;
			p->link = new_node;
		}
	}
}

void remove_node(ListNode* head, ListNode* p, ListNode* removed) {
	if (head == NULL) 
		printf("The list is blank.\n");
	
	else {
		if (p == NULL) printf("The preceding node cannot be NULL\n");
		else {
			p->link = removed->link;
			free(removed);
		}
	}
}

ListNode* get_node_at(ListType *list, int pos) { //return node pointer in 'pos' in the list
	
	ListNode* tmp_node = list->head;

	if (pos < 0) return NULL;
	for (int i = 0;i < pos;i++) 
		tmp_node = tmp_node->link;
	
	return tmp_node;
}

void add(ListType *list, int position, element data) { //insert new data at the 'position'
	ListNode* p;
	if (position >= 0 && position < list->length) {
		ListNode* node = (ListNode*)malloc(sizeof(ListNode));

		if (node == NULL) error("Memory allocation error");

		node->data = data;
		p = get_node_at(list, position - 1);
		insert_node((list->head), p, node);
		list->length++;
	}
}

void delete(ListType* list, int pos) { //delete a data at the 'pos' in the list
	if (!is_empty(list) && pos >= 0 && pos <list->length) {
		ListNode* p = get_node_at(list, pos - 1);
		ListNode* removed = get_node_at(list, pos);
		remove_node((list->head), p, removed);
		list->length--;
	}
}

element get_entry(ListType* list, int pos) { //return the data at the 'pos'
	ListNode* p;
	if (pos >= list->length) error("Position error");
	p = get_node_at(list, pos);
	return p->data;
}

void display(ListType* list) { //display the data of the whole list in the buffer
	
	ListNode* node = list->head;
	printf("( ");
	for (int i = 0; i < list->length; i++) {
		printf("%d ", node->data);
		node = node->link;
	}
	printf(" )\n");
}

void add_first(ListType *list, element data) { //adds a node at the beginning of the list
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));

	if (node == NULL) error("Memory allocation error");

	node->data = data;
	
	if (list->head == NULL) { //if the list is blank
		node->link = NULL;
		list->head = list->tail=node;
	}
	else {
		node->link = list->head;
		list->head = node;
	}
	list->length++;
}

void add_last(ListType* list, element data) { //adds a node at the end of the list
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));

	if (temp == NULL) error("Memory allocation error");


	temp->data = data;
	temp->link = NULL;

	if (list->tail == NULL) { //if the list is empty
		list->head = list->tail = temp;

	}
	else {
		list->tail->link = temp;
		list->tail = temp;
	}

	list->length++;
}

void delete_first(ListType* list) { //deletes the first node in the list
	if (list->head == NULL) printf("The list is blank.\n");
	else {
		ListNode* removed = list->head;
		list->head = list->head->link;
		free(removed);
		list->length--;
	}
}

void delete_last(ListType* list) {  //deletes the last node in the list
	if (list->head == NULL) printf("The list is blank.\n");
	else{
		ListNode* removed = list->tail;
		ListNode* p = get_node_at(list, (list->length) - 2);
	
		remove_node((list->head), p, removed);
		list->length--;
	}
}

int is_in_list(ListType* list, element item) { // a function that finds a node whose data is 'item'
	ListNode* p = list->head;
	
	while (p != NULL) {
		if (p->data == item) break;
		p = p->link;
	}

	if (p == NULL) return FALSE;
	else return TRUE;
}

int main() {
	ListType list1;
	init(&list1);
	add_first(&list1, 20);
	add_last(&list1, 30);
	add_first(&list1, 10);
	add_last(&list1, 40);
	add(&list1, 2, 70);
	display(&list1);

	delete(&list1, 2);
	delete_first(&list1);
	delete_last(&list1);
	display(&list1);

	printf("%s\n", is_in_list(&list1, 20) == TRUE ? "TRUE" : "FALSE");
	printf("%d\n", get_entry(&list1, 0));

	return 0;
}