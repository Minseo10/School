//#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

typedef struct TreeNode {
	int key;
	struct TreeNode* left, * right;
} TreeNode;

//generate a random number of range 1 to max_value using rand() function
int random(int max_value) {
	int r = rand() % max_value + 1;
	return r;
}

//Insert the key into the binary search tree 
//If key is already in tree, it is not inserted.
void insert_node(TreeNode** root, int key)
{
	TreeNode* p, * t;// p: parent node, t: current node
	TreeNode* n;// n: new node to be inserted
	t = *root;
	p = NULL;
	// Search first
	while (t != NULL) {
		p = t;
		if (key < t->key) t = t->left;
		else t = t->right;
	}
	// Since the key is not in the tree, insertion is possible.
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;
	n->key = key;
	n->left = n->right = NULL;
	
	if (p != NULL) //when the tree is not empty
		if (key < p->key)
			p->left = n;
		else p->right = n;
	else *root = n; //when the tree is empty
}

//let's use inorder traversal to print the sorted results
void inorder(TreeNode* root) {
	if (root) {
		inorder(root->left); // Left subtree
		printf("%d\n", root->key); // Visit root node
		inorder(root->right);// Right subtree
	}
}

int main() {
	int input_size = 1000;
	int data_maxval = 10000;

	int* input = (int*)malloc(sizeof(int) * input_size);
	srand(time(NULL));

	//generate input data randomly
	for (int i = 0; i < input_size;i++) {
		input[i] = random(data_maxval);
	}
	//print out the input data
	printf("random input data: \n");
	for (int i = 0; i < input_size;i++) {
		printf("%d ", input[i]);
	}
	printf("\n");

	//insert elements in the input array iteratively into the binary search tree
	TreeNode* root = NULL;
	for (int i = 0; i < input_size;i++) {
		insert_node(&root, input[i]);
	}

	//print the sorted results
	printf("Binary tree\n");
	inorder(root);
	
	return 0;

}