#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

//global variables
int NRES; //number of resource types
int NPROC; //number of processes

int main(int argc, char *argv[])
{
  // TODO: attempt to open scenario file and scan data into allocated structures

  //print error message if the file is not given on command line
  if(argv[1] == NULL){
    printf("Error: file is not given on the command line\n");
    return 0;
  }

  //make a file
  //set mode to 'r', so we can read from file
  FILE *fp = fopen(argv[1], "r");

  //print error message if file not found
  if(fp == NULL){
    printf("Error: file not found\n");
    return 0;
  }

  //get number of resources and number of processes from file
  fscanf(fp, "%d", &NRES);
  fscanf(fp, "%d", &NPROC);

  printf("Num of resources: %d\n", NRES);
  printf("Num of processes: %d\n", NPROC);

  //get space for total resource vector
  int* resVector = (int*) malloc(sizeof(int) * NRES);
  
  //fill resource vector from file
  for(int i = 0; i < NRES; i++){
    fscanf(fp, "%d", &resVector[i]);
    printf("Resource %d: %d\n", i, resVector[i]);
  }
  printf("\n");

  //get space for max demand/need matrix
  int** maxMatrix = (int**) malloc(sizeof(int*) * NPROC);
	for(int i = 0; i < NPROC; i++){
    maxMatrix[i] = (int*) malloc(sizeof(int) * NRES);
  }

  //populate max demand matrix from file
	for(int i = 0; i < NPROC; i++){
		for(int j = 0; j < NRES; j++){
			fscanf(fp, "%d", &maxMatrix[i][j]);
		}
	}
  //print max demand matrix
  printMaxtrix(maxMatrix);

  //get space for allocation matrix
  int** allocMatrix = (int**) malloc(sizeof(int*) * NPROC);
	for(int i = 0; i < NPROC; i++){
    allocMatrix[i] = (int*) malloc(sizeof(int) * NRES);
  }

  //populate allocation matrix from file
	for(int i = 0; i < NPROC; i++){
		for(int j = 0; j < NRES; j++){
			fscanf(fp, "%d", &allocMatrix[i][j]);
		}
	}
  //print allocation matrix
  printMaxtrix(allocMatrix);


  // TODO: Run banker's safety algorithm

  //close file
  fclose(fp);

  //free matrices

  free(resVector);
  resVector = NULL;

  for(int i = 0; i < NPROC; i++){
    	free(maxMatrix[i]);
    	maxMatrix[i] = NULL;

      free(allocMatrix[i]);
      allocMatrix[i] = NULL;
  }
  free(maxMatrix);
  maxMatrix = NULL;
  free(allocMatrix);
  allocMatrix = NULL;

  return 0;
}