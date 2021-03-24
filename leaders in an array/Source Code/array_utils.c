
/**
 * @author:Idan Damri
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "array_utils.h"
#include <math.h>

#define BIN_FLAG 2


void initAndDisplayMatrix(int rows, int cols, int** arr){
    int size = rows*cols;
    srand(time(NULL));
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            arr[i][j] = rand() % size; //I chose that an element of the matrix is an integer that belong to [0,size-1]
            printf("%4d",arr[i][j]);
        }
        printf("\n\n");
    }
}
int* buildAndDisplayRandArray(int size, bool isNegValid, int lowLim){
    int* arr;
    int negRange = 0;
    arr = (int*) calloc(size, sizeof(int));
    if(arr == NULL){
        fprintf(stderr, "err allocating memory using calloc()\n");
        exit(EXIT_FAILURE);
    }
    if(isNegValid)
        negRange = MAX_ELEMENT_VALUE / 2;

    srand(time(NULL));
    for(int i = 0; i < size; i++)
        *(arr + i) = (rand() % MAX_ELEMENT_VALUE) + lowLim - negRange;

    printArray(arr, size);
    return arr;
}
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}void quickSort(int* arr, int low, int high){
    if(high <= low)
        return;
    // the index of the pivot
    int pInd = partition(arr, low, high);
    quickSort(arr, low, pInd - 1);
    quickSort(arr, pInd + 1, high);
}
int partition(int* arr, int low, int high){
    //pivot's index
    int pInd = getPivot(arr, low, high);
    while(low <= pInd && pInd <= high) {
        while (low <= pInd && arr[low] < arr[pInd])
            low++;
        while (pInd <= high && arr[pInd] < arr[high])
            high--;
        swap(&arr[low], &arr[high]);
        high--;
        low++;
        if (low - 1 == pInd)
            pInd = high = high + 1;
        else if(high + 1 == pInd)
            pInd = low = low - 1;
    }
    return pInd;
}
//simple pivot calculation, not the best of course (like finding  the median O(n) time)
int getPivot(int* arr, int low, int high){
    int mid = (high + low) / 2;
    int a = arr[low], b = arr[mid], c = arr[high];
    if(a <= b){
        if(b <= c)
            return mid;
        if(a <= c)
            return high;
        return low;
    }
    else if(a <= c)
        return  low;
    else if(b <= c)
        return high;
    return mid;
}
void printArray(int* arr, int size){
    if(0 < size && arr != NULL) {
        printf("your array:\n");
        for (int i = 0; i < size; i++)
            printf("%d, ", arr[i]);

        printf("\n");
    }
}
void setLimitedRangeArray(int* arr, int size, int lowLim,  int elementOffset){
    int i = 0;
    int value;
    srand(time(NULL));
    while(i < size) {
        do{
            value = rand() % size + lowLim;
        }while(*(arr + value - lowLim));

        *(arr + value - lowLim) = value;
        i++;
    }
    i = 0;
    while(i < size){
        if(rand() % BIN_FLAG)
            *(arr + i) = *(arr + i) + elementOffset;
        i++;
    }
}

int* buildRandLimitedRangeArray(int size){
    int i = 0, range = 2*size;
    int temp[range];
    int* arr = (int*)calloc(size, sizeof(int));
    for(int j = 0; j < range; j++)
        temp[j] = 0;

    srand(time(NULL));
    while(i < size){
        int value = rand() % range + 1;
        while(temp[value])
            value = rand() % range + 1;
        temp[value] = 1;
        *(arr + i) = value;
        i++;
    }
    //change first entry to be greater than zero (make  the next line a comment if zero can be an element of the array
    *arr = rand() % (range + 1) + range + 1;
    return arr;
}
void printTriplet(void* triplet){
    if(triplet != NULL){
        printf("{%d,%d,%d}\n", ((triplet_t*)triplet)->a, ((triplet_t*)triplet)->b, ((triplet_t*)triplet)->c);
    }
}
void addListNode(linkedlist_t** list, void* newData, size_t dataSize){
    if(list == NULL || newData == NULL)
        return;
    list_node_t* newListNode = (list_node_t*)malloc(sizeof(list_node_t));
    newListNode->data = malloc(dataSize);
    newListNode->next = (*list)->head;
    for(int i = 0; i < dataSize; i++)
        *(char*)(newListNode->data + i) = *(int*)(newData + i);
    (*list)->head = newListNode;
    (*list)->size = (*list)->size + 1;
}

void printLinkedList(linkedlist_t* list, void(*fptr)(void* )){
    if(list == NULL){
        fprintf(stderr,"list is empty");
        exit(EXIT_FAILURE);
    }
    list_node_t* curr = list->head;
    while(curr != NULL){
        //execute the first instruction given the address of the function (with the given parameter)
        (*fptr)(curr->data);
        curr=curr->next;
    }
}
void initLinkedList(linkedlist_t** linkedlist){
    *linkedlist = (linkedlist_t*)malloc(sizeof(linkedlist_t));
    **linkedlist = (linkedlist_t){0}; //initialize all members to the appropriate zero for their type.
}
void setTriplet(triplet_t* triplet, int a, int b, int c){
    if(triplet != NULL) {
        triplet->a = a;
        triplet->b = b;
        triplet->c = c;
    }
}
void printOrderedPair(void* orderedPair){
    printf("(%d,%d)\n",((ordered_pair_t*)(orderedPair))->left, ((ordered_pair_t*)(orderedPair))->right);
}

void reverseArray(int *arr, int size) {
    int i = 0, j = size - 1;
    while (i < j)
        swap(&arr[i++], &arr[j--]);
}
int *buildArrayFromList(linkedlist_t *linkedlist) {
    list_node_t *curr = linkedlist->head;
    int size = linkedlist->size;
    int *arr = (int *) malloc(linkedlist->size * sizeof(int));
    int i = size - 1;
    while (curr) {
        *(arr + i) = *((int *) curr->data);
        curr = curr->next;
        i--;
    }
    return arr;
}
void printInt(void* numPtr){
    printf("%d, ", *(int*)numPtr);
}

