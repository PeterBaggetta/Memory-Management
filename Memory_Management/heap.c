/* Assignment 3
 * Pietro Baggetta
 * 1092160
 * Citation for Heap Code:
    * Lecture Code
    * Textbook Code
    * GeeksForGeeks.com
*/

#include "myHeader.h"

/* Find the parent node */
int parentIndex (int index) {
    return (index - 1) / 2;
}

/* Finds the left most node in the tree */
int leftIndex (int index) {
    return index * 2 + 1;
}

/* Finds the right most node in the tree */
int rightIndex (int index) {
    return index * 2 + 2;
}

void insertToHeap (Process *p, Process **heap, int *heapCounter) {

    heap[*heapCounter] = p;
    *heapCounter = *heapCounter + 1;
    int index = *heapCounter - 1;

    /* Insert to the heap in order of queue (smallest to largest) */
    while ((index > 0) && (heap[parentIndex (index)] -> queue >= heap[index] -> queue)) {
        Process *temp = heap[parentIndex (index)];
        heap[parentIndex (index)] = heap[index];
        heap[index] = temp;
        index = parentIndex (index);
    }
}

/* Orders the heap so the smallest queue number is at the root */
void heapify (Process **heap, int *heapCounter, int index) {

    if (*heapCounter == 1) {
        return;
    }

    int left = leftIndex (index);
    int right = rightIndex (index);
    int smallest = index;

    if ((left < *heapCounter) && (heap[left] -> queue < heap[index] -> queue)) {
        smallest = left;
    }

    if ((right < *heapCounter) && heap[right] -> queue < heap[index] -> queue) {
        smallest = right;
    }

    /* Swap root if a smaller queue number is found */
    if (smallest != index) {
        Process *temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        heapify (heap, heapCounter, smallest);
    }
}

/* Removes the root */
void removeRoot (Process **heap, int *heapCounter) {

    if (*heapCounter == 0) {
        return;
    }

    /* Temp variable to swap correctly */
    Process *temp = heap[*heapCounter - 1];
    heap[0] = temp;

    *heapCounter = *heapCounter - 1;

    heapify (heap, heapCounter, 0);
}
