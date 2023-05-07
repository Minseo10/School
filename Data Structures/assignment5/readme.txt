1. hw5_2.c
1) TreeNode* tree_successor(TreeNode* p)
: we will find the successor of node p
-TreeNode* y: we will save successor node in y(second case)

2. hw5_3.c
1) TreeNode* tree_predecessor(TreeNode* p) 
: we will find the predecessor of node p
-TreeNode* y: we will save predcessor node in y(second case)


3. hw5_4.c
1) void delete_node(TreeNode** root, int key)
: Deletion in binary search tree

-TreeNode* t: node whose data==key
-TreeNode* p: parent node of t
-TreeNode* child: child node of t
-TreeNode* pred: predecessor of node t
-TreeNode* pred_p: parent node of pred

//Case3
-Find the predecessor at right subtree
-Keep moving to the right and find the predcessor
-bring pred's right child node to predecessor's original location
-bring predecessor node to the location of node t 
