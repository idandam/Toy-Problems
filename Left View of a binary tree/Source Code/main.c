/**
 * author: Idan Damri
 */

#include <stdio.h>
#include "queue_bintree_utils.h"

/*****************************************************************/
int recPrintLeftView(node_t* root, int curr_level, int max_level);
void printLeftView(node_t* root);
/*****************************************************************/

int main() {
    node_t* root = getBinTree();
    printKeys(root);
    printf("%srecursive Left View:\n", SEPARATE);
    recPrintLeftView(root, 0 , -1);
    printf("%snon-recursive Left View:\n", SEPARATE);
    printLeftView(root);
    return 0;
}

/**
 * recursive function - prints the left view of a tree (a node v is a left view node if he's the left most node
 * at some level 0 <= i of the binary tree)
 * @param root the root of the binary tree
 * @param curr_level - the current level of the tree at the current stack frame of the recursive iteration
 * @param max_level - for all level 0 <= i < = max_level of the tree, we already printed the left most node at level i.
 *        we didn't print nodes that belongs to a level greater than max_level
 * @return the maximum level defined above
 */
int recPrintLeftView(node_t* root, int curr_level, int max_level){
    if(root == NULL)
        return max_level;
    if(max_level < curr_level){     //if we are currently at a level for which we didn't print any node
        printf("%d, ", root->key); //then print the key of the first node we encountered(it's the left most node)
        max_level = curr_level;    //update
    }
    max_level = recPrintLeftView(root->left, curr_level + 1, max_level); //print left view nodes belong to left subtree of root
    //max_level can get a new value during the traversal of the left subtree of root
    max_level = recPrintLeftView(root->right, curr_level +1, max_level); //print left view nodes belong to right subtree of root
    return max_level;
}
/*
 * same functionality of the function recPrintLeftView(...)
 * instead of using recursion, I used two queues: for the nodes of the binary tree, and for the level each node belong to
 * I know I could just use a field of a node level is a queue, I chose another approach(for practice...)
 */
void printLeftView(node_t* root){
    int curr_level = 0, max_level = -1;
    queue_t* queue;
    queue_num_t* numQueue;

    initQueue(&queue);
    initNumQueue(&numQueue);

    enqueue(queue, root);
    enqueue_number(numQueue, curr_level);

    while(!isQueueEmpty(queue)){
        root = dequeue(queue);
        curr_level = dequeue_number(numQueue);
        if(max_level < curr_level){
            printf("%d, ", root->key);
            max_level = curr_level;
        }
        if(root->left != NULL && root->right != NULL){
            enqueue(queue, root->left);
            enqueue(queue, root->right);
            enqueue_number(numQueue, curr_level+1);
            enqueue_number(numQueue, curr_level+1);
        }
    }
}