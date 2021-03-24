/**
 * Author:Idan Damri
 */

#include <stdio.h>
#include <stdlib.h>
#include "array_utils.h"

#define MAX_LARGEST 3

/*****************************************************************/
int* getMaxProduct(int *arr, int size);
//put in largest the three largest elements of arr
void setLargest(int *arr, int *largest, int size);
//put in smallest the two smallest elements of arr
void setSmallest(int *arr, int size, int *smallest, int max);
/*****************************************************************/


int main() {
    int size;
    printf("choose size:\n");
    scanf("%d", &size);
    if(size < MAX_LARGEST){
        printf("size can be at least 3");
        exit(EXIT_FAILURE);
    }
    int *arr = buildAndDisplayRandArray(size, true);
    int* res = getMaxProduct(arr, size);
    printf("result:{%d, %d, %d}\n",res[0], res[1], res[2]);
    return 0;
}
//see the solution's idea text file or the correctness pdf file
int* getMaxProduct(int *arr, int size) {
    //will contain the three largest elements of arr in increasing order
    //I used heap allocation because we may need to use largest in main()
    int* largest = (int*)malloc(MAX_LARGEST *sizeof(int));
    //will contain the two smallest elements of arr in increasing order
    //smallest will remain on the stack frame of this procedure, we don't need smallest in main()
    int smallest[MAX_LARGEST - 1] = {-1, -1};
    largest[0] = largest[1] = largest[2] = -1;

    setLargest(arr, largest, size); //O(size)
    setSmallest(arr, size, smallest, largest[2]); //O(size)
    
    if(0 <= smallest[0] || largest[2] <= 0 ||
            (0 < largest[0] && (smallest[0] * smallest[1] < largest[0] * largest[1]) ) )
        return largest;
    //modify only the two smallest elements of largest
    largest[0] = smallest[0];
    largest[1] = smallest[1];
    return largest;
}

void setLargest(int *arr, int* largest, int size) {
    int min=arr[0];
    int first, second, third; 
    //find the smallest integer of arr 
    for(int i = 0; i < size; i++) {
        if (arr[i] < min)
            min = arr[i];
    }
    min--; //now, there's no integer in arr that is smaller than min
    first = second = third = min; //initially, set the three largest element to be min and assume they are the three largest elements of arr
    for(int i = 0; i < size; i++){
        int temp = arr[i];
        if(first < temp){
            third = second;
            second = first;
            first = temp;
        }
        else if(second < temp){
            third = second;
            second = temp;
        }
        else if(third < temp)
            third = temp;
    }
    largest[0] = third; largest[1] = second; largest[2] = first;
    printf("the three largest elements of arr: %d, %d, %d\n", *largest, *(largest + 1), *(largest + 2));
}

void setSmallest(int *arr, int size, int *smallest, int max){
    int first = max + 1;
    int second = first;
    for(int i = 0; i < size; i++){
        int temp = arr[i];
        if(temp < first){
            second = first;
            first = temp;
        }
        else if (temp < second){
            second = temp;
        }
    }
    smallest[0] = first; smallest[1] = second;
    printf("the two smallest elements of arr: %d, %d\n", *smallest, *(smallest + 1));
}
