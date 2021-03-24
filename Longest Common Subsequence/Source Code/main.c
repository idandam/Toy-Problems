/**
* @author Idan Damri
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "array_utils.h"

#define LOW_LIM 0

/***********************************/
int** LCS(int *A, int n, int *B, int m);
void restoreLCS(int *A, int n, int m, int **arr);
/***********************************/
int main() {
    int n, m;
    int *A, *B;
    int **arr;
    printf("choose size of A and then size of B:\n");
    scanf("%d %d", &n, &m);
    A = buildAndDisplayRandArray(n, false, LOW_LIM);
    B = buildAndDisplayRandArray(m, false, LOW_LIM);
    arr = LCS(A, n, B, m);
    printf("the length of the LCS = %d.\n", arr[n][m]);
    if(0 < arr[n][m]) {
        printf("the LCS:\n");
        restoreLCS(A, n, m, arr);
    }
    return 0;
}

int** LCS(int *A, int n, int *B, int m) {
    int **arr = initAndDisplayMatrix(n + 1, m + 1, false);
    for (int i = 0; i < n + 1; i++)
        arr[i][0] = 0;
    for (int i = 1; i < m + 1; i++)
        arr[0][i] = 0;

    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (A[j - 1] == B[i - 1])
                arr[j][i] = 1 + arr[j - 1][i - 1];
            else
                arr[j][i] = max(arr[j-1][i], arr[j][i-1]);
        }
    }
    return arr;
}

void restoreLCS(int *A, int n, int m, int **arr) {
    int i = n, j = m;
    linkedlist_t *LCS;
    initLinkedList(&LCS);
    int k = arr[i][j];
    while (0 < k) {
        if (arr[i-1][j] == arr[i][j])
            i--;
        else if (arr[i][j-1] == arr[i][j])
            j--;
        else {
            i--;
            j--;
            k--;
            addListNode(&LCS, &(A[i]), sizeof(int));
        }
    }
    printLinkedList(LCS, printInt);
}
