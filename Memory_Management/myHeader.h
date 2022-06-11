#ifndef _MYHEADER_H
#define _MYHEADER_H

/* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Struct for processes */
typedef struct {
    int processID;
    int memSize;
    int inMemCounter;
    int queue;
} Process;

int ordered;

/* Function declarations */
/* Helper File */
void breakInput (char data[100][100], int lineCount, Process **heap, int *heapCounter);
int getNumHoles (int mem[1024]);
int getPerMemUsage (int mem[1024]);
void printHeap(Process **heap, int *heapCounter);

/* Heap File */
int parentIndex (int index);
int leftIndex (int index);
int rightIndex (int index);
void insertToHeap (Process *p, Process **heap, int *heapCounter);
void heapify (Process **heap, int *heapCounter, int index);
void removeRoot (Process **heap, int *heapCounter);

#endif
