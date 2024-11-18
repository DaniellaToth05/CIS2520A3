#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"

Variable variables[10];
int varCount = 0; 


// The createNode function allocates memory to the tree and creates a new node using the given data before returning the node.
Node* createNode(char *data){
	
	// check if data is not null
	if(data !=NULL){

		Node *newNode = malloc(sizeof(Node)); // allocate memory for the new node
		
		// check if memory allocation was successful
		if(newNode != NULL){
			int end = sizeof(newNode->data) - 1; // the last index of the data array (-1 because of the null terminator)
			strncpy(newNode->data, data, end); // copy the data into the new node
			newNode->data[end] = '\0';  // add the null terminator

			// set the left and right pointers to null
			newNode->left = NULL; 
			newNode->right = NULL;
			return newNode;
		}
		else{
			printf("Error: memory allocation failed\n");
			exit(1);
		}
	}
	else{
		printf("Error: data is null\n");
		return NULL;
	}
	return NULL;
	 
}

// The parseExpression function parses the expression string passed in from command line, stores the information in a new node, and returns the root node of the tree.
Node* parseExpression(char *expr){
	
	Node *left = NULL; // left node
	char value[10]; // value of the node
	int i = 0; 

	while(*expr == ' '){ // skip any leading white spaces
		expr++;
	}

	
	if (*expr == '(') {
		expr++; // skip the first opening bracket'
		left = parseExpression(expr); // recursively parse the inner expression

		// count to track nested parentheses
		int count = 1;

		// loop until the corresponding closing parenthesis is found
		while (count != 0 && *expr != '\0') {
			if (*expr == '(') {
				count++; // another opening bracket was found, increase the count
			} 
			else if (*expr == ')') {
				count--; // a closing bracket was found, decrease the count
			}
			expr++;
		}

		// skip the final closing parenthesis if it's balanced
		if (*expr == ')'){
			expr++;
		} 

		while(*expr == ' '){ // skip any trailing white spaces
			expr++;
		}

		// check if the character is an operator
		if(*expr == '+' || *expr == '-' || *expr == '*' || *expr == '/'){ // check if the character is an operator
			value[0] = *expr; // add the operator to the value array
			value[1] = '\0'; // add the null terminator to the value array
			expr++; // move to the next character
			
			Node *root = createNode(value); // create a new node with the operator

			// recursively parse the left and right expressions
			root->left = left;
			root->right = parseExpression(expr);

			return root;
		}
		return left;
	}
	
	// check if the character is a digit or a decimal point
	while(isdigit(*expr) || isalpha(*expr) || *expr == '.'){ // check if the character is a digit or a decimal point
		value[i] = *expr; // add the character to the value array
		i++; // move to the next index
		expr++; // move to the next character
	}
	value[i] = '\0'; // add the null terminator to the value array

	// check if the value is not empty
	if(i>0){
		return createNode(value); // create a new node with the value
	}
		

	while(*expr == ' '){ // skip any trailing white spaces
		expr++;
	}

	// check if the character is an operator
	if(*expr == '+' || *expr == '-' || *expr == '*' || *expr == '/'){ // check if the character is an operator
		value[0] = *expr; // add the operator to the value array
		value[1] = '\0'; // add the null terminator to the value array
		expr++; // move to the next character

		Node *root = createNode(value); // create a new node with the operator

		// recursively parse the left and right expressions
		root->left = parseExpression(expr);
		root->right = parseExpression(expr);

		return root;
	}
	return NULL;
}

// The preOrder function prints tree nodes in preorder traversal.
void preorder(Node *root){

	// if the root is not null
	if(root != NULL){
		printf("%s ", root->data); // print the data of the node
		preorder(root->left); // recursively print the left node
		preorder(root->right); // recursively print the right node
	}
	else {
		return; // return if the root is null
	}
}

// The inOrder function prints tree nodes in inorder traversal fully parenthesized.
void inorder(Node *root){

	// if the root is not null
	if(root != NULL){

		
		if(root->left != NULL || root->right != NULL){
			printf("("); // print the opening parenthesis
		}

		
		inorder(root->left); // recursively print the left node
		printf("%s", root->data); // print the data of the node
		inorder(root->right); // recursively print the right node


		if(root->left != NULL || root->right != NULL){
			printf(")"); // print the closing parenthesis
		}
	}
	else {
		return; // return if the root is null
	}
}

// The postOrder function prints tree nodes in postorder traversal.
void postorder(Node *root){
	
	// if the root is not null
	if(root != NULL){
		postorder(root->left); // recursively print the left node
		postorder(root->right); // recursively print the right node
		printf("%s ", root->data); // print the data of the node
	}
	else {
		return; // return if the root is null
	}
}

// The promptVariables function prompts the user to assign values to each variable found in the expression tree. The values should be stored in the Variables struct.
void promptVariables(Node *root){
	if(root != NULL){
		if(isalpha(root->data[0]) && root->data[0] == 'x'){ // check if the data is a letter
			int found = 0; // flag to check if the variable is already in the variables array

			// loop through the variables array
			for(int i = 0; i < varCount; i++){
				if(strcmp(variables[i].varName, root->data) == 0){ // check if the variable is already in the variables array
					found = 1; // set the flag to true
					break; // break out of the loop
				}
			}

			// if the variable is not in the variables array
			if(found == 0){
				if(varCount == 10){ // check if the variable count is 10
					printf("Error: too many variables\n"); // print an error message
					exit(1); // exit the program
				}
				else if(varCount < 10){ // check if the variable count is less than 10
					printf("Enter a value for %s: ", root->data); // prompt the user to enter a value for the variable
					
					while(scanf("%f", &variables[varCount].value) != 1){ // check if the input is a float
						printf("Error: invalid input\n"); // print an error message
						printf("Enter a value for %s: ", root->data); // prompt the user to enter a value for the variable
						while(getchar() != '\n'); // clear the input buffer
					}

					strncpy(variables[varCount].varName, root->data, sizeof(variables[varCount].varName) - 1); // store the variable name in the variables array
					variables[varCount].varName[sizeof(variables[varCount].varName) - 1] = '\0';
					varCount++; // increment the variable count
				}
				else{
					printf("Error: too many variables\n"); // print an error message
					exit(1); // exit the program
				}
			}
		}
		promptVariables(root->left); // recursively prompt the left node
		promptVariables(root->right); // recursively prompt the right node
	}
}

// The calculate function calculates the expression and returns its result. Division by 0 and/or other error scenarios should be checked.
float calculate(Node *root){
	if(root == NULL){
		return 0; // return 0 if the root is null
	}

	if(isalpha(root->data[0]) && root->data[0] == 'x'){ // check if the data is a letter
		for(int i = 0; i < varCount; i++){ // loop through the variables array
			if(strcmp(variables[i].varName, root->data) == 0){ // check if the variable is in the variables array
				return variables[i].value; // return the value of the variable
			}
		}
		return 0; // return 0 if the variable is not in the variables array
	}

	// check if the data is a digit
	if(isdigit(root->data[0] || root->data[0] == '.')){
		return atof(root->data); // return the value of the data
	}

	// recursively calculate the left and right nodes
	float left = calculate(root->left);
	float right = calculate(root->right);

	// check if the operator is addition
	if(strcmp(root->data, "+") == 0){
		return left + right; // return the sum of the left and right nodes
	}
	// check if the operator is subtraction
	else if(strcmp(root->data, "-") == 0){
		return left - right; // return the difference of the left and right nodes
	}
	// check if the operator is multiplication
	else if(strcmp(root->data, "*") == 0){
		return left * right; // return the product of the left and right nodes
	}
	// check if the operator is division
	else if(strcmp(root->data, "/") == 0){
		if(right != 0){ // check if the right node is 0
			return left / right; // return the quotient of the left and right nodes
		}
		else{
			printf("Error: division by zero\n"); // print an error message
			exit(1); // exit the program
		}	
		
	}

	printf("Error: invalid operator\n"); // print an error message
	exit(1); // exit the program
}