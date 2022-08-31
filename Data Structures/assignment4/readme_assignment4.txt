1. linked_stack.cpp

1) typedef struct DlistNode 
: circular doubly linked list

2) void init(DlistNode *phead) 
: initialize linked list
-phead: a pointer to the head node

3) int is_empty(DlistNode* phead)
: check if the list is empty
when only the head node exits, then the list is empty

- phead: a pointer to the head node

4) void push(DlistNode* phead, element data) 
: insert new node into right of head node
-phead: a pointer to the head node
-temp: node we will insert

5) element pop(DlistNode* phead) 
: delete the node which is in right side of head node and return the data
-phead: a pointer to the head node
-temp: it is a node we will delete. It is in the right side of the head node.

6) element peek(DlistNode* phead) 
: return the data of node which is in right side of head node
-phead: a pointer to the head node


2. Simulation.cpp
(I only wrote explanations of the revised parts. Rest of the code is same with original code.)

1) int duration = 100; int max_serv_time = 20;
: let's set 'duration' to 100  and 'max_serv_time' to 20 to obtain meaningful results.

2) in main()
int service_time1 = 0; 
int service_time2 = 0;
: service_time1 is the service time left of the customer who is receiving service from the first bank staff
  service_time2 is the service time left of the customer who is receiving service from the second bank staff

3) if (service_time1 > 0 && service_time2 > 0)	
: when both bank staff is serving a customer
->decrement service_time1 and service_time2 by 1

4) if (service_time1 > 0 && service_time2 == 0) 
: only first bank staff is serving a customer
->decrement service_time1 by 1 & take out a customer from the queue and send him/her to the second bank staff

5) if (service_time1 == 0 && service_time2 > 0) 
: only second bank staff is serving a customer
->decrement service_time2 by 1 & take out a customer from the queue and send him/her to the first bank staff

6) if(service_time1 == 0 && service_time2 == 0)
: when no customer is receiving service
->take out a customer from the queue and start the service.

7) printf("\n");
: for convenience
		