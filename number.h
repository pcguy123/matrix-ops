#ifndef __number__
#define __number__

#include <stdio.h>
#include <stdlib.h>

struct Number
{
    int value;
    int imag;
    int numChars;
};

struct Fraction
{
    struct Number num;
    struct Number den;
    int fracChars;
    int ind;
};

struct ComplexNumber
{
    struct Fraction real;
    struct Fraction imag;
    int compChars;
};

// returns the greatest common divisor of two numbers
int gcd(int v1, int v2);
// reduces Fractions
void reduce(struct Fraction* f);
// returns the absolute value of a number
int abs(int n);
// initializers for the Number, Fraction, and ComplexNumber structs
void initNum(struct Number* n, int value, int imag);
void initFrac(struct Fraction* f, int num, int den, int imag);
void initComp(struct ComplexNumber* c, struct Fraction* r, struct Fraction* i);
void setReal(struct ComplexNumber* c, struct Fraction* f);
void setImag(struct ComplexNumber* c, struct Fraction* f);
// functions for printing fractions and complex numbers
void printNum(struct Number* n);
void printFraction(struct Fraction* f);
void printComp(struct ComplexNumber* c);
// returns the number of characters in the string representation of integers, Numbers,
// Fractions and ComplexNumbers
int getDigitCount(int n);
int getNumChars(struct Number* n);
int getFracChars(struct Fraction* f);
int getCompChars(struct ComplexNumber* c);
// results are the sums of Numbers, Fractions, and ComplexNumbers
// functions ending with S means it should be used if both inputs are real or
// if both inputs are imaginary
// functions not ending with S will result in a ComplexNumber
void addNumS(struct Number* sum, struct Number* n1, struct Number* n2);
void addNum(struct ComplexNumber* sum, struct Number* n1, struct Number* n2);
void addFracS(struct Fraction* sum, struct Fraction* f1, struct Fraction* f2);
void addFrac(struct ComplexNumber* c, struct Fraction* f1, struct Fraction* f2);
void addComp(struct ComplexNumber* sum, struct ComplexNumber* c1, struct ComplexNumber* c2);
void checkAddProb(struct Fraction* f1, struct Fraction* f2);
// returns the products of Numbers, Fractions, and ComplexNumbers
void multNum(struct Number* prod, struct Number* n1, struct Number* n2);
void multFrac(struct Fraction* prod, struct Fraction* f1, struct Fraction* f2);
void multComp(struct ComplexNumber* prod, struct ComplexNumber* c1, struct ComplexNumber* c2);

#endif
