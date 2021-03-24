/**
*author:Idan Damri
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue_bintree_utils.h"

/*****************************************************************/
node_t* closetAncestor(node_t* root, int key1, int key2);
node_t* lookFor(node_t* root, int key, stack_t* stack);
node_t* backtrackBranches(stack_t* stack1, stack_t* stack2);
/*****************************************************************/

int main() {
    int key1, key2;
    node_t *root;
    node_t* res;

    root = getBinTree();
    if(root == NULL)
        exit(EXIT_FAILURE);

    printKeys(root);

    printf("%sLowest Common Ancestor:\nChoose two positive numbers(two keys):\n");
    scanf("%d %d", &key1, &key2);
    res = closetAncestor(root, key1, key2);
    if(res != NULL)
        printf("Key of the lowest ancestor to nodes containing keys %d and %d is %d\n", key1, key2, res->key);
    else
        printf("one of the keys is not belong to the tree\n");
    return 0;
}

/**
 * the correctness is easy, in a tree there's only one path from any two nodes
 * therefore it's sufficient to "record" the two branches in a LIFO order (they recorded via two stacks)
 * after we have two non-null stacks, we only need to backtrack the branches(using the stacks) until finding the
 * lowest common ancestor
 * @param root tree's root
 * @param key1 first key
 * @param key2 second key
 * @return the lowest common ancestor of the two nodes containing key1 and key2
 */
node_t* closetAncestor(node_t* root, int key1, int key2){
    if(root == NULL )
        return NULL;
    stack_t* stack_key1; //a branch of the tree were key1 can be found
    stack_t* stack_key2; //a branch of the tree were key2 can be found
    initStack(&stack_key1);
    //first is the root of the branch that leads to a node with key1
    node_t* first = lookFor(root, key1, stack_key1);
    node_t* second; //second will have the same root, but different path
    if(first == NULL)
        return NULL;
    initStack(&stack_key2);
    second = lookFor(root, key2, stack_key2);
    if(second == NULL)
        return NULL;
    return backtrackBranches(stack_key1, stack_key2);
}
/**
 * look for a node that containing key and record that branch in a LIFO order by using stack
 * @param root
 * @param key
 * @param stack
 * @return the node that contains key, if exists one, NULL otherwise
 */
node_t* lookFor(node_t* root, int key, stack_t* stack){
    if(root == NULL)
        return NULL;
    push(stack,root); //this current node can be in a branch that contains a node that contains key
    if(root->key == key)
        return root; //end of branch, the branch is recorded until this current node
    node_t* temp=lookFor(root->left, key, stack);
    if(temp == NULL)
        temp = lookFor(root->right, key, stack);
    if(temp == NULL)
        pop(stack); //remove this current node since it's not relevant to the branch
    return temp;
}
/**
 * backtrack simultaniously the two branches until the they reach a common node
 * NOTE: I didn't check for some edge cases, this function was created only to be use by the function
 * closestAncestors(...)
 * @param stack1 the first branch
 * @param stack2 the second branch
 * @return a common node to the first elements in the stacks
 */
node_t* backtrackBranches(stack_t* stack1, stack_t* stack2){
    //initially, assume that the size of stack1 is smaller
    int min = stack1->size,  max = stack2->size;
    stack_t* longer = stack2;
    //if the initial assumption is wrong
    if(max < min){
        swap(&min, &max);
        longer = stack1;
    }
    while(min < max){
        pop(longer);
        max--;
    }
    node_t* temp1 = NULL;
    node_t* temp2 = NULL;
    do{
        temp1 = pop(stack1);
        temp2 = pop(stack2);
    }while(temp1 != temp2); //compare addresses

    return temp1; //could also return temp2
}
