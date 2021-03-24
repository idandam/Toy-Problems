/**
 * author: Idan Damri
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue_bintree_utils.h"

void enqueue(queue_t* queue,node_t* tree_node){
    if(queue->head != NULL) {
        queue->tail->next = (q_node_t *) malloc(sizeof(q_node_t));
        queue->tail = queue->tail->next;
        queue->tail->tree_node = tree_node;
        queue->tail->next = NULL;
    }
    else{
        queue->head = (q_node_t *) malloc(sizeof(q_node_t));
        queue->head->tree_node = tree_node;
        queue->tail = queue->head;
        queue->tail->next = NULL;
    }
}
node_t* dequeue(queue_t* queue){
    q_node_t* temp = queue->head;
    node_t* res = queue->head->tree_node;
    queue->head = queue->head->next;
    temp->next = NULL;
    free(temp);
    return res;
}
void enqueue_number(queue_num_t* queue, int data){
    if(queue->head != NULL) {
        queue->tail->next = (q_num_node_t*) malloc(sizeof(q_num_node_t));
        queue->tail = queue->tail->next;
        queue->tail->data = data;
        queue->tail->next = NULL;
    }
    else{
        queue->head = (q_num_node_t *) malloc(sizeof(q_num_node_t));
        queue->head->data = data;
        queue->tail = queue->head;
        queue->tail->next = NULL;
    }
    queue->size = queue->size + 1;
}
int dequeue_number(queue_num_t* queue){
    q_num_node_t* temp = queue->head;
    int data = queue->head->data;
    queue->head = queue->head->next;
    temp->next = NULL;
    free(temp);
    queue->size = queue->size - 1;
    return data;
}
/**
 * initialize the root of the binary tree
 * @return  the root of the binary tree
 */
node_t* init(){
    node_t* root =(node_t*)malloc(sizeof(node_t));
    root->key = 1;
    root->left = root->right = NULL;
    return root;
}
void initQueue(queue_t** queue){
    *queue = (queue_t*)malloc(sizeof(queue_t));
    (*queue)->head = (*queue)->tail = NULL;
}
void initNumQueue(queue_num_t** queue){
    *queue = (queue_t*)malloc(sizeof(queue_num_t));
    (*queue)->size = 0;
    (*queue)->head = (*queue)->tail = NULL;
}
bool isQueueEmpty(queue_num_t* queue){
    return queue->size == 0;
}
/**
 * create two childs and attach them to the given tree node
 * @param tree_node the root of the sub-tree we're creating
 * @param isRandom get a the value of true if it's a random binary tree, false otherwise
 * @param pos if the tree is not random then we create two children of root at positions pos and pos+1
 *          according to a bfs ordering
 */
void createChilds(node_t* tree_node, int pos){
    tree_node->left = (node_t*)malloc(sizeof(node_t));
    tree_node->right = (node_t*)malloc(sizeof(node_t));

    tree_node->left->key = pos;
    tree_node->right->key = pos + 1;
    tree_node->left->left = tree_node->left->right = tree_node->right->left = tree_node->right->right = NULL;

}

/**
 * print all the keys in the binary tree, in bfs order
 * @param root  the root of the binary tree
 */
void printKeys(node_t* root){
    queue_t* bfsQueue;
    initQueue(&bfsQueue);
    enqueue(bfsQueue, root);
    printf("your tree in a bfs order:\n");
    while(!isEmpty(bfsQueue)){
        node_t* curr = dequeue(bfsQueue);
        printf("%d, ", curr->key);
        if(curr->left != NULL && curr->right != NULL){
            enqueue(bfsQueue, curr->left);
            enqueue(bfsQueue, curr->right);
        }
    }
    printf("\n");
}
void push(stack_t* stack, node_t* tree_node){
    s_node_t* newNode = (s_node_t*)malloc(sizeof(s_node_t));
    newNode->tree_node = tree_node;
    newNode->next = stack->head;
    stack->head = newNode;
    stack->size = stack->size + 1;
}
node_t* pop(stack_t* stack){
    if(!isEmpty(stack)){
        s_node_t* temp = stack->head;
        node_t* res = temp->tree_node;
        stack->head = temp->next;
        temp->next = NULL;
        stack->size = stack->size - 1;
        free(temp);
        return res;
    }
    return NULL;

}
bool isEmpty(stack_t* stack){
    return stack->size == 0;
}
//just messing with some 2-d pointers
void initStack(stack_t** stack){
    *stack = (stack_t*)malloc(sizeof(stack_t));
    (*stack)->size = 0;
    (*stack)->head=NULL;
}

/**
 * build a binary with a bfs ordering from 1 to size
 */
/* for example, if size = 5 then the binary tree is of the form

          1
   2           3
4      5

*/
node_t* getBinTree() {
    int size, i=1;
    queue_t* bfsQueue;
    node_t* root;
    printf("choose a size for your binary tree(3 <= size <= 21)\n");
    scanf("%d",&size);
    if(size < MIN_SIZE || MAX_SIZE < size || (size % 2 == 0))
        return NULL;

    root = init();
    initQueue(&bfsQueue);
    enqueue(bfsQueue, root);
    size--;
    while(i < size){
        node_t* curr = dequeue(bfsQueue);
        createChilds(curr, i+1); //for mapping the correct key depending on the ordering of the keys(I chose bfs)
        enqueue(bfsQueue, curr->left);
        enqueue(bfsQueue, curr->right);
        i = i + 2;
    }
    return root;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


