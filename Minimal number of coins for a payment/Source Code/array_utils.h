
/**
 * Author:Idan Damri
 */

#ifndef MINCOINSFORPAYMENT_ARRAY_UTILS_H
#define MINCOINSFORPAYMENT_ARRAY_UTILS_H

#endif //MINCOINSFORPAYMENT_ARRAY_UTILS_H


#define MAX_ELEMENT_VALUE 50

typedef enum {false, true} bool;

void initAndDisplayMatrix(int rows, int cols, int** arr);
//build,display and return the address of a random array
int* buildAndDisplayRandArray(int size, bool isNegValid, int lowLim, bool isUnique, int elementOffset);
void quickSort(int* arr, int low, int high);
int partition(int* arr, int low, int high);
int getPivot(int* arr, int low, int high);
void printArray(int* arr, int size);
void setLimitedRangeArray(int* arr, int size, int elementOffset, int lowLim);
void swap(int* a, int* b);