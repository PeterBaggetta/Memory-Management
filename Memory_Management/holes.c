/* Assignment 3
 * Pietro Baggetta
 * 1092160
*/

#include "myHeader.h"

int main (int argc, char *argv[]) {

    /* Not enough command arguments entered */
    if (argc != 3) {
        printf ("****************************************************\n");
        printf ("            Invalid command line                    \n");
        printf (" Format: ./holes <testfile> <first|best|worst|next> \n");
        printf ("****************************************************\n");
        exit (0);
    }

    char *fileName = argv[1];
    int type;   /* Stores type of allocation method from user */

    if (!strcmp (argv[2], "first")) {
        printf ("***** First Fit *****\n");
        type = 0;
        
    } else if (!strcmp (argv[2], "best")) {
        printf ("***** Best Fit *****\n");
        type = 1;
        
    } else if (!strcmp (argv[2], "next")) {
        printf ("***** Next Fit *****\n");
        type = 2;

    } else if (!strcmp (argv[2], "worst")) {
        printf ("***** Worst Fit *****\n");
        type = 3;
        
    } else {
        printf ("*************************************************\n");
        printf ("      Invalid type of allocation strategy        \n");
        printf ("    Viable options: first, best, next, worst     \n");
        printf ("*************************************************\n");
        exit (0);
    }

    FILE *file = fopen (fileName, "r");
    char data[100][100];
    int lineCount = 0;

    /* Read in file to array to later be put into a heap */
    while (fgets (data[lineCount], sizeof (data), file)) {
        int len = strlen (data[lineCount]);

        if (data[lineCount][len - 1] == '\n') {
            data[lineCount][len - 1] = '\0';
        }
        lineCount++;
    }
    fclose (file);

    /* Create main heap */
    Process **heap = malloc (sizeof (Process *) * 1024);
    int heapCounter = 0;
    ordered = 0;

    breakInput (data, lineCount, heap, &heapCounter);
    /* printHeap (heap, &heapCounter); */

    int *mem = malloc (sizeof (int) * 1024);
    for (int i = 0; i < 1024; i++) {
        mem[i] = -1;
    }

    /* Keep track of memory use with an array of size 1024 */
    Process **memQ = malloc (sizeof (Process *) * 1024);
    int memCounter = 0, pidLoaded = 0, lastIn = 0;
    float numProcesses = 0.0, numHoles = 0.0, cumMemUsage = 0.0;

    while (heapCounter > 0) {
        Process * currProcess = heap[0];
        bool canFit = false;
        int holes[1024][3], holeNum = 0, holeIndex = 0;

        /* Check all locations of holes */
        for (int i = 0; i < 1024; i++) {
            if (mem[i] == -1) {
                /* Found hole */
                int startIndex = i;
                int currIndex = i;

                /* Get size of hole and store it into holes array */
                while ((currIndex < 1024) && (mem[currIndex] == -1)) {
                    currIndex++;
                }
                int endIndex = currIndex - 1;

                holes[holeNum][0] = startIndex;
                holes[holeNum][1] = endIndex;
                holes[holeNum][2] = endIndex - startIndex + 1;
                holeNum++;
                i = currIndex;
            }
        }

        if (type == 0) {
            /* First Fit Algorithm (Finds the first hole that fits the process size) */
            for (int i = 0; i < holeNum; i++) {
                if (holes[i][2] >= currProcess -> memSize) {
                    holeIndex = i;
                    canFit = true;
                    break;
                } else {
                    canFit = false;
                }
            }
        } else if (type == 1) {
            /* Best Fit Algorithm (Find the hole closest to the process size) */
            int difference = 1024;
            canFit = false;
            for (int i = 0; i < holeNum; i++) {
                /* Check if hole is bigger than size of process (can fit) */
                if (holes[i][2] >= currProcess -> memSize) {
                    if ((holes[i][2] - currProcess -> memSize) <= difference) {
                        difference = holes[i][2] - currProcess -> memSize;
                        holeIndex = i;
                        canFit = true;
                    }
                }
            }
        } else if (type == 2) {
            /* Next Fit Algorithm (Finds where last process was inserted, then finds the next hole after that time) */
            canFit = 0;
            for (int i = 0; i < holeNum; i++) {
                if (memCounter == 0) {
                    lastIn = 0;
                }

                /*  */
                if ((holes[i][2] >= currProcess -> memSize) && (holes[i][0] >= lastIn)) {
                    holeIndex = i;
                    canFit = true;
                    break;
                } else if ((holes[i][2] >= currProcess -> memSize) && (holes[i][0] >= 0)) {
                    holeIndex = i;
                    canFit = true;
                    break;
                }
            }
        } else if (type == 3) {
            /* Worst Fit Algorithm (Finds the biggest hole and inserts process) */
            int biggest = 0;
            canFit = false;
            for (int i = 0; i < holeNum; i++) {
                if (holes[i][2] >= currProcess -> memSize) {
                    if (holes[i][2] >= biggest) {
                        holeIndex = i;
                        canFit = true;
                        biggest = holes[i][2];
                    }
                }
            }
        }

        if (canFit) {
            /* Increase counter for how many time the process has been in memory */
            currProcess -> inMemCounter = currProcess -> inMemCounter + 1;

            if (currProcess -> inMemCounter <= 3) {
                int start = holes[holeIndex][0];

                /* Assign block in memory to a process */
                for (int i = 0; i < currProcess -> memSize; i++) {
                    mem[start] = currProcess -> processID;
                    start++;
                }

                /* Keep track for next algorithm */
                lastIn = start;

                ordered += 1;
                currProcess -> queue = ordered;

                /* Put process into "memory" */
                insertToHeap (currProcess, memQ, &memCounter);

                pidLoaded += 1;
                numProcesses += memCounter;
                numHoles += getNumHoles (mem);

                float perMemUsage = ((getPerMemUsage (mem) / 1024.0f) * 100);
                cumMemUsage += perMemUsage;

                printf ("pid loaded, #processes = %d, #holes = %.0d, %%memusage = %.0f, cumulative %%mem = %.0f\n", memCounter, getNumHoles (mem), perMemUsage, (cumMemUsage / pidLoaded));
            }

            removeRoot (heap, &heapCounter);
        
        } else {
            /* Process size cannot fit into memory so take out oldest */
            Process *old = memQ[0];

            for (int i = 0; i < 1024; i++) {
                if (mem[i] == old -> processID) {
                    mem[i] = -1;
                }
            }

            removeRoot (memQ, &memCounter);
            ordered += 1;
            old -> queue = ordered;
            insertToHeap (old, heap, &heapCounter);
        }
    }

    printf ("Total loads = %d, average #processes = %.1f, average #holes = %.1f, cumulative %%mem = %0.f\n", pidLoaded, (numProcesses / pidLoaded), (numHoles / pidLoaded), (cumMemUsage / pidLoaded));

    free (heap);
    free (mem);
    free (memQ);

    return 0;
}
