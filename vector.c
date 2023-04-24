/**
 * Define vector and matrix operations
 */
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

/**
 * Adds two matrices together
 * @param matrixA pointer to a 2D array
 * @param matrixB pointer to a 2D array
 * @return pointer to the newly added matrix
 */
int **addMatrix(int **matrixA, int **matrixB)
{
	// allocate space for new matrix
	int **newMatrix = (int **)malloc(sizeof(int *) * NPROC);
	for (int i = 0; i < NPROC; i++)
	{
		newMatrix[i] = (int *)malloc(sizeof(int) * NRES);
	}

	for (int i = 0; i < NPROC; i++)
	{
		for (int j = 0; j < NRES; j++)
		{
			newMatrix[i][j] = (matrixA[i][j] + matrixB[i][j]);
		}
	}

	return newMatrix; // don't forget to free in main if we use this method
}

/**
 * Adds two vectors together
 * @param vectorA pointer to first vector
 * @param vectorB pointer to second vector
 * @return pointer to the newly added vector
 */
int *addVector(int *vectorA, int *vectorB)
{
	// allocate space for new vector
	int *newVector = (int *)malloc(sizeof(int) * NRES);

	for (int i = 0; i < NRES; i++)
	{
		newVector[i] = vectorA[i] + vectorB[i];
	}

	return newVector; // don't forget to free in main if we use this method
}

/**
 * Add one vector to another vector
 * @param vec1  The vector that will hold the sum
 * @param vec2  The vector that will be added to vec1
 * @param ncols  The number of elements in each vector
 */
void addVec2toVec1(int *vec1, int *vec2)
{
	// TODO: This seemed more convenient than creating a new vector,
	// and if it is only used on clones (i.e. workVec), it should not
	// cause problems. But will need to make sure once we try different orderings
	for (int i = 0; i < NRES; i++)
		vec1[i] += vec2[i];
	return;
}

/**
 * Compare two given vectors
 * @param vectorA pointer to first vector
 * @param vectorB pointer to second vector
 * @return 1 if vectors are the same, 0 otherwise
 */
int compareVector(int *vectorA, int *vectorB)
{
	for (int i = 0; i < NRES; i++)
	{
		// if vector's are not the same, return false
		if (vectorA[i] != vectorB[i])
		{
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
int **copyMatrix(int **oldMatrix)
{
	// allocate space for new matrix
	int **newMatrix = (int **)malloc(sizeof(int *) * NPROC);
	for (int i = 0; i < NPROC; i++)
	{
		newMatrix[i] = (int *)malloc(sizeof(int) * NRES);
	}

	for (int i = 0; i < NPROC; i++)
	{
		for (int j = 0; j < NRES; j++)
		{
			newMatrix[i][j] = oldMatrix[i][j];
		}
	}

	return newMatrix; // don't forget to free in main if we use this method
}

/**
 * Deep copy a given vector
 * @param oldVector pointer to a vector
 * @return pointer to the newly copied vector
 */
int *copyVector(int *oldVector)
{
	// allocate space for new vector
	int *newVector = (int *)malloc(sizeof(int) * NRES);

	for (int i = 0; i < NRES; i++)
	{
		newVector[i] = oldVector[i];
	}

	return newVector; // don't forget to free in main if we use this method
}

/**
 * Clone vector
 * @param vec  Pointer to the original vector, to be cloned
 * @param result  Pointer to the vector to resulting clone
 */
void clonevec(int *vec, int *result)
{
	for (int col = 0; col < NRES; col++)
		result[col] = vec[col];
	return; 
}

/**
 * Print a given matrix
 * @param matrix pointer to a 2D array
 */
void printMatrix(int **matrix)
{
	for (int i = 0; i < NPROC; i++)
	{
		for (int j = 0; j < NRES; j++)
		{
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
void printVector(int *vector)
{
	for (int i = 0; i < NRES; i++)
	{
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
int **subMatrix(int **matrixA, int **matrixB)
{
	// allocate space for new matrix
	int **newMatrix = (int **)malloc(sizeof(int *) * NPROC);
	for (int i = 0; i < NPROC; i++)
	{
		newMatrix[i] = (int *)malloc(sizeof(int) * NRES);
	}

	for (int i = 0; i < NPROC; i++)
	{
		for (int j = 0; j < NRES; j++)
		{
			newMatrix[i][j] = (matrixA[i][j] - matrixB[i][j]);
		}
	}

	return newMatrix; // don't forget to free in main if we use this method
}

/**
 * Subtract two matrices and assign the result to a third matrix
 * whose pointer is an input
 * @param mat1  Pointer to the matrix to subtract from
 * @param mat2  Pointer to the matrix to be subtract
 * @param result  A pointer to the matrix to assign the results to
 */
void subtractmats(int **mat1, int **mat2, int **result)
{
	for (int i = 0; i < NPROC; i++)
		for (int j = 0; j < NRES; j++)
			result[i][j] = mat1[i][j] - mat2[i][j];
	return;
}

/**
 * Subtracts two vectors together
 * @param vectorA pointer to first vector
 * @param vectorB pointer to second vector
 * @return pointer to the newly subtracted  vector
 */
int *subVector(int *vectorA, int *vectorB)
{
	// allocate space for new vector
	int *newVector = (int *)malloc(sizeof(int) * NRES);

	for (int i = 0; i < NRES; i++)
	{
		newVector[i] = vectorA[i] - vectorB[i];
	}

	return newVector; // don't forget to free in main if we use this method
}

/**
 * Subtract two vectors and assign the result to a third vector
 * If the third vector is mallocd, it should be done in the calling function
 * that way it can be freed there.
 * @param vec1  Pointer to the vector to subract from
 * @param vec2  Pointer to the vector to be subtracted from vec1
 * @param result  Pointer to the resulting vector
 * @param ncols  Number of elements in each vector
 */
void subtractvecs(int *vec1, int *vec2, int *result)
{
	for (int i = 0; i < NRES; i++)
		result[i] = vec1[i] - vec2[i];
	return;
}

/**
 * Determine if one vector is >= another
 * @param greater  The vector to test (should be >= the other)
 * @param vec2  The vector to compare against (should be < the other)
 * @returns 1 if True, 0 if False
 */
int vec1GreaterOrEqualVec2(int *greater, int *lesser)
{
	// TODO: we could malloc this temporary vector and then free it before returning,
	// but it's only a vector so maybe not necessary?
	int result[NRES];
	subtractvecs(greater, lesser, result);
	for (int col = 0; col < NRES; col++)
		if (result[col] < 0)
			return 0;
	return 1;
}

/**
 * Sum rows of a matrix for each column and assign the result to a vector
 * @params mat  Pointer to the matrix to sum the rows of
 * @params result  Pointer to assign the results to
 */
void sumRows(int **mat, int *result)
{
	for (int col = 0; col < NRES; col++)
	{
		result[col] = 0;
		for (int row = 0; row < NPROC; row++)
			result[col] += mat[row][col];
	}
	return;
}
