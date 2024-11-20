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
        printf("\nError, node could not be created with empty or null data.\n");
        return NULL;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node)); // allocate memory for the new node

	// check if memory allocation failed
    if (newNode == NULL) {
        printf("\nError, memory allocation failed for node.\n");
        exit(1);
    }
    
    char *copy = (char*)malloc(strlen(data) + 1); // allocate memory for the data

	// check if memory allocation failed
    if (copy == NULL) {
        printf("\nError, memory allocation failed for node data.\n");
        free(newNode); // free the memory allocated for the node
        exit(1);
    }
    
    strcpy(copy, data); // copy the data to the new memory location	

    
    newNode->left = NULL; // set the left child to NULL
    newNode->right = NULL; // set the right child to NULL
    
	strcpy(newNode->data, copy); // copy the data to the node

    free(copy); // free the memory allocated for the data

    //printf("Node created with data: %s\n", newNode->data); 

    return newNode; // return the new node
}


// The parseExpression function parses the expression string passed in from command line, stores the information in a new node, and returns the root node of the tree.
/* 	references used for this function:
		* https://www.geeksforgeeks.org/expression-tree/
		* https://craftinginterpreters.com/parsing-expressions.html  
		* https://stackoverflow.com/questions/11703082/parsing-math-expression-in-c 
*/
Node* parseExpression(char *expr) {

	Node *newNode; // create a new node

	// check if the expression is empty
    if (expr == NULL || strlen(expr) == 0) {
        return NULL;
    }


    int parenthesesCount = 0; // count the number of parentheses
    int operatorPosition = -1; // position of the operator
    int length = strlen(expr); // length of the expression

    
	// check if the expression is enclosed in parentheses
    if (expr[0] == '(' && expr[length - 1] == ')') {
        int valid = 1; // variable to check if the expression is valid

		// check if the parentheses are balanced
        for (int i = 1; i < length - 1; i++) {
            if (expr[i] == '(') { // if the character is an opening parenthesis
                parenthesesCount++; // increment the count of parentheses
            } 
			else if (expr[i] == ')') { // if the character is a closing parenthesis
                parenthesesCount--; // decrement the count of parentheses
            }
			// if the count of parentheses is less than 0
            if (parenthesesCount < 0) {
                valid = 0; // set valid to 0
                break;
            }
        }
		// if the expression is valid and the count of parentheses is 0
        if (valid && parenthesesCount == 0) {
            
			// remove the parentheses by shifting the characters to the left
            for (int i = 0; i < length - 2; i++) {
                expr[i] = expr[i + 1]; // shift 
            }
			// set the last character to null
            expr[length - 2] = '\0';
            length -= 2; // decrement the length
        }
    }


    parenthesesCount = 0; // reset the count of parentheses
	// loop through the expression from right to left
    for (int i = length - 1; i >= 0; i--) { 
        if (expr[i] == ')') { // if the character is a closing parenthesis
            parenthesesCount++; // increment the count of parentheses
        } 
		else if (expr[i] == '(') { // if the character is an opening parenthesis
            parenthesesCount--; // decrement the count of parentheses
        } 
		else if (parenthesesCount == 0) { // if the count of parentheses is 0
			// check if the character is a plus or minus operator
            if (expr[i] == '+' || expr[i] == '-') {
                operatorPosition = i; // set the operator position
                break; 
            } 
			// otherwise if the character is a multiplication or division operator
			else if ((expr[i] == '*' || expr[i] == '/') && operatorPosition == -1) {
                operatorPosition = i; // set the operator position
            }
        }
    }

	// check if an operator was found
	if (operatorPosition != -1) { 

		newNode = (Node *)malloc(sizeof(Node)); // allocate memory for the new node

		// check if memory allocation failed
		if (newNode == NULL) {
			printf("Error, memory allocation failed.\n");
			exit(1);
		}

		newNode->data[0] = expr[operatorPosition]; // set the data of the node to the operator
		newNode->data[1] = '\0';  // set the null terminator

		expr[operatorPosition] = '\0';	// set the operator to null
		
		newNode->left = parseExpression(expr); // parse the left expression
		newNode->right = parseExpression(expr + operatorPosition + 1); // parse the right expression 
	} 
	
	// if no operator was found
	else { 
		newNode = (Node *)malloc(sizeof(Node)); // allocate memory for the new node
		
		// check if memory allocation failed
		if (newNode == NULL) {
			printf("Error, memory allocation failed.\n"); 
			exit(1);
		}
		
		strncpy(newNode->data, expr, sizeof(newNode->data) - 1); // copy the expression to the data of the node
		newNode->data[sizeof(newNode->data) - 1] = '\0'; // set the null terminator

		
		newNode->left = NULL; // set the left child to null
		newNode->right = NULL; // set the right child to null
	} 

	
	return newNode; // return 
}


// The preOrder function prints tree nodes in preorder traversal.
void preorder(Node *root){

	// if the root is not null
	if(root == NULL){
		return; // return if the root is null
		
	}
	else {
		printf("%s ", root->data); // print the data of the node
		preorder(root->left); // recursively print the left node
		preorder(root->right); // recursively print the right node
	}
}


// The inOrder function prints tree nodes in inorder traversal fully parenthesized.
void inorder(Node *root){
	// if the root is not null
	if(root != NULL){
		
		printf("("); // print the opening parenthesis
		
		inorder(root->left); // recursively print the left node
		printf("%s", root->data); // print the data of the node
		inorder(root->right); // recursively print the right node
		
		printf(")"); // print the closing parenthesis
		
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
 	
	// check if the root is null
	if (root == NULL) {
        return; 
    }

    // check if the node contains a variable
    if (isalpha(root->data[0])) {
        for (int i = 0; i < varCount; i++) {
            if (strcmp(variables[i].varName, root->data) == 0) { // check if the variable is already in the array
                return; 
            }
        }

		// if the count of variables is greater than or equal to 10
        if (varCount >= 10) {
            printf("Error, there are too many variables.\n"); // print an error message
            return;
        }

        // ask the user for the value of the variable
        printf("Please enter a value for %s: ", root->data);

		// check if the input is valid
        while (scanf("%f", &variables[varCount].value) != 1) {
            printf("Invalid input, please enter a valid value for %s: ", root->data);
            while (getchar() != '\n');  
        }

        // add the variable to the array
        strcpy(variables[varCount].varName, root->data);
        varCount++; // increment the variable count
    }

    promptVariables(root->left); // recursively prompt the left node
    promptVariables(root->right); // recursively prompt the right node
}


// // The calculate function calculates the expression and returns its result. Division by 0 and/or other error scenarios should be checked.
float calculate(Node *root){
	float sum;
	float difference;
	float product;
	float division;
	float num;

	// check if the root is null
    if (root == NULL) {
        return 0.0; 
    }

    // check if the root is a leaf node
    if (root->left == NULL && root->right == NULL) {

		// check if data is a variable
        if (isalpha(root->data[0])) { 
            
			// loop through the variables array
            for (int i = 0; i < varCount; i++) {

				// check if the variable is in the variables array
                if (strcmp(variables[i].varName, root->data) == 0) {
					// return the value of the variable
                    return variables[i].value; 
                }
            }
			printf("Error, the variable '%s' could not be found.\n", root->data); // print an error message
			return 0.0; // return 0
        } 
		else if (isdigit(root->data[0]) || root->data[0] == '.') { // check if data is a number
            num = atof(root->data); // convert the data to a float
			return num; // return the number
        } 
		else {
            printf("Error, invalid data '%s'.\n", root->data); // print an error message
            return 0.0; // return 0
        }
    }

    
    float leftValue = calculate(root->left); // calculate the left value
    float rightValue = calculate(root->right); // calculate the right value

    // check if the operator is addition, subtraction, multiplication, or division
	// if operation is addition
    if (strcmp(root->data, "+") == 0) {
		sum = leftValue + rightValue; // calculate the sum
        return sum; // return the sum
    } 
	// if operation is subtraction
	else if (strcmp(root->data, "-") == 0) {
        difference = leftValue - rightValue; // calculate the difference
		return difference; // return the difference
    } 
	// if operation is multiplication
	else if (strcmp(root->data, "*") == 0) {
        product = leftValue * rightValue; // calculate the product
		return product; // return the product
    } 
	// if operation is division
	else if (strcmp(root->data, "/") == 0) {
        // check if the right value is 0
		if (rightValue == 0.0) { 
            printf("Error, cannot divide by zero.\n"); // print an error message
            return 0.0;
        }
		division = leftValue / rightValue; // calculate the division
        return division; // return the division
    } 
	else { // if the operator is not valid
        printf("Error, found an unknown operator '%s'.\n", root->data); // print an error message
        return 0.0;
    }
}

