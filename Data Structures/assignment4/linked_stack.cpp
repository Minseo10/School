// linked_stack.cpp : Defines the entry point for the console application.
//Assignment4 number1

//#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef int element;

typedef struct DlistNode { //use circular doubly linked list
	element data;
	struct DlistNode* llink;
	struct DlistNode* rlink;
} StackeNode;

//typedef struct {
//	StackNode* top;
//} LinkedStackType;

void init(DlistNode *phead) //phead is a pointer to the head node
{
	phead->llink = phead;
	phead->rlink = phead;
}

int is_empty(DlistNode* phead) 
{
	return (phead->llink == phead && phead->rlink == phead); //when only the head node exits then the list is empty
}

void push(DlistNode* phead, element data) //insert new node into right of head node
{
	DlistNode* temp = (DlistNode*)malloc(sizeof(DlistNode));
	if (temp == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		return;
	}

	else {
		temp->data = data;
		temp->llink = phead;
		temp->rlink = phead->rlink;
		phead->rlink->llink = temp;
		phead->rlink = temp;
		
	}
}

element pop(DlistNode* phead) //delete the node which is in right side of head node and return the data
{
	if (is_empty(phead)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else {
		DlistNode* temp = phead->rlink;
		int item = temp->data;
		phead->rlink = phead->rlink->rlink;
		phead->rlink->rlink->llink = phead;
		free(temp);
		return item;
	}
}

element peek(DlistNode* phead) //return the data of node which is in right side of head node
{
	if (is_empty(phead)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else {
		return phead->rlink->data;
	}
}

void main()
{
	DlistNode s;
	init(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);

	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
}