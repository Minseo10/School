hw9_1.cpp
Visual Studio2019

1) int transform(char* key)
: transform the string key into and integer by summing ASCII codes of an each character
-key: pointer of the string
-number: sum of the ASCII codes

2) int hash_function(char* key)
: division function (key mod TABLE SIZE)
-key: pointer of the string

3) void hash_chain_add(element item, ListNode* ht[])
: add item to the hash table
-item: string we will add to the hash table
-ht: deliver hash_table[TABLE_SIZE] to this parameter

4) void hash_chain_search(element item, ListNode* ht[])
: search item and print whether the search is successed or not
-item: string we will add to the hash table
-ht: deliver hash_table[TABLE_SIZE] to this parameter

5) void hash_chain_print(ListNode* ht[])
: print the hash table
-item: string we will add to the hash table
-ht :deliver hash_table[TABLE_SIZE] to this parameter

6) void init_table(ListNode* ht[])
: initialize the hash tale with null pointer
-ht: deliver hash_table[TABLE_SIZE] to this parameter

7) void hash_chain_delete(element item, ListNode* ht[])
: delete item in the hash table
-t: currnet node
-node_before: node which is located right before t



hw9_2.cpp

1) int random(int max_value)
: generate a random number of range 1 to max_value using rand() function
-max_value: maximum range of  number we can generate

2) void insert_node(TreeNode** root, int key)
: Insert the key into the binary search tree. If key is already in tree, it is not inserted.
-root: pointer of the root node 
-key: value we will insert
-p: parent node
-t: current node
-n: new node to be inserted

3) void inorder(TreeNode* root)
: let's use inorder traversal to print the sorted results(inorder traversal: visit left subtree, root node, right subtree in order) 
-root: node we will visit


