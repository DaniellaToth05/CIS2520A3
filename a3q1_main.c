#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"


// The main function drives the menu selection loop.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please use following input form: %s 'expression'\n", argv[0]);
        return 1;
    }

    char expr[100];
    int j = 0;

    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (argv[1][i] != '\\') { 
            expr[j++] = argv[1][i];
        }
    }
    expr[j] = '\0';

    Node *root = parseExpression(expr);
    
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Preorder\n");
        printf("2. Inorder\n");
        printf("3. Postorder\n");
        printf("4. Calculate\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf("\nPreorder: \n");
                preorder(root); 
                printf("\n"); 
                break;
            case 2: 
                printf("\nInorder: \n");
                inorder(root); 
                printf("\n"); 
                break;
            case 3: 
                printf("\nPostorder: \n");
                postorder(root); 
                printf("\n"); 
                break;
            case 4: 
                getchar(); 
                varCount = 0; // resetting for each loop
                promptVariables(root);
                printf("\nResult: %.2f\n", calculate(root));
                break;
            case 5: break;
            default: printf("Please enter a valid choice.\n");
        }
    } while (choice != 5);

    while(root != NULL) {
        Node *temp = root; // store the current node in a temporary variable

        if (root->left != NULL) {
            root = root->left; // move to the left node
        } 
        else if (root->right != NULL) {
            root = root->right; // move to the right node
        } 
        else {
            root = NULL; // set the root to null
        }
        free(temp); // free the memory of the current node
    }


    return 0;
}
