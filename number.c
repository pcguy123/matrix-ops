#include "number.h"


int gcd(int v1, int v2)
{
    int rem = v1 % v2;
    if(rem == 0)
        return v2;
    else
        return gcd(v2, rem);
}

void reduce(struct Fraction* f)
{
    if(f->num.value == 0)
    {
        f->num.imag = 0;
        f->den.value = 1;
        f->den.imag = 0;
        return;
    }
    
    if(f->den.value < 0)
    {
        f->num.value *= -1;
        f->den.value *= -1;
    }
    
    // cancel out imaginaries if possible
    if(f->num.imag == f->den.imag)
    {
        f->num.imag = 0;
        f->den.imag = 0;
    }
    
    if(f->den.imag == 1)
    {
        f->num.imag = 1;
        f->den.imag = 0;
    }
    
    if(f->den.value < 0)
    {
        f->num.value *= -1;
        f->den.value *= -1;
    }
    
    // reduce fractions
    int div = gcd(abs(f->num.value), abs(f->den.value));
    f->num.value /= div;
    f->den.value /= div;
}

// returns the absolute value of n
int abs(int n)
{
    if(n < 0)
        return -1 * n;
    return n;
}

// initializes Number n
void initNum(struct Number* n, int value, int imag)
{
    n->value = value;
    n->imag = imag;
    n->numChars = getNumChars(n);
}

// initializes Fraction f
void initFrac(struct Fraction* f, int num, int den, int imag)
{
    initNum(&(f->num), num, imag);
    initNum(&(f->den), den, 0);
    f->fracChars = getFracChars(f);
}

// initializes ComplexNumber c
void initComp(struct ComplexNumber* c, struct Fraction* r, struct Fraction* i)
{
    if(r != NULL)
        initFrac(&(c->real), r->num.value, r->den.value, 0);
    else
        initFrac(&(c->real), 0, 1, 0);
    
    if(i != NULL)
        initFrac(&(c->imag), i->num.value, i->den.value, 1);
    else
        initFrac(&(c->imag), 0, 1, 0);
    
    c->compChars = getCompChars(c);
}

// prints Fraction f
void printFraction(struct Fraction* f)
{
    if(f->num.value == 1 && f->num.imag)
        printf("i");
    else if(f->num.value == -1 && f->num.imag)
        printf("-i");
    else
    {
        printf("%i", f->num.value);
        if(f->num.imag)
            printf("i");
    }
    
    if(f->den.value != 1)
        printf("/%i", f->den.value);
}

// prints ComplexNumber c
void printComp(struct ComplexNumber* c)
{
    if(c->real.num.value != 0)
    {
        printFraction(&(c->real));
        if(c->imag.num.value == 0)
            return;
        if(c->imag.num.value > 0)
            printf("+");
        printFraction(&(c->imag));
    }
    else
    {
        printFraction(&(c->imag));
    }
}

// returns the number of digits are in the number n (+1 for negative sign)
int getDigitCount(int n)
{
    int count = 0;
    if(n < 0)
        count++;
    if(n == 0)
        return 1;
    while(n != 0)
    {
        count++;
        n /= 10;
    }
    return count;
}

int getNumChars(struct Number* n)
{
    return getDigitCount(n->value);
}

int getFracChars(struct Fraction* f)
{
    int count = getNumChars(&(f->num)) + getNumChars(&(f->den)) + 1;
    return count;
}

int getCompChars(struct ComplexNumber* c)
{
    if((c->real.num.value == 0) && (c->imag.num.value == 0))
        return 1;
    
    
    int count = 0;
    
    if(c->real.num.value != 0)
    {
        count += getFracChars(&(c->real));
        if(c->imag.num.value > 0)
        {
            count += getFracChars(&(c->imag)) + 1;
        }
        else if(c->imag.num.value < 0)
        {
            count += getFracChars(&(c->imag));
        }
    }
    else
    {
        count += getFracChars(&(c->imag));
    }
    
    return count;
}

void multNum(struct Number* prod, struct Number* n1, struct Number* n2)
{
    prod->value = n1->value * n2->value;
    if(n1->imag == n2->imag)
        prod->imag = 0;
    else
        prod->imag = 1;
}

void addFracS(struct Fraction* sum, struct Fraction* f1, struct Fraction* f2)
{
    sum->num.value = f1->num.value * f2->den.value + f2->num.value * f1->den.value;
    sum->den.value = f1->den.value * f2->den.value;
    sum->num.imag = f1->num.imag;
    sum->den.imag = 0;
    reduce(sum);
}

void addFrac(struct ComplexNumber* c, struct Fraction* f1, struct Fraction* f2)
{
    if(f1->num.imag && f2->num.imag)
        addFracS(&(c->imag), f1, f2);
    else if(f1->num.imag == 0 && f2->num.imag == 0)
        addFracS(&(c->real), f1, f2);
    else
    {
        if(f1->num.imag == 0)
        {
            c->real = *f1;
            c->imag = *f2;
        }
        else
        {
            c->real = *f2;
            c->imag = *f1;
        }
    }
}

void addComp(struct ComplexNumber* sum, struct ComplexNumber* c1, struct ComplexNumber* c2)
{
    addFracS(&(sum->real), &(c1->real), &(c2->real));
    addFracS(&(sum->imag), &(c1->imag), &(c2->imag));
    sum->compChars = getCompChars(sum);
}
