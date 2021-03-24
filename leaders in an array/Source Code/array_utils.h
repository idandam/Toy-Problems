/**
 * @author Idan Damri
 */

#ifndef LEADERS_ARRAY_UTILS_H
#define LEADERS_ARRAY_UTILS_H

#endif //LEADERS_ARRAY_UTILS_H


#define MAX_ELEMENT_VALUE 70

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

typedef struct ordered_pair{
    int left;
    int right;
}ordered_pair_t;

void addListNode(linkedlist_t** list, void* newData, size_t dataSize);
void initAndDisplayMatrix(int rows, int cols, int** arr);
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
void printOrderedPair(void* orderedPair);
void reverseArray(int *arr, int size);
//assuming thhat the elements of the list are added to the head of the list
int *buildArrayFromList(linkedlist_t *linkedlist);
void printInt(void* numPtr);

