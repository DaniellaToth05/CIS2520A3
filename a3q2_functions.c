#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "a3q2_header.h"

/*
 * The downHeap function performs the downheap algorithm.
 * The key at the passed position is swapped with the key of it's child with the smallest value.
 * If the key is smaller, than both of it's children's keys then no swap happens.
 * After swap, the downHeap is called again to the new position of the swapped key and it terminates when it's value is smaller than both children.
*/
void downHeap(int key[20], int pos, int array[20][10]){
    int child = 2 * pos + 1; // the left child of the passed position
    int value = key[pos]; // the value of the current node

    // while the left child is less than the size of the heap
    while(child < 20){
      int max = value; // the max value
      int maxPos = -1; // the position of the max value

      // find the max value of the current node and its children
      for(int i = 0; i < 2; i++){
        if(child + 1 < 20){
          if(key[child + i] > max){ // if the child is greater than the current node
            max = key[child + i]; // the max value
            maxPos = child + i; // the position of the max value
          }
        }
      }

      // if the current node is already the max value, then break
      if(maxPos == -1){
        return;
      }

      swap(pos, maxPos, key, array); // swap the current node with the max value node 

      pos = maxPos; // the new position of the key
      child = 2 * pos + 1; // the new left child of the key 
    }

}

// The isParent function returns true if the passed position has a child or false if there's no child
bool isParent(int keyPos){
  // if the left child is less than the size of the heap
  if (2 * keyPos + 1 < 20){
    return true; // return true
  }
  return false; // return false

}

// The swap function swaps 2 rows in the 2D array and the key array. It receives the position of the 2 rows to be swapped, the key array, and the 2D array in its arguements.
void swap(int key1Pos, int key2Pos, int key[20], int array[20][10]){
  int tempKey = key[key1Pos]; // the temporary key
  int tempArray[10]; // the temporary array

  // copy the first row to the temporary array
  for(int i = 0; i < 10; i++){
    tempArray[i] = array[key1Pos][i];
  }

  // copy the second row to the first row
  for(int i = 0; i < 10; i++){
    array[key1Pos][i] = array[key2Pos][i];
  }

  // copy the temporary array to the second row
  for(int i = 0; i < 10; i++){
    array[key2Pos][i] = tempArray[i];
  }

  // swap the keys
  key[key1Pos] = key[key2Pos];
  key[key2Pos] = tempKey;


}
