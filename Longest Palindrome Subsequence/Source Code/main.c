/**
 * @author Idan Damri
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "array_utils.h"


/**************************************************************/
#define MAX_LEN 100

//the desired palindrome is not necessarily unique
void longestPalindromeSubsequence(char *sequence, int length);
//initialize mat according to the base cases mentioned in the pdf file
void initBaseCases(int **mat, int n, char* sequence);
//print the result (the length of the desired palindrome and the palindrome itself)
void printResult(int **lengths, int length, char* sequence);
/**************************************************************/

int main() {
    char sequence[MAX_LEN];
    printf("write a string:\n");
    setbuf(stdin,0);
    fgets(sequence, MAX_LEN, stdin);//I didn't check for a bad input.
    longestPalindromeSubsequence(sequence, strlen(sequence) - 1);
    return 0;
}

void longestPalindromeSubsequence(char *sequence, int length) {
    int ** lengths = initZeroMatrix(length, length);
    setbuf(stdout,0);
    initBaseCases(lengths, length, sequence);
    int i = 0, j = 2, prevj = 2;
    //we stop looping when we skipped the entry of the result (lengths[0][length-1])
    //the traversal is done in a diagonal(top to bottom) starting from third main diagonal
    //see pdf file for explanation, if needed.
    while(!(i == 0 && length <= j)){
        while(j < length){
            if(sequence[i] == sequence[j])
                lengths[i][j] = 2 + lengths[i+1][j-1];
            else
                lengths[i][j] = max(lengths[i][j-1], lengths[i+1][j]);
            i++;
            j++;
        }
        j = ++prevj;
        i=0;
    }
    printf("updated matrix(result in entry [0][length-1]:\n");
    setbuf(stdout,0);
    printIntegerMatrix(lengths, length, length);
    printResult(lengths, length, sequence);
    for(int i = 0; i < length; i++)
        free(lengths[i]);

}

void printResult(int **lengths, int length, char* sequence) {
    int maxPalindromeSubseqLength = lengths[0][length - 1];
    char maxPalindromeSubseq[maxPalindromeSubseqLength + 1];
    maxPalindromeSubseq[maxPalindromeSubseqLength] = '\0';
    printf("max palindrome subsequence length = %d\n",maxPalindromeSubseqLength);

    //restore longest palindrome subsequence
    int i = 0, j = length - 1, maxLengthTemp = maxPalindromeSubseqLength;
    int k = 0, l = maxPalindromeSubseqLength - 1;
    while(i < j){ //while didn't reach the main diagonal of lengths
        if(lengths[i][j-1] == lengths[i][j])
            j--;
        else if(lengths[i+1][j] == lengths[i][j])
            i++;
        else{ //lengths[i][j-1] and lengths[i+1][j] are smaller than lengths[i][j]
            maxPalindromeSubseq[k] = sequence[i];
            maxPalindromeSubseq[l] = sequence[j];
            i++;
            j--;
            k++;
            l--;
            maxLengthTemp -= 2;
        }
    }
  if(i == j)//if the palindrome length is odd then print the last element
      maxPalindromeSubseq[k] = sequence[i];
  printf("desired palindrome(not necessarily unique):\n");
  for(int i = 0; i < maxPalindromeSubseqLength; i++)
      printf("%c", maxPalindromeSubseq[i]);
}

void initBaseCases(int **mat, int n, char* sequence) {
    //assume i <= j.
    //mat[i][j] represents the subsequence - sequence[i....j]

    //by definition of a palindrome, one element is a palindrome of size 1
    //any non-empty subsequence contains at least element and therefore contains
    //a palindrome of size 1
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            mat[i][j] = 1;
    n--;
    //iterate the second main diagonal (from above the main diagonal)
    for(int i = 0; i < n; i++) {
        if (sequence[i] == sequence[i + 1])
            mat[i][i + 1] = 2;
    }
    n++;
    printf("matrix after filling according to base cases:\n");
    printIntegerMatrix(mat, n, n);

}
