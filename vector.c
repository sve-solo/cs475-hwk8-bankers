#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// TODO - Define vector and matrix operations

/**
 * Print a given matrix
 * @param matrix pointer to a 2D array
 */
void printMaxtrix(int** matrix){
    for(int i = 0; i < NPROC; i++){
		for(int j = 0; j < NRES; j++){
			printf("%d ", matrix[i][j]);
		}
        printf("\n");
	}
    printf("\n");
}