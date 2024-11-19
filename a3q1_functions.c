#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"


Variable variables[10];
int varCount = 0; 


// The createNode function allocates memory to the tree and creates a new node using the given data before returning the node.
Node* createNode(char *data){
	
	// check if data is empty or null
    if (data == NULL || strlen(data) == 0) {
        printf("Error: Cannot create a node with empty or null data.\n");
        return NULL;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node)); // allocate memory for the new node

	// check if memory allocation failed
    if (newNode == NULL) {
        printf("Error: Memory allocation failed for node.\n");
        exit(1);
    }
    
    char *copy = (char*)malloc(strlen(data) + 1); // allocate memory for the data

	// check if memory allocation failed
    if (copy == NULL) {
        printf("Error: Memory allocation failed for node data.\n");
        free(newNode); // free the memory allocated for the node
        exit(1);
    }
    
    strcpy(copy, data); // copy the data to the new memory location	

    
    newNode->left = NULL; // set the left child to NULL
    newNode->right = NULL; // set the right child to NULL
    
	strcpy(newNode->data, copy); // copy the data to the node

    free(copy); // free the memory allocated for the data

    printf("Node created with data: %s\n", newNode->data); 

    return newNode; // return the new node
}


// The parseExpression function parses the expression string passed in from command line, stores the information in a new node, and returns the root node of the tree.
Node* parseExpression(char *expr){
	return NULL;
}


// The preOrder function prints tree nodes in preorder traversal.
void preorder(Node *root){
}


// The inOrder function prints tree nodes in inorder traversal fully parenthesized.
void inorder(Node *root){
}


// The postOrder function prints tree nodes in postorder traversal.
void postorder(Node *root){
}


// The promptVariables function prompts the user to assign values to each variable found in the expression tree. The values should be stored in the Variables struct.
void promptVariables(Node *root){
}


// The calculate function calculates the expression and returns its result. Division by 0 and/or other error scenarios should be checked.
float calculate(Node *root){
	return 0;
}