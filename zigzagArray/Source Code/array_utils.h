/**
 * @author Idan Damri
 */

#ifndef ZIGZAGARRAY_ARRAY_UTILS_H
#define ZIGZAGARRAY_ARRAY_UTILS_H

#endif //ZIGZAGARRAY_ARRAY_UTILS_H


#define BIN_FLAG 2
#define MAX_ELEMENT_VALUE 50
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

typedef enum {false, true} bool;
typedef struct triplet{
    int a;
    int b;
    int c;
}triplet_t;

typedef struct list_node{
    void* data;
    struct list_node* next;
}list_node_t;

typedef struct linkedlist{
    int size;
    void* head;
}linkedlist_t;

void addListNode(linkedlist_t** list, void* newData, size_t dataSize);
int** initAndDisplayMatrix(int rows, int cols, bool isRandom);
void printMatrix(int** arr, int rows, int cols);
//build,display and return the address of a random array
int* buildAndDisplayRandArray(int size, bool isNegValid, int lowLimt);
int* buildRandLimitedRangeArray(int size);
void quickSort(int* arr, int low, int high);
int partition(int* arr, int low, int high);
int getPivot(int* arr, int low, int high);
void printArray(int* arr, int size);
void swap(int* a, int* b);
void printTriplet(void* triplet);
void addListNode(linkedlist_t** list, void* newData, size_t dataSize);
void printLinkedList(linkedlist_t* list, void(*fptr)(void* data));
void initLinkedList(linkedlist_t** linkedlist);
void setTriplet(triplet_t* triplet, int a, int b, int c);
void printInt(void* x);

