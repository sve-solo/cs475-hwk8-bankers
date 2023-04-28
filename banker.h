/* declarations related to banker's algorithm */

int isSafe(int *availVec, int **allocMat, int **needMat);

int safeCheck(int* workVec, int* finishVec, int** allocMat, int** needMat, int* sequence, int recurse);
