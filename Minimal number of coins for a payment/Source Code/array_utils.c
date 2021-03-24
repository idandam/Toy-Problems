/**
 * Author:Idan Damri
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "array_utils.h"

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
int* buildAndDisplayRandArray(int size, bool isNegValid, int lowLim, bool isUnique, int elementOffset){
    int* arr;
    int negRange = 0;
    arr = (int*) calloc(size, sizeof(int));
    if(arr == NULL){
        fprintf(stderr, "err allocating memory using calloc()\n");
        exit(EXIT_FAILURE);
    }
    if(isUnique) {
        setLimitedRangeArray(arr, size, lowLim, elementOffset);
        printArray(arr, size);
        return arr;
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

