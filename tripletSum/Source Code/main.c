/**
 * @author Idan Damri
 */
#include <stdio.h>
#include <stdlib.h>
#include "array_utils.h"

#define MIN_SIZE 3

/***************************************************/
//set a linked list of such triplets if there's at least one triplet
void setListOfTripletsSum(int* arr, int size);
//after setting the list, print how many triplets exists and print them to the screen
void printResult(linkedlist_t* linkedlist);
/**************************************************/

int main() {
    int size;
    int* arr;
    printf("choose size:\n");
    scanf("%d", &size);
    if(size < MIN_SIZE){
        fprintf(stderr, "size must be no less than 3");
        exit(EXIT_FAILURE);
    }
    arr = buildRandLimitedRangeArray(size);
    printArray(arr, size);
    setListOfTripletsSum(arr,size);
    return 0;
}

void setListOfTripletsSum(int* arr, int size){
    if(arr == NULL || size < MIN_SIZE )
        return;

    int minIndex = MIN_SIZE - 1;
    linkedlist_t* linkedlist; //linked list of triplets
    initLinkedList(&linkedlist);
    triplet_t triplet;
    size_t tripletSize = sizeof(triplet_t);

    quickSort(arr,0, size - 1);
    printf("sorted array in increasing order.\n");
    printArray(arr, size);

    for(int i = size - 1; minIndex <= i; i--){
        int first = 0, last = i - 1;
        while(first < last){
            int sum = *(arr + first) + *(arr + last);
            if(sum < *(arr + i))
                first++;
            else if(*(arr + i) < sum)
                last--;
            else {                                                  //could also write *(arr + i);
                setTriplet(&triplet, *(arr + first), *(arr + last), sum );
                addListNode(&linkedlist, &triplet, tripletSize);
                first++;
                last--;
            }
        }
    }
    printResult(linkedlist);
}
//helper procedure
void printResult(linkedlist_t* linkedlist){
    if(0 < linkedlist->size) {
        printf("there're %d triplets:\n", linkedlist->size);
        printLinkedList(linkedlist, printTriplet);
    }
    else
        printf("no such triplets exists\n");
}