#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "array_utils.h"

#define TEST_SIZE 2
#define NO_NEG false
#define LOW_LIM 1

//we say that a positive integer n is of length l, if n contains l digits.
/****************************************************************************************************/
void largestNumberFormedFromArray(int *arr, int size);
//get the lengths list and initialize the ordered pairs array
linkedlist_t *getListAndInitOrderedPairs(int *arr, int size, ordered_pair_t **orderedPairsPtr);
//initialize the lengths array and the ordered pairs array
int *initArrays(int *arr, int size, int *lengthsSize, ordered_pair_t **orderedPairsPtr, int **lengths);
//make an array of ordered pairs from an ordered pairs linked list
void fromOrderedPairsListToArray(linkedlist_t *orderedPairList, ordered_pair_t **orderedPairsArrayPtr);

/**
 *
 * @param num an integer
 * @param digit the "digit" MSD of num
 * @return the "digit" MSD of num
 */
int getDigit(int num, int digit);
/**
 *
 * @param length  the number of digits that num contains
 * @param num
 * @return  num as a string type
 */
char *getString(int length, int num);
/**
 * compare two positive integers according to the digits
 * @param currMaxInteger  the first integer to compare. the address of this integer will contains,
 * at the end of this procedure, the bigger integer between the two.
 * @param currMaxIntegerLength the number of digits that currMaxInteger contains. the address of this value
 * will contains at the end of this procedure, the number of digits that the bigger integer contains
 * @param otherInteger the other integer to compare
 * @param otherIntegerLength the number of digits that otherInteger  contains
 * @return
 */
bool setMaxInteger(int* currMaxInteger, int* currMaxIntegerLength, int otherInteger, int otherIntegerLength);

void freeChoices(char *arr[], int size);

/***************************************************************************************************/
int main() {
   int size;
    printf("choose array size:\n");
    scanf("%d", &size);
    int* arr = buildAndDisplayRandArray(size, NO_NEG, LOW_LIM);
    largestNumberFormedFromArray(arr, size);
   return 0;
}

void largestNumberFormedFromArray(int *arr, int size) {
    quickSort(arr, 0, size - 1);
    printf("quicksort your array\n");
    printArray(arr, size);
    int lengthsSize; //will be initialized after the call to initArrays()
    int* lengths; //the length of an integer is the number of digits that the integer contains
    char* choices[size];
    ordered_pair_t *orderedPairs;
    initArrays(arr, size, &lengthsSize, &orderedPairs, &lengths);
    //the index of the right most integer with lengths[i] number of digits, that we chose from arr
    //for choices[k]
    int toDecrement;
    for(int k = 0; k < size; k++) {
        int currMaxInteger = 0, currMaxIntegerLength = 1;
        for (int i = 0; i < lengthsSize; i++) {
            //if there's an element with lengths[i] digits to compare
            if (orderedPairs[i].left <= orderedPairs[i].right) {
                bool isMaxChanged = setMaxInteger(&currMaxInteger, &currMaxIntegerLength, arr[orderedPairs[i].right], lengths[i]);
                if(isMaxChanged)
                    toDecrement = i;
            }
        }
        //set the correct integer to a string type and put this value at choices[k]
        choices[k] = getString(currMaxIntegerLength, currMaxInteger);
        //we no longer need the integer at arr[orderedPairs[toDecrement].right
        //go one location to the left, this value (if exists, is the next largest integer with
        //lengths[toDecrement] digits
        orderedPairs[toDecrement].right--;
    }
    printf("printing largest number:\n");
    for(int k = 0; k < size; k++)
        printf("%s", choices[k]);
    printf("\nprinting the largest number with a separator:\n");
    for(int k = 0; k < size; k++)
        printf("%s|", choices[k]);
    freeChoices(choices, size);

}

void freeChoices(char *arr[], int size) {
    for(int i = 0; i < size; i++)
        free(arr[i]);

}

char *getString(int length, int num) {
    char* numString = malloc(length * sizeof(char));
    itoa(num, numString, 10);
    return numString;
}

int getDigit(int num, int digit) {
    int x = 1;
    while(0 < digit) {
        x = x * 10;
        digit--;
    }
    return (num % x) / (x / 10);
}

int *initArrays(int *arr, int size, int *lengthsSize, ordered_pair_t **orderedPairsPtr, int **lengths) {
    linkedlist_t *lengthsList = getListAndInitOrderedPairs(arr, size, orderedPairsPtr);
    *lengthsSize = lengthsList->size;
    *lengths = buildArrayFromList(lengthsList);
}

linkedlist_t *getListAndInitOrderedPairs(int *arr, int size, ordered_pair_t **orderedPairsPtr) {
    linkedlist_t *lengths;
    linkedlist_t *orderedPairsList;
    initLinkedList(&lengths);
    initLinkedList(&orderedPairsList);
    ordered_pair_t *o_pair = (ordered_pair_t *) malloc(sizeof(ordered_pair_t));
    int length = floor(log10(arr[0])) + 1;
    addListNode(&lengths, &length, sizeof(int));
    o_pair->left = 0;
    int curr;
    int i = 1;
    while (i < size) {
        if (length < (curr = floor(log10(arr[i])) + 1)) {
            length = curr;
            addListNode(&lengths, &length, sizeof(int));
            o_pair->right = i - 1; //last index of integers with "length" digits
            addListNode(&orderedPairsList, o_pair, sizeof(ordered_pair_t));
            o_pair->left = i; //first index of integers with "lengths"(=curr) digits
        }
        i++;
    }
    o_pair->right = i - 1;
    addListNode(&orderedPairsList, o_pair, sizeof(ordered_pair_t));
    printf("print ordered pairs:\n");
    printLinkedList(orderedPairsList, printOrderedPair);
    fromOrderedPairsListToArray(orderedPairsList, orderedPairsPtr);
    return lengths;
}

void fromOrderedPairsListToArray(linkedlist_t *orderedPairList, ordered_pair_t **orderedPairArrayPtr) {
    int size = orderedPairList->size;
    list_node_t* head = (list_node_t*)(orderedPairList->head);
    *(orderedPairArrayPtr) = (ordered_pair_t*) malloc(size * sizeof(ordered_pair_t));
    for(int i = size - 1; 0 <= i; i--) {
        (*orderedPairArrayPtr + i)->left = ((ordered_pair_t *)(head->data))->left;
        setbuf(stdout,0);
        (*orderedPairArrayPtr + i)->right = ((ordered_pair_t *)(head->data))->right;
        head=head->next;
    }


}
    //MSD = Most Significant Digit
    bool setMaxInteger(int* currMaxInteger, int* currMaxIntegerLength, int otherInteger, int otherIntegerLength) {
        int currMaxIntegerMSD = *currMaxIntegerLength;
        int otherIntegerMSD = otherIntegerLength;
        int d1, d2; //d = digit
        while (true) {
            if(currMaxIntegerMSD == 0){
                if(otherIntegerMSD == 0)
                    break;
                else
                    currMaxIntegerMSD = *currMaxIntegerLength;
            }
            else if(otherIntegerMSD == 0)
                otherIntegerMSD = otherIntegerLength;
            else if ((d1 = getDigit(*currMaxInteger, currMaxIntegerMSD--))
                < (d2 = getDigit(otherInteger, otherIntegerMSD--))) {
                *currMaxInteger = otherInteger;
                *currMaxIntegerLength = otherIntegerLength;
                return true;
            }
            else if(d2 < d1)
                return false;
            //if we reached here then notice that the MSD of the two integers is now decremented by one
        }
        return false;
    }


