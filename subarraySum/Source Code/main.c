/**
* Author: Idan Damri
*/
#include <stdio.h>
#include <stdlib.h>
#include "array_utils.h"


#define RES_SIZE 2

int* subarraySum(int size, int* arr, int s);
int* initResult(int* res, int start, int end);

int main() {
    int size, s;
    int* arr;
    int* res;

    printf("choose size:\n");
    scanf("%d", &size);
    arr = buildAndDisplayRandArray(size);

    printf("choose sum:\n");
    scanf("%d", &s);
    res = subarraySum(size, arr, s);

    if(res != NULL)
        printf("(%d,%d)\n", res[0],res[1]);
    else
        printf("No such subarray exists\n");

    return 0;
}
int* subarraySum(int size, int* arr, int s){
    if(size == 0)
        return NULL;
    int* res = (int*)malloc(RES_SIZE * sizeof(int));

    if(s == 0) {
        for (int i = 0; i < size; i++)
            if (arr[i] == 0)
                return initResult(res,i, i);

        return NULL; //if we reached here the s=0 and not element of A is 0 so there's no such subarray
    }
    int start=-1, end=0, sum=arr[0];
    while(sum != s && start < size){
        while(sum < s){
            end++;
            if(end == size)
                return NULL;
            sum = sum + arr[end];
        }
        while(s < sum){
            start++;
            sum = sum - arr[start];
        }

    }

    if(sum == s)
        return initResult(res, start+1, end);

    return NULL;
}
int* initResult(int* res, int start, int end){
    *(res) = start;
    *(res+1) = end;
    return res;
}
