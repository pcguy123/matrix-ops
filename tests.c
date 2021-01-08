#include "tests.h"


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
