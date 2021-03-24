/**
 * Author:Idan Damri
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "array_utils.h"

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
int* buildAndDisplayRandArray(int size, bool isNegValid){
    int* arr;
    int negRange = 0;
    arr = (int*)malloc(size * sizeof(int));
    if(isNegValid)
        negRange = MAX_ELEMENT_VALUE / 2;

    srand(time(NULL));
    printf("your array:\n");
    for(int i=0; i < size; i++) {
        int value = *(arr + i) = (rand() % MAX_ELEMENT_VALUE) - negRange;
        printf("%d, ", value);
    }
    printf("\n");

    return arr;
}
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


