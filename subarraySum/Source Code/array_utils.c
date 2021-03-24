
/**
 * Author : Idan Damri
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_utils.h"

#define MAX_ELEMENT_VALUE 20

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
int* buildAndDisplayRandArray(int size){
    int* arr;
    arr = (int*)malloc(size * sizeof(int));

    srand(time(NULL));
    printf("your array:\n");
    for(int i=0; i < size; i++) {
        int value = *(arr + i) = rand() % MAX_ELEMENT_VALUE;
        printf("%d, ", value);
    }
    printf("\n");

    return arr;


}
