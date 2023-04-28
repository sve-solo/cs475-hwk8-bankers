#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "banker.h"

/**
 * Determine if threads can safely be run without the possibility of a deadlock
 * @param workVec matrix of what resources are avaliable to threads
 * @param finishVec vector that shows if threads can finisb
 * @param allocMat matrix of resources allocated to threads
 * @param needMat matrix of what resources threads need to finish
 * @param sequence vector that holds the sequences to print
 * @param recurse int used for recursion
 */
int safeCheck(int* workVec, int* finishVec, int** allocMat, int** needMat, int* sequence, int recurse){
    int safe = 0;
    int printUnsafe = 1;
    
    //base case
    if(recurse == NPROC){
        //print safe schedules
        printf("SAFE: ");
        for(int i = 0; i < NPROC; i++){
            printf("%d ", sequence[i]);
        }
        printf("\n");
        //printVector(sequence, NPROC);
        return 1;
    }

    //simulates if threads can finish
    //printf("Before: ");
    //printVector(workVec, NRES);
    for (int row = 0; row < NPROC; row++){
        // Can we run this thread?
        if ((finishVec[row] == 0) && (compareVector(workVec, needMat[row]))){//(vec1GreaterOrEqualVec2(workVec, needMat[row]))){
            // pretend that thread i finishes execution
            // then OS can reclaim thread i's allocated resources
            // workVec += allocMat[row];
            finishVec[row] = 1;
            addVec2toVec1(workVec, allocMat[row]);
            //printf("After, row %d: ", row);
            //printVector(workVec, NRES);
            

            //update safe sequence
            sequence[recurse] = row;
            //printVector(sequence, NPROC);

            //recursion
            safe = safeCheck(workVec, finishVec, allocMat, needMat, sequence, recurse + 1);

            //reverse for recursion
            printUnsafe = 0;
            finishVec[row] = 0;
            subVector(workVec, allocMat[row]);
            //printf("After subtracting, row %d: ", row);
            //printVector(workVec, NRES);
        }
    }

    //if the checker fails
    if(printUnsafe == 1){
        //printVector(finishVec, NPROC);
        printf("UNSAFE: ");
        for (int i = 0; i < NPROC; i++)
        {
            if (finishVec[i] == 0)
                printf("T%d ", i);
        }
        printf("cannot finish\n");

    }

    return safe;
}


/**
 * Determine if threads can safely be run without the possibility of a deadlock
 * @param availVec matrix of what resources are avaliable to threads
 * @param allocMat matrix of resources allocated to threads
 * @param needMat matrix of what resources threads need to finish
 */
int isSafe(int *availVec, int **allocMat, int **needMat){

    // Need to keep track of the order the threads run in in the simulation
    //int threadorder[NPROC];

    // Initialization of work vector for resources and finish vector for processes
    // The work vec holds the number of currently available resources,
    // which increases every time a thread finishes and its resources are freed up
    // Note: this is not mallocd so it does not need to be freed
    // But it could be mallocd here and then freed before returning
    //int workVec[NRES];
    int* workVec = copyVector(availVec);
    //printVector(workVec, NRES);
    int* finishVec = (int*) malloc(NPROC * sizeof(int));
    for (int i = 0; i < NPROC; i++){
        finishVec[i] = 0;
    }
    //printVector(finishVec, NPROC);

    //fill sequence with -1s, before it has actual values
    int* sequence = (int*) malloc(NPROC * sizeof(int));
    for (int i = 0; i < NPROC; i++){
        sequence[i] = -1;
    }
    //printVector(sequence, NPROC);
    
    //call safeCheck to print the schedules
    int recurse = 0;
    safeCheck(workVec, finishVec, allocMat, needMat, sequence, recurse);
    
    //free vectors
    free(workVec);
    workVec = NULL;
    free(finishVec);
    finishVec = NULL;

    free(sequence);
    sequence = NULL;
    
    return 0;

}


