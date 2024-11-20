# CIS2520-F24-A2

## Student Information 
Name : Daniella Toth

Student Number : 1261398

## Assignment Overview
What is the assignment about?  

Explain the purpose of the program and what it accomplishes.
    
    This assignment involves implementing two programs to practice using data structures in C. The first program focuses on creating a Binary Expression Tree 
    that is supposed to parses a fully parenthesized arithmetic expression provided using the command line (e.g., ./a3q1 '(((x1+5.12)*(x2-7.68))/x3)' ). It builds a tree to represent 
    the expression, supports Preorder, Inorder, and Postorder traversals, and allows users to assign values to variables and evaluate the expression.

    The second program involves implementing a Max-Heap. It reads 200 integers from a text file named f.dat, stores them in a 20x10 2D array, and treats each 
    row as an object with a key and information content. It then builds a max-heap using a downheap algorithm.

## Resources 
Did you use any resources (for example book, notes etc) in this assignment?
    
    Resources I used for Question 1 include :

      https://courselink.uoguelph.ca/d2l/le/content/911255/viewContent/3962993/View 
      Slides 20-28 on traversals of the "Tree" lecture slides for understanding the 3 traversals: 

      https://www.geeksforgeeks.org/expression-tree/

      https://craftinginterpreters.com/parsing-expressions.html  

      https://stackoverflow.com/questions/11703082/parsing-math-expression-in-c, 
              -> specifically I used the C++ implementation submitted by user 'BLUEPIXY' as a reference
                 for my parseExpression function in order in order to better understand how to handle 
                 operator precedence and parentheses correctly while recursively constructing the binary 
                 expression tree, as I had a lot of trouble trying to complete this function. This has also 
                 been cited above the respective function in my a3q1_functions.c file.


    Resources I used for Question 2 include:

      https://courselink.uoguelph.ca/d2l/le/content/911255/viewContent/3969793/View 
      Slides 22 and 23 of the "Heap" lecture slides for pseudocode to complete the down heap function
     
## Implementation
Is the assignment complete? If not, mention what part of the assignment is missing or incomplete.
- Yes the assignment is completed

