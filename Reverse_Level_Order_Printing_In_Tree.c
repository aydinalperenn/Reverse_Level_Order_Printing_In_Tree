/*
    Alperen Aydın
      201180014
    Data Structures
    Assignment 3
*/

// C program to print binary tree reverse level order traversal

#include <stdio.h>
#include <stdlib.h>

//A binary tree node has data, pointer to left and right child 
struct treeNode
{
    int data;
    struct treeNode* leftptr;
    struct treeNode* rightptr;
};

struct nodes{  // For build a struct array to use storage and printing
    int data;
    int level;
};

//Function prototypes

void reverseLevelOrder(struct treeNode* root);
struct treeNode* newNode(int data);
int findNumLevel(struct treeNode* root);
int max (int a, int b);
void makeArrNumElementsOfEachLevel (struct treeNode* root, int arr[], int level);
int findMaxElementSize(int arr[], int n);
void setArrOfData(struct treeNode* root,  struct nodes structNodes[], int level, int* index);
void print(struct nodes structNodes[], int n, int numLevel, int maxElementSize, int temp);



// It is the helper function to find the max number in the two elements which sent with parameter
int max(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

// Function to find numLevel (how many levels in th tree)
int findNumLevel (struct treeNode* root){ // That function finds max node number

    int numLevel = 0;
    if(root!=NULL){ /* Referenced from ceng205-ders11.pdf, but I can say that I referenced only %15-20 percent from PDF for traversaling. The others were written by me.*/
        int left = findNumLevel(root->leftptr);
        int right = findNumLevel(root->rightptr);
        numLevel = max(left, right) + 1;
    }

    return numLevel;
}

// Function to makeArray for filling the array with NumElements in each level
void makeArrNumElementsOfEachLevel (struct treeNode* root, int arr[], int level){

    if (root == NULL){
        return;
    }

    // Increase the number of nodes
    arr[level]++;

    // Recursive for left and right nodes
    makeArrNumElementsOfEachLevel(root->leftptr, arr, level+1);
    makeArrNumElementsOfEachLevel(root->rightptr, arr, level+1);
}

// That function finds how many elements in the tree
int findMaxElementSize(int arr[], int n){ //
    int maxElementSize= 0;
    for(int i=0; i<n; i++){

        maxElementSize += arr[i];

    }
    return maxElementSize; // Assign the maxElementSize variable
}

/*  The function which assign datas and its levels in a struct array with the elements int the tree respectively */
void setArrOfData(struct treeNode* root,  struct nodes structNodes[], int level, int* index){

    if (root == NULL){
        return;
    }

    structNodes[*index].data = root->data;
    structNodes[*index].level = level;
    (*index)++;

    setArrOfData(root->leftptr, structNodes, level+1, index);
    setArrOfData(root->rightptr, structNodes, level+1, index);
}

// To print datas with the order of requested in the question
void print(struct nodes structNodes[], int n, int numLevel, int maxElementSize, int temp){
    // temp is for check how many data printed
    // maxElementSize is for check the temp is reached to num of all elements
    // numLevel is for printing the right order (requested in the question)
    while(temp!=maxElementSize){ //
        for(int i = 0; i<n; i++){
            if(structNodes[i].level == numLevel){
                printf("%d ", structNodes[i].data);
                temp++;
            }
        }
        numLevel--;
    }
}




//Function to print reverse level order traversal a binary tree
void reverseLevelOrder(struct treeNode* root)
{
    int numLevel = 1; // The variable which measure the total level num
    int maxElementSize = 0; /* The variable which include the number of elementsin the tree. (It will be used to create struct array and print function) */

    numLevel = findNumLevel(root);  // To calculate how many levels in th tree

    int arrNumElementsOfEachLevel[numLevel]; /* Make an  empty list to store how many element in each level. For example, Let's say 2 elements in first level, then arr arrNumElementsOfEachLevel[0] = 2 */
    for(int i = 0; i<numLevel; i++){
        arrNumElementsOfEachLevel[i] = 0;
    }

    makeArrNumElementsOfEachLevel(root,arrNumElementsOfEachLevel,0); /* to calculate how many elements in each level */

    // Find maxElementSize
    maxElementSize = findMaxElementSize(arrNumElementsOfEachLevel, numLevel); // To find how many elements in the tree

    /*
       Now, we will create a struct nodes array which include all node->data's and all nodes' levels in the tree.
       Then we will assign all datas.
       Finally, we will print order which requested in the question thanks to array
    */

    struct nodes structNodes[maxElementSize];  //Creating the array which will be included datas

    int* index = 0; // the index variable to set datas in the struct array
    setArrOfData(root, structNodes,  1, &index); // set the struct array with tree nodes datas and levels

    print(structNodes,maxElementSize, numLevel, maxElementSize, 0); // print datas with the order of requested in the question


}

//Insert new node to the binary tree
struct treeNode* newNode(int data)
{
    struct treeNode* treeNode = (struct treeNode*) malloc(sizeof(struct treeNode));
    treeNode->data = data;
    treeNode->leftptr = NULL;
    treeNode->rightptr = NULL;
    return(treeNode);
}

int main()
{
    struct treeNode *root = newNode(9);
    root->leftptr = newNode(12);
    root->rightptr = newNode(21);
    root->leftptr->leftptr = newNode(15);
    root->leftptr->rightptr = newNode(8);
    root->rightptr->leftptr = newNode(7);
    root->rightptr->rightptr = newNode(11);


    printf("Level Order traversal of binary tree is \n");
    reverseLevelOrder(root);
    return 0;
}
