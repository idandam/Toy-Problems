#include <stdio.h>
#include "array_utils.h"
#define NO_NEG false
#define LOW_LIM 1

/*********************************/
void printLeaders(int* arr, int size);
/*********************************/
int main() {
    int size;
    printf("choose array size\n");
    scanf("%d",&size);
    int* arr = buildAndDisplayRandArray(size, NO_NEG, LOW_LIM);
    printLeaders(arr, size);
    return 0;
}
void printLeaders(int* arr, int size){
    int max = arr[size-1];
    linkedlist_t* leaders;
    initLinkedList(&leaders);
    addListNode(&leaders, &max, sizeof(int));
    for(int i = size - 2; 0 <= i; i--){
        if(max < arr[i]) {
            max = arr[i];
            addListNode(&leaders, &max, sizeof(int));
        }
    }
    printf("the leaders of your array:\n");
    printLinkedList(leaders, printInt);
    printf("\n");
}
