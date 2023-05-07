과제3_2번

1. typedef struct ListNode
: structure type for a node in the list

2. typedef struct ListHeader
-length: number of nodes
-head: head pointer
-tail: pointer of the last node

3. void error(const char* message)
: print a error message
-message: error message

4. void init(ListHeader* list) 
: initialize a list
-list: pointer variable of the list we will initialize

5. void insert_node_last(ListHeader* list,int data ) 
: insert a node at the last of the list
-list:  pointer variable of the list
-data: int type data to that we will insert in the list
-temp: temporary ListNode* type variable to store the data and link of the node we will insert

6. void merge(ListHeader* list1, ListHeader* list2, ListHeader* list3) 
: merge list1 and list2 in ascending order and store it into list3
-list1, list2, list3: pointer variables of three lists. 
                      list a, b are sended to parameter list1, 2, and list c is sended to parameter list3.

-a, b: head pointer of list 1, 2

7. void print_list(ListHeader* list) 
: print a list
-list: pointer variable of the list that we will print

8. int main()

-m, n: number of nodes in list a and b
-int a_data[MAX]: array to store the data of list a
-int b_data[MAX]: array to store the data of list b

과제3_3번

1. typedef struct ListNode
: structure type for a node in the list

2. typedef struct ListHeader
-length: number of nodes
-head: head pointer
-tail: pointer of the last node

3. void error(const char* message)
: print a error message
-message: error message

4. void init(ListHeader* list) 
: initialize a list
-list: pointer variable of the list

5. int is_empty(ListType *list) 
: check if a list is empty
-list: pointer variable of the list

6. int get_length(ListType *list)
: return the length of the list
-list: pointer variable of the list

7. void insert_node(ListNode* head, ListNode* p, ListNode* new_node) 
: insert 'new_node' right after node 'p' in the list whose pointer of head pointer is 'head'
-head: head pointer
-p: a node which will be right before the new node
-new node: a node we will insert

8. void remove_node(ListNode* head, ListNode* p, ListNode* removed)
: remove a node
-head: head pointer
-p: a node which is be right before the node we will remove
-removed: a node we will remove

9. ListNode* get_node_at(ListType *list, int pos) 
: return node pointer whose location is 'pos' in the list
-list: pointer variable of the list
-pos: position of the node

10. void add(ListType *list, int position, element data) 
: insert a new node at  'position' th location
-list: pointer variable of the list
-pos: position where we will add the node
-data: data of the node

11. void delete(ListType* list, int pos) 
: delete a node whose location is 'pos'
-list: pointer variable of the list
-pos: position of the node

12. element get_entry(ListType* list, int pos)
: return the data whose location is 'pos'
-list: pointer variable of the list
-pos: position of the node

13. void display(ListType* list) 
: display the data of the whole list in the buffer
-list: pointer variable of the list

14. void add_first(ListType *list, element data) 
: add a node at the beginning of the list
-list: pointer variable of the list
-data: data of the node

15. void add_last(ListType* list, element data) 
: add a node at the end of the list
-list: pointer variable of the list
-data: data of the node

16. void delete_first(ListType* list) 
: delete the first node in the list
-list: pointer variable of the list

17. void delete_last(ListType* list)
: delete the last node in the list
-list: pointer of the list

18. int is_in_list(ListType* list, element item) 
: check if a node whose data is 'item' exists
-list: pointer of the list
-item: data of a node
-> return TRUE(1) if node exists, and return FALSE(0) if not


