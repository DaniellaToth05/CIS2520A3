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

	int length = strlen(expr); // get the length of the expression
	int balanceCount; // variable to keep track of the balance of parentheses

	// check if the expression is empty
	if(length == 0){
		printf("Error: Expression is empty.\n");
		return NULL;
	}

	// check if the expression is a single variable (base case)
	if(expr[0] == '(' && expr[length - 1] == ')'){

		balanceCount = 0; // reset the balance count

		// loop through the expression
		for (int i = 0; i < length - 1; i++){
			// check if the character is an open parenthesis
			if (expr[i] == '('){
				balanceCount++; // increment the balance count
			}

			// check if the character is a close parenthesis
			else if (expr[i] == ')'){
				balanceCount--; // decrement the balance count
			}

			// check if the balance count is 0
			if (balanceCount == 0){
				break; // break the loop
			}
		}

		// if balance count is 0
		if (balanceCount == 0){
			char temp[length - 1]; // create a temporary array to store the expression
			strncpy(temp, expr + 1, length - 2); // copy the expression to the temporary array
			temp[length - 2] = '\0'; // set the last character to null
			return parseExpression(temp); // return the parsed temporary expression
		}
	}

	int isOperator = 0; // variable to check if the expression contains an operator

	// loop through the expression
	for(int i = 0; expr[i] != '\0'; i++){

		// check if the character is an operator
		if(expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/'){
			isOperator = 1; // set the isOperator variable to 1
			break;
		}
	}

	// if the expression does not contain an operator
	if(!isOperator){
		Node* notOperator = createNode(expr); // create a node with the expression
		return notOperator; // return it
	}

	balanceCount = 0; // reset the balance count
	char *operatorPosition = NULL; // variable to store the position of the operator
	int operatorPrecedence = -1; // variable to store the precedence of the operator

	// loop through the expression
	for(int i = 0; expr[i] != '\0'; i++){

		// check if the character is an open parenthesis
		if (expr[i] == '('){
			balanceCount++; // increment the balance count
		}
		// check if the character is a close parenthesis
		else if(expr[i] == ')'){
			balanceCount--; // decrement the balance count
		}
		// check if the balance count is 0
		else if(balanceCount == 0){
			int currentPrecedence = -1; // variable to store the current precedence

			// check if the character is a plus or minus operator
			if ((expr[i] == '+' || expr[i] == '-')){
				currentPrecedence = 0; // set the current precedence to 0 (lowest)
			}

			// check if the character is a multiplication or division operator
			else if ((expr[i] == '*' || expr[i] == '/')){
				currentPrecedence = 1; // set the current precedence to 1 (highest)
			}

			// check if the current precedence is greater than the operator precedence
			if (currentPrecedence > operatorPrecedence){
				operatorPosition = &expr[i]; // set the operator position to the current character
				operatorPrecedence = currentPrecedence; // set the operator precedence to the current precedence
			}
		}
	}
	// check if the operator position is null
	if(operatorPosition == NULL){
		printf("Error: No operator found.\n"); // print an error message
		return NULL;
	}

	char leftExpression[100]; // variable to store the left expression
	char rightExpression[100]; // variable to store the right expression

	strncpy(leftExpression, expr, operatorPosition - expr); // copy the left expression to the leftExpression variable

	leftExpression[operatorPosition - expr] = '\0'; // set the last character to null

	strcpy(rightExpression, operatorPosition + 1); // copy the right expression to the rightExpression variable

	// create a node with the operator
	char stringOperator[2];
	stringOperator[0] = *operatorPosition; // set the first character to the operator
	stringOperator[1] = '\0'; // set the last character to null

	Node *root = createNode(stringOperator); // create a node with the operator

	root->left = parseExpression(leftExpression); // parse the left expression and set it as the left child of the root
	root->right = parseExpression(rightExpression); // parse the right expression and set it as the right child of the root

	return root; // return the root
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