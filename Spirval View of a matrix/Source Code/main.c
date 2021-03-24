/**
 * Author : Idan Damri
 */

#include <stdio.h>
#include <stdlib.h>
#include "array_utils.h"

#define NUMBER_OF_DIRECTIONS 4
enum {RIGHT, DOWN, LEFT, UP} DIRECTIONS;

/***************************************************************/
void printSpiralView(int rows, int cols, int** arr);
/**************************************************************/

int main() {
    int rows, columns;
    int** arr;

    printf("choose the number of rows and columns:\n");
    scanf("%d %d", &rows, &columns);

    arr = (int**) malloc(rows * sizeof(int*));
    for(int i=0; i<rows; i++)
            *(arr + i) = (int*)malloc(columns * sizeof(int));

    initAndDisplayMatrix(rows, columns, arr);

    printf("Spiral view of your matrix:\n");
    printSpiralView(rows, columns, arr);

    return 0;
}
/*
 * NOTE: there's no duplicate of code.
 * every case has different implementation, however they have some similarity.
 * I could write a function f such that a cases statement will look like this:
 * case x:
 * f(params...); break;
 * but it will make the function hard to read and maybe not so easy to understand.
 */
void printSpiralView(int rows, int cols, int** arr) {
    int direction = RIGHT; //set initial direction, starting index will be (0,0) (after we increment col at the first iteration of the loop
    int row = 0, col = -1; 
    int rightLim = cols - 1, downLim = rows - 1, leftLim = 0, upLim = 0; //initialize borders 
    while (upLim <= downLim && leftLim <= rightLim) { //see the solution's idea text file
        switch (direction) {
            case RIGHT:
                col++;
                while (col <= rightLim) {
                    printf("%d, ", arr[row][col]);
                    col++;
                }
                upLim++; //if we reached here then the row we printed is no longer available for traversal, so update the upper border 
                col--;  //get back to the bounds of the array
                break;
            case DOWN:
                row++;
                while (row <= downLim) {
                    printf("%d, ", arr[row][col]);
                    row++;
                }
                rightLim--;
                row--;
                break;
            case LEFT:
                col--;
                while (leftLim <= col) {
                    printf("%d, ", arr[row][col]);
                    col--;
                }
                col++;
                downLim--;
                break;
            case UP:
                row--;
                while (upLim <= row) {
                    printf("%d, ", arr[row][col]);
                    row--;
                }
                row++;
                leftLim++;
                break;
        }
        direction = (direction + 1) % NUMBER_OF_DIRECTIONS;  //change direction 90 degrees clockwise
    }
}
