// main.c
// COMPILE: gcc -Wall -Werror -Wvla main.c matrix.c number.c tests.c number_structs_tests.c -o matrix
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "number.h"
#include "tests.h"
#include "number_structs_tests.h"


// no arguments being used - use this if they will be used in the future (int argc, char* argv[])
int main()
{
    // get the sizes of the input matrices
    int m;
    int n;
    int p;
    printf("Input m, n, and p for dot product:\n");
    scanf("%i", &m);
    scanf("%i", &n);
    scanf("%i", &p);
    
    // create the structs for the input matrices and the product matrix
    struct Matrix matA;
    struct Matrix matB;
    struct Matrix matProd;
    
    initMat(&matA, m, n, "matA");
    initMat(&matB, n, p, "matB");
    initMat(&matProd, m, p, "matProd");
    
    // ask for the values for the first matrix
    printf("Input first matrix (%ix%i = %i values):\n", m, n, m * n);
    
    // get the values for the matA
    for(int i = 0; i < matA.m; i++)
        for(int j = 0; j < matA.n; j++)
            scanf("%i", &(matA.mat[i][j]));
    
    // ask for the values for the second matrix
    printf("Input second matrix (%ix%i = %i values):\n", n, p, n * p);
    
    // get the values for the matB
    for(int i = 0; i < matB.m; i++)
        for(int j = 0; j < matB.n; j++)
            scanf("%i", &(matB.mat[i][j]));
    
    
    // set matProd's matrix to the dot product of matA and matB
    matProd.mat = dot(&matA, &matB);
    
    printf("\n");
    printDotResult(&matA, &matB, &matProd);
    printf("\n");
    
    if(matA.m == matA.n)
    {
        matA.det = determinant(&matA);
        printf("determinant of matA is %i\n", matA.det);
    }
    if(matB.m == matB.n)
    {
        matB.det = determinant(&matB);
        printf("determinant of matB is %i\n", matB.det);
    }
    printf("\n");
    
    // inverse stuff
    matA.inv = inverse(&matA);
    printInverse(&matA);
    matB.inv = inverse(&matB);
    printInverse(&matB);
    
    freeMatMemory(&matA);
    freeMatMemory(&matB);
    freeMatMemory(&matProd);
    
    printf("\n");
    
    allNumberTests();
    
    return EXIT_SUCCESS;
}