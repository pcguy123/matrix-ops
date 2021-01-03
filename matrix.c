#include "matrix.h"


void initMat(struct Matrix* mat, int m, int n, char* name)
{
    mat->mat = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) 
         mat->mat[i] = (int*)malloc(n * sizeof(int));
    mat->m = m;
    mat->n = n;
    mat->detCalc = 0;
    mat->cross = NULL;
    mat->crossCalc = 0;
    mat->eigenValues = NULL;
    mat->eigenVectors = NULL;
    mat->eigenCount = 0;
    mat->inv = NULL;
    mat->invChecked = 0;
    mat->invCoeff = 0.0;
    mat->name = (char*)malloc(8 * sizeof(int));
    strcpy(mat->name, name);
}

// free memory associated with a matrix
void freeMatMemory(struct Matrix* mat)
{
    for(int r = 0; r < mat->m; r++)
        free(mat->mat[r]);
    free(mat->mat);
    
    if(mat->cross != NULL)
        free(mat->cross);
    
    if(mat->eigenValues != NULL)
        free(mat->eigenValues);
    
    if(mat->eigenVectors != NULL)
    {
        for(int v = 0; v < mat->eigenCount; v++)
            free(mat->eigenVectors[v]);
        free(mat->eigenVectors);
    }
    free(mat->name);
}

// mat = matrix, m = # rows, n = # cols
int* generateDigitArray(struct Matrix* mat, int inverse)
{
    int** matToPrint;
    // determines if the printed row will come from the matrix or its inverse
    if(inverse == 0)
        matToPrint = mat->mat;
    else
        matToPrint = mat->inv;
    
    int* greatest = (int*)malloc(mat->n * sizeof(int));
    for(int i = 0; i < mat->n; i++)
        greatest[i] = 0;
    
    // fill "greatest" array with the greatest value in each column of the matrix
    for(int i = 0; i < mat->n; i++)
    {
        for(int j = 0; j < mat->m; j++)
        {
            if(abs(matToPrint[j][i]) > abs(greatest[i]))
                greatest[i] = matToPrint[j][i];
        }
    }
    
    // now, greatest is filled with largest values in each column
    // fill it with the number of digits in each one
    // e.g   [1  153  23]   --->   [1  3  2]
    for(int i = 0; i < mat->n; i++)
        greatest[i] = getDigitCount(greatest[i]);
    return greatest;
}

// mat = matrix, m = # rows, n = # cols, r = row being printed
void printEmptyRow(struct Matrix* mat, int inverse)
{
    int* digits = generateDigitArray(mat, inverse);
    int spacesNeeded = 0;
    
    printf("  ");
    for(int i = 0; i < mat->n; i++)
    {
        // space between two elements
        if(i > 0)
            printf("  ");
        // extra space for correct alignment
        spacesNeeded = digits[i];
        for(int j = 0; j < spacesNeeded; j++)
            printf(" ");
    }
    // freeing memory
    free(digits);
}

// mat = matrix, m = # rows, n = # cols, r = row being printed
void printMatrixRow(struct Matrix* mat, int r, int inverse)
{
    // determines if the printed row will come from the matrix or its inverse
    int** matToPrint;
    if(inverse == 0)
        matToPrint = mat->mat;
    else
        matToPrint = mat->inv;
    
    int* digits = generateDigitArray(mat, inverse);
    int spacesNeeded = 0;
    
    // handles the printing
    printf("[");
    for(int i = 0; i < mat->n; i++)
    {
        // space between two elements
        if(i > 0)
            printf("  ");
        // extra space for correct alignment
        spacesNeeded = digits[i] - getDigitCount(matToPrint[r][i]);
        for(int j = 0; j < spacesNeeded; j++)
            printf(" ");
        // actual element
        printf("%i", matToPrint[r][i]);
    }
    printf("]");
    // freeing memory
    free(digits);
}

// returns the determinant of a matrix - calculated using recursion
int determinantR(int** mat, int m)
{
    // base case for recursion (2x2 matrix)
    if(m == 2)
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    // base case for recursion (1x1 matrix)
    if(m == 1)
        return mat[0][0];
    
    int det = 0;
    // allocates space for the small matrix
    int** small = (int**)malloc((m - 1) * sizeof(int*)); 
    for (int i = 0; i < m - 1; i++) 
        small[i] = (int*)malloc((m - 1) * sizeof(int));
    /*
        pseudocode for the code below:
        
        for each column i in the mxm matrix
            get the smaller (m-1)x(m-1) matrix from each column except column i
                get column i+1, i+2, ... wrap around to first column ... ,i-2, i-1
                for each of those column, copy the column into small matrix
            get determinant of that
            add them all up
            this is recursive
        
    */
    // for each column in mat
    for(int i = 0; i < m; i++)
    {
        // for each column in small
        for(int j = 0; j < m; j++)
        {
            // for each row in small
            for(int k = 0; k < m - 1; k++)
            {
                if(i > j)
                {
                    small[k][j] = mat[k+1][j];
                }
                else if(i < j)
                {
                    small[k][j-1] = mat[k+1][j];
                }
            }
        }
        if(i % 2 == 0)
            det += mat[0][i] * determinantR(small, m - 1);
        else
            det -= mat[0][i] * determinantR(small, m - 1);
    }
    for(int i = 0; i < m - 1; i++)
        free(small[i]);
    free(small);
    return det;
}

// starter function for the determinant - calls the recursive function
int determinant(struct Matrix* mat)
{
    if(mat->detCalc == 0)
    {
        mat->det = determinantR(mat->mat, mat->m);
        mat->detCalc = 1;
    }
    return mat->det;
}

int** inverse(struct Matrix* mat)
{
    if(mat->invChecked == 1)
    {
        if(mat->invertible == 1)
            return mat->inv;
        else
            return NULL;
    }
    
    if(mat->detCalc == 0)
        mat->det = determinant(mat);
    if(mat->det == 0)
    {
        mat->invertible = 0;
        return NULL;
    }
    
    mat->invertible = 1;
    mat->invCoeff = 1 / mat->det;
    mat->inv = (int**)malloc(mat->m * sizeof(int*));
    for (int i = 0; i < mat->m; i++) 
         mat->inv[i] = (int*)malloc(mat->m * sizeof(int));
    
    for(int i = 0; i < mat->m; i++)
    {
        for(int j = 0; j < mat->m; j++)
        {
            if(i % 2 == 0)
            {
                if(j % 2 == 0)
                    mat->inv[j][i] = mat->mat[i][j];
                else
                    mat->inv[j][i] = -1 * mat->mat[i][j];
            }
            else
            {
                if(j % 2 == 0)
                    mat->inv[j][i] = -1 * mat->mat[i][j];
                else
                    mat->inv[j][i] = mat->mat[i][j];
            }
        }
    }
    
    return mat->inv;
}

void printInverse(struct Matrix* mat)
{
    if(mat->invertible)
    {
        printf("%s has inverse:\n", mat->name);
        
        for(int i = 0; i < mat->m; i++)
        {
            if(i == 0)
            {
                if(mat->det < 0)
                    printf("(-1/%i) * ", abs(mat->det));
                else
                    printf("(1/%i) * ", mat->det);
            }
            else
            {
                printf("       ");
                for(int j = 0; j < getDigitCount(mat->det); j++)
                    printf(" ");
            }
            printMatrixRow(mat, i, 1);
            printf("\n");
        }
    }
    else
    {
        printf("%s is not invertible\n", mat->name);
    }
}

// returns the dot product matrix (matrix.mat, not matrix) of two matrices
int** dot(struct Matrix* mat1, struct Matrix* mat2)
{
    /*
        multiplication example
              n             p          p
           [1 2 3]         [5]       [38]
         m [4 5 6]  x   n  [6]  =  m [92]
                           [7]
         2x3            3x1
                            
        end with a 2x1, mxp
    */
    
    // allocates space for the product
    int** mat3 = (int**)malloc(mat1->m * sizeof(int*)); 
    for (int i = 0; i < mat1->m; i++) 
         mat3[i] = (int*)malloc(mat2->n * sizeof(int));
    
    /*  pseudocode for the chunk of code below:
        for(each row in mat1)
            for(each column in mat2)
                multiply corresponding elements
                add them together
                put the result in mat3
    */
    int sum = 0;
    for(int i = 0; i < mat1->m; i++)
    {
        for(int j = 0; j < mat2->n; j++)
        {
            for(int k = 0; k < mat1->n; k++)
                sum += mat1->mat[i][k] * mat2->mat[k][j];
            mat3[i][j] = sum;
            sum = 0;
        }
    }
    
    return mat3;
}

void printDotResult(struct Matrix* mat1, struct Matrix* mat2, struct Matrix* matProd)
{
    int maxRows = 0;
    int middleRow = 0;
    
    if(mat1->m > mat2->m)
        maxRows = mat1->m;
    else
        maxRows = mat2->m;
    
    // determines which row on which to output "*" and "="
    if(maxRows % 2 == 0)
        middleRow = (int)(maxRows / 2);
    else
        middleRow = (int)((maxRows + 1) / 2);
        
    // print out the answer
    for(int i = 0; i < maxRows; i++)
    {
        // if mat1 has row i:
        if(mat1->m > i)
            printMatrixRow(mat1, i, 0);
        // else it will print enough spaces for correct alignment
        else
            printEmptyRow(mat1, 0);
        
        // filler spaces (and equals sign on middle row)
        if(i == middleRow - 1)
            printf("  *  ");
        else
            printf("     ");
        
        // if mat2 has row i:
        if(mat2->m > i)
            printMatrixRow(mat2, i, 0);
        // else it will print enough spaces for correct alignment
        else
            printEmptyRow(mat2, 0);
        
        // filler spaces (and equals sign on middle row)
        if(i == middleRow - 1)
            printf("  =  ");
        else
            printf("     ");
        
        // if mat_prod has row i:
        if(matProd->m > i)
            printMatrixRow(matProd, i, 0);
        // else it will print enough spaces for correct alignment
        else
            printEmptyRow(matProd, 0);
        printf("\n");
    }
}
