#ifndef __matrix__
#define __matrix__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "number.h"

struct Matrix
{
    int** mat;
    int m;
    int n;
    int det;
    int detCalc;
    int* cross;
    int crossCalc;
    int* eigenValues;
    int** eigenVectors;
    int eigenCount;
    int** inv;
    int invChecked;
    int invertible;
    double invCoeff;
    char* name;
};

void initMat(struct Matrix* mat, int m, int n, char* name);
void freeMatMemory(struct Matrix* mat);
int* generateDigitArray(struct Matrix* mat, int inverse);
void printEmptyRow(struct Matrix* mat, int inverse);
void printMatrixRow(struct Matrix* mat, int r, int inverse);
int determinantR(int** mat, int m);
int determinant(struct Matrix* mat);
int** inverse(struct Matrix* mat);
void printInverse(struct Matrix* mat);
int** dot(struct Matrix* mat1, struct Matrix* mat2);
void printDotResult(struct Matrix* mat1, struct Matrix* mat2, struct Matrix* matProd);

#endif

