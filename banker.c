#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "banker.h"

/**
 * Determine if threads can safely be run without the possibility of a deadlock
 * @param availVec
 */
int isSafe(int *availVec, int **allocMat, int **needMat)
{

    // Need to keep track of the order the threads run in in the simulation
    int threadorder[NPROC];

    // Initialization of work vector for resources and finish vector for processes
    // The work vec holds the number of currently available resources,
    // which increases every time a thread finishes and its resources are freed up
    // Note: this is not mallocd so it does not need to be freed
    // But it could be mallocd here and then freed before returning
    int workVec[NRES];
    clonevec(availVec, workVec);
    int finishVec[NPROC];
    for (int i = 0; i < NPROC; i++)
        finishVec[i] = 0;

    // Simulation: See if all threads can finish
    int unfinished = 1;
    int notstuck = 1;
    int count = 0;
    int iorder = 0;
    while (unfinished & notstuck)
    {
        count += 1;
        unfinished = 0; // Set to finished until we find a thread we *need* to do
        notstuck = 0;   // Set to stuck until we find a thread we *can* do
        // We are trying the threads sequentially, from zero. We also need to try
        // different orderings. This will require resetting workVec etc.
        for (int row = 0; row < NPROC; row++)
        {
            // Can we run this thread?
            if ((finishVec[row] == 0) & (vec1GreaterOrEqualVec2(workVec, needMat[row])))
            {
                // pretend that thread i finishes execution
                // then OS can reclaim thread i's allocated resources
                // workVec += allocMat[row];
                addVec2toVec1(workVec, allocMat[row]);
                finishVec[row] = 1;
                notstuck = 1; // We are not stuck because we just freed resources

                // Create the ordering for this string
                threadorder[iorder] = row;
                iorder++;
            }
            else if (finishVec[row] == 0)
                unfinished = 1; // We are not finished, but we may be stuck
        }
        if (count >= 100)
        {
            printf("too many tries, giving up!\n");
            return 0;
        }
    }

    if ((unfinished) & (notstuck))
        printf("Unfinished and not stuck\n");
    else if ((unfinished) & (notstuck == 0))
        printf("Unfinished and stuck\n");
    else if ((unfinished == 0) & (notstuck))
        printf("Finished and not stuck!\n");
    else if ((unfinished == 0) & (notstuck == 0))
        printf("Stuck but who cares, we finished!\n");
    else
        printf("How did this happen?");

    // As soon as we find one that did not finish, we can return 0 for unsave
    if (unfinished)
    {
        printf("Unsafe: ");
        for (int i = 0; i < NPROC; i++)
        {
            if (finishVec[i] == 0)
                printf("T%d ", i);
        }
        printf("cannot finish\n");
        return 0;
    }

    printf("Safe: ");
    for (int i = 0; i < NPROC; i++)
        if (finishVec[i] == 0)
        {
            printf("\nError: T%d not safe!", i);
            return 0;
        }
        else
            printf("T%d ", threadorder[i]);
    printf("\n");

    // If they all finished, we can return 1 for safe
    return 1;
}
