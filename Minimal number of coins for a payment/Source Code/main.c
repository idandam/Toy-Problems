/*
 * Author:Idan Damri
 */
#include <stdio.h>
#include <stdlib.h>
#include "array_utils.h"

/***************************************************************/
void minCoins(int* coins, int numOfCoins, int amountToPay); //show the minimum number of coins
void showCoins(int* amounts, int lim, int* coins, int numOfCoins); //show an exact payment option
/***************************************************************/

//I didn't check for bad inputs, all inputs must be nonnegative integers
int main() {
    int amountToPay, numOfCoins, i = 0;
    //you can change it to any number of coins, but in real life it's rare to have more than 5 coins with different amount
    printf("choose an amount of payment and the number of coins:\n");
    scanf("%d %d",&amountToPay, &numOfCoins);
    int coins[numOfCoins];
    printf("choose coins:\n");
    while(i < numOfCoins && scanf("%d", &coins[i]) == 1)
        i++;
    printArray(coins, numOfCoins);
    minCoins(coins,numOfCoins, amountToPay);

    free(coins);
    return 0;
}
/**
 * print to the screen the minimum coins we can use to pay some amount
 * @param coins array of coins
 * @param numOfCoins size of the array
 * @param amountToPay the amount we need to pay
 * I didn't documented this procedure, see the pdf files for that
 */
void minCoins(int* coins, int numOfCoins, int amountToPay){
    int lim = amountToPay + 1;
    int amounts[lim];

    amounts[0] = 0;
    for(int amount = 1; amount <= amountToPay; amount++){
        int min = lim;
        for(int coinIndex = 0; coinIndex < numOfCoins; coinIndex++){
            int j = amount - coins[coinIndex];
            if(0 <= j && amounts[j] < min)
                min = amounts[j];
        }
        amounts[amount] = 1 + min;
    }
    if(lim <= amounts[amountToPay]) {
        printf("can't pay the given amount with the given coins\n");
        return;
    }
    else {
        printf("you can pay an amount of %d with no less than %d coins.\n", amountToPay, amounts[amountToPay]);
    }
    setbuf(stdout ,0);
    printArray(amounts, lim);
    printf("you can use:\n");
    showCoins(amounts, lim, coins, numOfCoins);
}

/**
* show an exact payment option(see pdf file number 5)
* @param amounts the array of amounts, each index represent an amount, the last index is the required amount to pay
* @param lim the size of the amounts array
* @param coins the array of coins
* @param numOfCoins the size of the coins array
*/
void showCoins(int* amounts, int lim, int* coins, int numOfCoins){
    int amount = lim - 1, j = 0;
    int currCoin;
    int counts[lim]; //additional array for counting how many times a coin appear in the payment
    //initially, all coins appear zero times
    for(int k = 0; k < lim; k++){
        counts[k] = 0;
    }
    while(0 < amount){ //while we still have some amount to pay
        currCoin = coins[j]; //try using this coin
        //if using this coin gave a new amount for which the minimum coins
        //to pay is exactly the previous minimum value minus 1(see pdf file 5)
        if(currCoin <= amount && amounts[amount - currCoin] == amounts[amount] - 1){
            counts[currCoin]++; //then we can use this coin. Count 1 for using this coin.
            amount = amount - currCoin; //continue to do the same with the new amount we got after using this coin
        }
        else{ //this coin is not useful
            j++; //try another coin located at the next index in the coins array
            //if you tried all the coins from a given index (that is necessarily greater than the starting index of the coins array)
            if( j == numOfCoins)
                j = 0;  //then try again from the beginning with other coins that positioned before the given index
        }
    }
    j = 0;
    //given that we know that some coin is a good coin, print how many times with can pay the amount with this coin
    while(j < numOfCoins){
        currCoin = coins[j];
        if(0 < counts[currCoin])
            printf("%d coins of %d.\n", counts[currCoin], currCoin);
        j++;
    }

}
