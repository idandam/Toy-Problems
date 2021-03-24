/**
* @author: Idan Damri
*/

#include <stdio.h>
#include <stdlib.h>
#include "array_utils.h"

void makeZigzagArray(int* arr, int size);
int main() {
    int size;
    printf("choose array size:\n");
    scanf("%d", &size);
    int* arr = buildRandLimitedRangeArray(size);
    printArray(arr, size);
    makeZigzagArray(arr, size);
    printf("zigzagged your array.\n");
    printArray(arr, size);
    free(arr);
    return 0;
}
/*
We can write a for loop like this (naive way)
for(int i=0; i< size; i++) //assume size was decremented by 1 (so if |A| = n then now size = n-1)
       //if i is even                             if i is odd
       if( ((!(i & 1)) && arr[i+1] < arr[i]) || ((i & 1) && arr[i] < arr[i+1]) )
            swap(&arr[i], &arr[i+1]);
 We can do this with less basic operations
 Observ the truth table :
    i is even | arr[i] < arr[i+1]| swap()
        0     |      0           |    0
        0     |      1           |    1
        1     |      0           |    1
        0     |      1           |    0
    
    Assume z = swap() , x = i is even,  y = arr[i]<arr[i+1]
    then z = (!x and y) or (x and !y)  =  x xor y 
*/
void makeZigzagArray(int* arr, int size){
    if(size == 0 || arr == NULL)
        return;
    size--;
    for(int i=0; i< size; i++)
        if( (!(i&1)) ^ (arr[i] < arr[i+1]) ) //x xor y (in C, the xor operator is ^ )
            swap(&arr[i], &arr[i+1]);
    
}
