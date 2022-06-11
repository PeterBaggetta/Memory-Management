/* Assignment 3
 * Pietro Baggetta
 * 1092160
*/

#include "myHeader.h"

/* Takes the input file and stores it in the respective variable in the heap */
void breakInput (char data[100][100], int lineCount, Process **heap, int *heapCounter) {

    int i = 0;

    while (i < lineCount) {
        Process *p = malloc (sizeof (Process));

        /* Get the process ID */
        char *temp = strtok (data[i], " ");
        p -> processID = atoi (&data[i][0]);

        /* Get the memory chunk size */
        temp = strtok (NULL, " ");

        p -> memSize = atoi (temp);

        /* Set the number of time the process is in memory to zero */
        p -> inMemCounter = 0;

        /* Sorting for heap (sorts on the order processes enter) */
        ordered += 1;
        p -> queue = ordered;

        insertToHeap (p, heap, heapCounter);

        i++;
    }
    
}

/* Find the total number of holes in the memory */
int getNumHoles (int mem[1024]) {
    int holes = 0;

    for (int i = 0; i < 1024; i++) {
        /* If the index in memory array is -1, then there is a hole */
        if (mem[i] == -1) {
            int index = i;

            while ((index < 1024) && (mem[index] == -1)) {
                index++;
            }

            holes++;
            i = index;
        }
    }
    return holes;
}

/* Finds how much of the memory is being used at the moment */
int getPerMemUsage (int mem[1024]) {
    int usage = 0;

    for (int i = 0; i < 1024; i++) {
        /* If index in memory array is not -1, then a process occupies that space */
        if (mem[i] != -1) {
            usage++;
        }
    }
    return usage;
}

/* FOR TESTING PURPOSES */
void printHeap(Process **heap, int *heapCounter) {

    for (int i = 0; i < *heapCounter; i++) {
        printf("ID: %d  | SIZE: %d  | QUEUE: %d\n", heap[i] -> processID, heap[i] -> memSize, heap[i] -> queue);
    }
}
