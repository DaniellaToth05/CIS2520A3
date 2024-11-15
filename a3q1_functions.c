#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"

// testing github

Variable variables[10];
int varCount = 0; 


// The createNode function allocates memory to the tree and creates a new node using the given data before returning the node.
Node* createNode(char *data){
	return NULL;
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