#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// note: check for memory leaks using, e.g.:
// valgrind --leak-check=full ./bankers safe.txt

// global variables
int NRES;  // number of resource types
int NPROC; // number of processes

int main(int argc, char *argv[])
{

  // print error message if the file is not given on command line
  if (argv[1] == NULL)
  {
    printf("Error: file is not given on the command line\n");
    printf("Usage: ./bankers <scenario file>\n");
    return 0;
  }

  // Attempt to open scenario file and scan data into allocated structures
  // set mode to 'r', so we can read from file
  FILE *fp = fopen(argv[1], "r");

  // print error message if file not found
  if (fp == NULL)
  {
    printf("Error: file not found\n");
    return 0;
  }

  // get number of resources and number of processes from file
  fscanf(fp, "%d", &NRES);
  fscanf(fp, "%d", &NPROC);

  printf("Num of resources: %d\n", NRES);
  printf("Num of processes: %d\n\n", NPROC);

  // get space for total resource vector
  int *resVector = (int *)malloc(sizeof(int) * NRES);

  // fill resource vector from file
  for (int i = 0; i < NRES; i++)
  {
    fscanf(fp, "%d", &resVector[i]);
  }
  printVector(resVector);

  // get space for max demand/need matrix
  int **maxMatrix = (int **)malloc(sizeof(int *) * NPROC);
  for (int i = 0; i < NPROC; i++)
  {
    maxMatrix[i] = (int *)malloc(sizeof(int) * NRES);
  }

  // populate max demand matrix from file
  for (int i = 0; i < NPROC; i++)
  {
    for (int j = 0; j < NRES; j++)
    {
      fscanf(fp, "%d", &maxMatrix[i][j]);
    }
  }
  // print max demand matrix
  printf("Max demand matrix:\n");
  printMatrix(maxMatrix);

  // get space for allocation matrix
  int **allocMatrix = (int **)malloc(sizeof(int *) * NPROC);
  for (int i = 0; i < NPROC; i++)
  {
    allocMatrix[i] = (int *)malloc(sizeof(int) * NRES);
  }

  // populate allocation matrix from file
  for (int i = 0; i < NPROC; i++)
  {
    for (int j = 0; j < NRES; j++)
    {
      fscanf(fp, "%d", &allocMatrix[i][j]);
    }
  }
  // print allocation matrix
  printf("Allocation matrix:\n");
  printMatrix(allocMatrix);

  // sanity check

  // sanity check 1
  // make sure currently allocated resources do not exceed the total number of resources
  int sum = 0;
  for (int i = 0; i < NRES; i++)
  {
    for (int j = 0; j < NPROC; j++)
    {
      sum += allocMatrix[j][i];
      // printf("allocMatrix: %d\n", allocMatrix[j][i]);
    }
    // printf("Sum for %d: %d\n", i, sum);
    // printf("Resvec for %d: %d\n", i, resVector[i]);
    if (sum > resVector[i])
    {
      printf("Integrity test failed: allocated resources exceed total resources\n");
      break;
    }
    sum = 0;
  }

  // sanity check 2.
  // make sure each thread’s needs do not exceed its max demands for each resource type

  int **sanity2 = subMatrix(maxMatrix, allocMatrix);
  for (int i = 0; i < NPROC; i++)
  {
    for (int j = 0; j < NRES; j++)
    {
      if (sanity2[i][j] < 0)
      {
        printf("Integrity test failed: allocated resources exceed demand for Thread %d\n", i);
        printf("Need %d instances of resource %d\n", sanity2[i][j], j);
        break;
      }
    }
  }

  // Compute the availability vector (PMR)
  // Get the availability resource vector
  int totAllocVector[NRES];
  sumRows(allocMatrix, totAllocVector);
  // resVector is the total resource vector
  int *availVector;
  availVector = (int *)malloc(sizeof(int) * NRES);
  subtractvecs(resVector, totAllocVector, availVector);
  // Get the need matrix, which is maximum demand - current allocation
  int **needMatrix = (int **)malloc(sizeof(int *) * NPROC);
  for (int i = 0; i < NPROC; i++)
    needMatrix[i] = (int *)malloc(sizeof(int) * NRES);
  subtractmats(maxMatrix, allocMatrix, needMatrix);

  // TODO: Run banker's safety algorithm with different orderings
  // the following has just one ordering (PMR)
  isSafe(availVector, allocMatrix, needMatrix);

  // close file
  fclose(fp);

  // free matrices

  free(resVector);
  resVector = NULL;
  free(availVector);
  availVector = NULL;

  for (int i = 0; i < NPROC; i++)
  {
    free(maxMatrix[i]);
    maxMatrix[i] = NULL;

    free(allocMatrix[i]);
    allocMatrix[i] = NULL;

    free(sanity2[i]);
    sanity2[i] = NULL;

    free(needMatrix[i]);
    needMatrix[i] = NULL;
  }
  free(maxMatrix);
  maxMatrix = NULL;
  free(allocMatrix);
  allocMatrix = NULL;
  free(sanity2);
  sanity2 = NULL;
  free(needMatrix);
  needMatrix = NULL;

  return 0;
}