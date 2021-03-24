/**
 * author: Idan Damri
 * this file represent an interface of useful procedures to use when working with data structures like
 * binary tree, stack and queues
 */

#ifndef UNTITLED_QUEUE_BINTREE_UTILS_H
#define UNTITLED_QUEUE_BINTREE_UTILS_H

#endif //UNTITLED_QUEUE_BINTREE_UTILS_H

#define  MIN_SIZE 3 //minimum number of nodes in a binary tree
#define MAX_SIZE 21 //maximum number nodes in a binary tree
#define SEPARATE "\n--------------------------------------------\n"


typedef enum {false,true} bool;

typedef struct node{ //represents a node of a binary tree
    int key;
    struct node* left; 
    struct node* right;
}node_t;

typedef struct q_node{//represents a node of a queue that contains
    node_t* tree_node; // a pointer to a binary tree node
    struct q_node* next; //next element in the queue 
}q_node_t;
typedef struct q_num_node{
    int data;
    struct q_num_node* next;
}q_num_node_t;

typedef struct queue{
    int size;
    q_node_t* head;
    q_node_t* tail;
}queue_t;
typedef struct queue_num{
    int size;
    q_num_node_t* head;
    q_num_node_t* tail;
}queue_num_t;

typedef struct s_node{//represents a stack node
    node_t* tree_node;
    struct s_node* next;
}s_node_t;

typedef struct stack{
    int size;
    struct s_node* head;
}stack_t;

//I'll skip explanation of some procedures here, since I assume that you have some background with those procedures
//for other procedures , you can find explanation in the c file.
void enqueue(queue_t* queue,node_t* tree_node);
node_t* dequeue(queue_t* queue);
node_t* init();
void enqueue_number(queue_num_t* queue, int data);
int dequeue_number(queue_num_t* queue);
void initNumQueue(queue_num_t** queue);
bool isQueueEmpty(queue_t* queue);
bool isNumQueueEmpty(queue_num_t* queue);
void createChilds(node_t* tree_node, int pos); //create left and right childs of the binary tree rooted at tree_node
void printKeys(node_t* root); //print the keys of the binary tree rooted at root.
void initStack(stack_t** stack);
void push(stack_t* stack, node_t* tree_node);
node_t* pop(stack_t* stack);
bool isEmpty(stack_t* stack);
void initQueue(queue_t** queue);
node_t* getBinTree(); //return a pointer to the root of a binary tree that contains keys ordered in a bfs form
void swap(int* a, int* b); //swap content between what can be found in the address of a and what can be found in the address of b
