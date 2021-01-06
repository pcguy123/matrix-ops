// main.c
// COMPILE: gcc -Wall -Werror -Wvla main.c matrix.c number.c -o matrix
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "number.h"


void charTest(struct ComplexNumber* c)
{
    printf("CHARACTER TEST\nc: ");
    printComp(c);
    printf("\t%i\n\tr: ", getCompChars(c));
    printFraction(&(c->real));
    printf("\t%i\n\t\tn: ", getFracChars(&(c->real)));
    printNum(&(c->real.num));
    printf("\t%i\n\t\td: ", getNumChars(&(c->real.num)));
    printNum(&(c->real.den));
    printf("\t%i\n\ti: ", getNumChars(&(c->real.den)));
    printFraction(&(c->imag));
    printf("\t%i\n\t\tn: ", getFracChars(&(c->imag)));
    printNum(&(c->imag.num));
    printf("\t%i\n\t\td: ", getNumChars(&(c->imag.num)));
    printNum(&(c->imag.den));
    printf("\t%i\n\n", getNumChars(&(c->imag.den)));
}

void fracTest(struct Fraction* f, int num, int den, int imag)
{
    initFrac(f, num, den, imag);
    printf("OR: Fraction = ");
    printFraction(f);
    printf("\n");
    reduce(f);
    printf("RE: Fraction = ");
    printFraction(f);
    printf("\n");
    printf("\n");
}

void compTest(struct ComplexNumber* c)
{
    printf("OR: ");
    printComp(c);
    printf("\n");
    reduce(&(c->real));
    reduce(&(c->imag));
    printf("RE: ");
    printComp(c);
    printf("\n\n");
}

void compAddTest(struct ComplexNumber* c1, struct ComplexNumber* c2)
{
    struct ComplexNumber sum;
    addComp(&sum, c1, c2);
    printComp(c1);
    printf(" + ");
    printComp(c2);
    printf(" = ");
    printComp(&sum);
    printf("\n\n");
}

void compMultTest(struct ComplexNumber* c1, struct ComplexNumber* c2)
{
    struct ComplexNumber prod;
    multComp(&prod, c1, c2);
    printComp(c1);
    printf(" * ");
    printComp(c2);
    printf(" = ");
    printComp(&prod);
    printf("\n\n");
    charTest(&prod);
    printf("\n\n");
}

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
    
    // fraction stuff
    struct Fraction f;
    
    // PLAIN REDUCE
    
    // 5/10 -> 1/2
    fracTest(&f, 5, 10, 0);
    
    // -5/10 -> -1/2
    fracTest(&f, -5, 10, 0);
    
    // 5/-10 -> -1/2
    fracTest(&f, 5, -10, 0);
    
    // -5/-10 -> 1/2
    fracTest(&f, -5, -10, 0);
    
    // IMAGINARIES
    
    // 5i/10 -> i/2
    fracTest(&f, 5, 10, 1);
    
    // -5i/10 -> -i/2
    fracTest(&f, -5, 10, 1);
    
    // 5i/-10 -> -i/2
    fracTest(&f, 5, -10, 1);
    
    // -5i/-10 -> i/2
    fracTest(&f, -5, -10, 1);
    
    // DIFFERENT FRACTIONS
    
    // 4i/10 -> 2i/5
    fracTest(&f, 4, 10, 1);
    
    // 4i/2 -> 2i
    fracTest(&f, 4, 2, 1);
    
    // 4/2 -> 2
    fracTest(&f, 4, 2, 0);
    
    // -4i/2 -> -2i
    fracTest(&f, -4, 2, 1);
    
    // 4i/-2 -> -2i
    fracTest(&f, 4, -2, 1);
    
    // -4i/-2 -> 2i
    fracTest(&f, -4, -2, 1);
    
    
    
    
    
    printf("COMPLEX NUMBER ADDITION TESTING\n\n");
    printf("*****ADDITION TESTING*****\n\n");
    
    struct ComplexNumber c1;
    struct ComplexNumber c2;
    
    struct Fraction f1;
    struct Fraction f2;
    
    // 4/2+4i/2 -> 2+2i
    initFrac(&f1, 4, 2, 0);
    initFrac(&f2, 4, 2, 1);
    initComp(&c1, &f1, &f2);
    compTest(&c1);
    
    // -4/2+5i/1 -> -2+5i
    f1.num.value = -4;
    f1.den.value = 2;
    f2.num.value = 5;
    f2.den.value = 1;
    initComp(&c2, &f1, &f2);
    compTest(&c2);
    
    // 2+2i + -2+5i = 7i
    compAddTest(&c1, &c2);
    
    // -4/2+5i/1 -> -2+5i
    initComp(&c1, &f1, &f2);
    compTest(&c1);
    
    // 8/6+6i/8 -> 4/3+3i/4
    f1.num.value = 8;
    f1.den.value = 6;
    f2.num.value = 6;
    f2.den.value = 8;
    initComp(&c2, &f1, &f2);
    compTest(&c2);
    
    // -2+5i + 4/3+3i/4 = -2/3+23i/4
    compAddTest(&c1, &c2);
    
    charTest(&c1);
    charTest(&c2);
    
    // f1: 0/1 -> 0
    // f2: 0i/1 -> 0
    f1.num.value = 0;
    f1.den.value = 1;
    f2.num.value = 0;
    f2.den.value = 1;
    initComp(&c1, &f1, &f2);
    initComp(&c2, &f1, &f2);
    compTest(&c1);
    compTest(&c2);
    
    // 0+0i + 0+0i = 0
    compAddTest(&c1, &c2);
    
    // f1: 0/1 -> 0
    // f2: 0i/0 -> ind
    f2.den.value = 0;
    initComp(&c1, &f1, &f2);
    initComp(&c2, &f1, &f2);
    compTest(&c1);
    compTest(&c2);
    
    // 0+∞i + 0+∞i = ∞
    compAddTest(&c1, &c2);
    
    // f1: 0/1 -> 0
    // f2: 1i/0 -> ∞
    f2.num.value = 1;
    initComp(&c1, &f1, &f2);
    compTest(&c1);
    
    charTest(&c1);
    charTest(&c2);
    
    // f1: 0/1 -> 0
    // f2: 0i/1 -> 0
    f2.num.value = 0;
    f2.den.value = 1;
    initComp(&c2, &f1, &f2);
    compTest(&c2);
    
    // 0+∞i + 0+0i = 0
    compAddTest(&c1, &c2);
    
    
    
    
    
    // COMPLEX NUMBER MULTIPLICATION TESTING
    printf("*****MULTIPLICATION TESTING*****\n\n");
    
    // 4/2+4i/2 -> 2+2i
    initFrac(&f1, 4, 2, 0);
    initFrac(&f2, 4, 2, 1);
    initComp(&c1, &f1, &f2);
    compTest(&c1);
    
    // -4/2+5i/1 -> -2+5i
    f1.num.value = -4;
    f1.den.value = 2;
    f2.num.value = 5;
    f2.den.value = 1;
    initComp(&c2, &f1, &f2);
    compTest(&c2);
    
    // 2+2i + -2+5i = 7i
    compMultTest(&c1, &c2);
    
    // -4/2+5i/1 -> -2+5i
    initComp(&c1, &f1, &f2);
    compTest(&c1);
    
    // 8/6+6i/8 -> 4/3+3i/4
    f1.num.value = 8;
    f1.den.value = 6;
    f2.num.value = 6;
    f2.den.value = 8;
    initComp(&c2, &f1, &f2);
    compTest(&c2);
    
    // -2+5i + 4/3+3i/4 = -2/3+23i/4
    compMultTest(&c1, &c2);
    
    // f1: 0/1 -> 0
    // f2: 0i/1 -> 0
    f1.num.value = 0;
    f1.den.value = 1;
    f2.num.value = 0;
    f2.den.value = 1;
    initComp(&c1, &f1, &f2);
    initComp(&c2, &f1, &f2);
    compTest(&c1);
    compTest(&c2);
    
    // 0+0i + 0+0i = 0
    compMultTest(&c1, &c2);
    
    // f1: 0/1 -> 0
    // f2: 0i/0 -> ind
    f2.den.value = 0;
    initComp(&c1, &f1, &f2);
    initComp(&c2, &f1, &f2);
    compTest(&c1);
    compTest(&c2);
    
    // 0+∞i + 0+∞i = ∞
    compMultTest(&c1, &c2);
    
    // f1: 0/1 -> 0
    // f2: 1i/0 -> ∞
    f2.num.value = 1;
    initComp(&c1, &f1, &f2);
    compTest(&c1);
    
    // f1: 0/1 -> 0
    // f2: 0i/1 -> 0
    f2.num.value = 0;
    f2.den.value = 1;
    initComp(&c2, &f1, &f2);
    compTest(&c2);
    
    // 0+∞i + 0+0i = 0
    compMultTest(&c1, &c2);
    
    return EXIT_SUCCESS;
}