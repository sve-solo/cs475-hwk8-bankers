#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// TODO - Define vector and matrix operations

/**
 * Adds two matrices together
 * @param matrixA pointer to a 2D array
 * @param matrixB pointer to a 2D array
 * @return pointer to the newly added matrix
 */
int** addMatrix(int** matrixA, int** matrixB){
	//allocate space for new matrix
	int** newMatrix = (int**) malloc(sizeof(int*) * NPROC);
	for(int i = 0; i < NPROC; i++){
    	newMatrix[i] = (int*) malloc(sizeof(int) * NRES);
  	}

    for(int i = 0; i < NPROC; i++){
		for(int j = 0; j < NRES; j++){
			newMatrix[i][j] = (matrixA[i][j] + matrixB[i][j]);
		}
	}

	return newMatrix; //don't forget to free in main if we use this method
}

/**
 * Adds two vectors together
 * @param vectorA pointer to first vector
 * @param vectorB pointer to second vector
 * @return pointer to the newly added vector
 */
int* addVector(int* vectorA, int* vectorB){
	//allocate space for new vector
	int* newVector = (int*) malloc(sizeof(int) * NRES);

	for(int i = 0; i < NRES; i++){
		newVector[i] = vectorA[i] + vectorB[i];
	}

	return newVector; //don't forget to free in main if we use this method
} 

/**
 * Compare two given vectors
 * @param vectorA pointer to first vector
 * @param vectorB pointer to second vector
 * @return 1 if vectors are the same, 0 otherwise
 */
int compareVector(int* vectorA, int* vectorB){
	for(int i = 0; i < NRES; i++){
		//if vector's are not the same, return false
		if(vectorA[i] != vectorB[i]){
			printf("VectorA: %d, VectorB: %d\n", vectorA[i], vectorB[i]);
			return 0;
		}
	}
	return 1;
}


/**
 * Deep copy a given matrix
 * @param oldMatrix pointer to a 2D array
 * @return pointer to the newly copied matrix
 */
int** copyMatrix(int** oldMatrix){
	//allocate space for new matrix
	int** newMatrix = (int**) malloc(sizeof(int*) * NPROC);
	for(int i = 0; i < NPROC; i++){
    	newMatrix[i] = (int*) malloc(sizeof(int) * NRES);
  	}

    for(int i = 0; i < NPROC; i++){
		for(int j = 0; j < NRES; j++){
			newMatrix[i][j] = oldMatrix[i][j];
		}
	}

	return newMatrix; //don't forget to free in main if we use this method
}

/**
 * Deep copy a given vector
 * @param oldVector pointer to a vector
 * @return pointer to the newly copied vector
 */
int* copyVector(int* oldVector){
	//allocate space for new vector
	int* newVector = (int*) malloc(sizeof(int) * NRES);

	for(int i = 0; i < NRES; i++){
		newVector[i] = oldVector[i];
	}

	return newVector;
}


/**
 * Print a given matrix
 * @param matrix pointer to a 2D array
 */
void printMatrix(int** matrix){
    for(int i = 0; i < NPROC; i++){
		for(int j = 0; j < NRES; j++){
			printf("%d ", matrix[i][j]);
		}
        printf("\n");
	}
    printf("\n");
}

/**
 * Print a given vector
 * @param oldVector pointer to a vector
 */
void printVector(int* vector){
	for(int i = 0; i < NRES; i++){
		printf("%d ", vector[i]);
	}
	printf("\n");
	printf("\n");
}

/**
 * Subtracts two matrices
 * @param matrixA pointer to a 2D array
 * @param matrixB pointer to a 2D array
 * @return pointer to the new matrix
 */
int** subMatrix(int** matrixA, int** matrixB){
	//allocate space for new matrix
	int** newMatrix = (int**) malloc(sizeof(int*) * NPROC);
	for(int i = 0; i < NPROC; i++){
    	newMatrix[i] = (int*) malloc(sizeof(int) * NRES);
  	}

    for(int i = 0; i < NPROC; i++){
		for(int j = 0; j < NRES; j++){
			newMatrix[i][j] = (matrixA[i][j] - matrixB[i][j]);
		}
	}

	return newMatrix; //don't forget to free in main if we use this method
}

/**
 * Subtracts two vectors together
 * @param vectorA pointer to first vector
 * @param vectorB pointer to second vector
 * @return pointer to the newly subtracted  vector
 */
int* subVector(int* vectorA, int* vectorB){
	//allocate space for new vector
	int* newVector = (int*) malloc(sizeof(int) * NRES);

	for(int i = 0; i < NRES; i++){
		newVector[i] = vectorA[i] - vectorB[i];
	}

	return newVector; //don't forget to free in main if we use this method
} 
