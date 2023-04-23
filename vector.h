
// TODO: function prototypes of vector and matrix operations
int **addMatrix(int **matrixA, int **matrixB);

int *addVector(int *vectorA, int *vectorB);

void addVec2toVec1(int *vec1, int *vec2);

int vec1GreaterOrEqualVec2(int *greater, int *lesser);

int compareVector(int *vectorA, int *vectorB);

int **copyMatrix(int **oldMatrix);

int *copyVector(int *oldVector);

void clonevec(int *vec, int *result);

void printMatrix(int **matrix);

void printVector(int *vector);

int **subMatrix(int **matrixA, int **matrixB);

int *subVector(int *vectorA, int *vectorB);

void subtractvecs(int *vec1, int *vec2, int *result);

void sumRows(int **mat, int *result);

void subtractmats(int **mat1, int **mat2, int **result);

extern int NRES;  // number of resource types
extern int NPROC; // number of processes