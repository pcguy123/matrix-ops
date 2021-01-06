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
    if(f->den.value == 0)
    {
        if(f->num.value < 0)
            initFrac(f, -1, 0, 0);
        else
            initFrac(f, 1, 0, 0);
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
    if(num == 0 && den == 0)
    {
        f->fracChars = 3;
        f->ind = 1;
    }
    else
    {
        f->fracChars = getFracChars(f);
        f->ind = 0;
    }
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

void printNum(struct Number* n)
{
    if(n->imag == 0)
        printf("%i", n->value);
    else
        printf("%ii", n->value);
}

void printFraction(struct Fraction* f)
{
    if(f->ind == 1)
    {
        printf("ind");
        return;
    }
    if(f->den.value == 0)
    {
        if(f->num.value < 0)
            printf("-");
        printf("∞");
        return;
    }
    
    if(f->num.value == 1 && f->num.imag)
        printf("i");
    else if(f->num.value == -1 && f->num.imag)
        printf("-i");
    else
    {
        printf("%i", f->num.value);
        if(f->num.imag && f->num.value != 0)
            printf("i");
    }
    
    if(f->den.value != 1)
        printf("/%i", f->den.value);
}

void printComp(struct ComplexNumber* c)
{
    if(c->real.ind == 1 || c->imag.ind == 1)
    {
        printf("ind");
        return;
    }
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
    return getDigitCount(n->value) + n->imag;
}

int getFracChars(struct Fraction* f)
{
    if(f->ind == 1)
        return 3;
    else if(f->den.value == 0)
        return 1;
    else
    {
        if(f->den.value == 1)
            return getNumChars(&(f->num));
        else
            return getNumChars(&(f->num)) + getNumChars(&(f->den)) + 1;
    }
}

int getCompChars(struct ComplexNumber* c)
{
    if(c->real.ind == 1 || c->imag.ind == 1)
        return 3;
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

// ADD INDETERMINANT
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
    if(f1->ind == 1 || f2->ind == 1)
    {
        initFrac(sum, 0, 0, 0);
        sum->ind = 1;
        return;
    }
    if(f1->den.value == 0 && f2->den.value == 0)
    {
        if((f1->num.value < 0 && f2->num.value > 0) || (f1->num.value > 0 && f2->num.value < 0))
        {
            initFrac(sum, 0, 0, 0);
            sum->ind = 1;
            return;
        }
    }
    else if(f1->den.value == 0 && f2->den.value != 0)
    {
        *sum = *f1;
        reduce(sum);
        return;
    }
    else if(f1->den.value != 0 && f2->den.value == 0)
    {
        *sum = *f2;
        reduce(sum);
        return;
    }
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

void addFracToComp(struct ComplexNumber* c, struct Fraction* f)
{
    if(f->num.imag == 0)
    {
        addFrac(c, &(c->real), f);
    }
    else
    {
        addFrac(c, &(c->imag), f);
    }
}

void multFrac(struct Fraction* prod, struct Fraction* f1, struct Fraction* f2)
{
    if(f1->num.imag == 0 && f2->num.imag == 0)
        initFrac(prod, f1->num.value * f2->num.value, f1->den.value * f2->den.value, 0);
    else if(f1->num.imag == 1 && f2->num.imag == 1)
        initFrac(prod, -1 * f1->num.value * f2->num.value, f1->den.value * f2->den.value, 0);
    else
        initFrac(prod, f1->num.value * f2->num.value, f1->den.value * f2->den.value, 1);
    reduce(prod);
    prod->fracChars = getFracChars(prod);
}

void multComp(struct ComplexNumber* prod, struct ComplexNumber* c1, struct ComplexNumber* c2)
{
    struct Fraction f;
    if(c1->real.ind == 1 || c1->imag.ind == 1 || c2->real.ind == 1 || c2->imag.ind == 1)
    {
        initFrac(&f, 0, 0, 0);
        f.ind = 1;
        initComp(prod, &f, &f);
        return;
    }
    initFrac(&f, 0, 1, 0);
    initComp(prod, &f, &f);
    multFrac(&f, &(c1->real), &(c2->real));
    addFracToComp(prod, &f);
    multFrac(&f, &(c1->real), &(c2->imag));
    addFracToComp(prod, &f);
    multFrac(&f, &(c1->imag), &(c2->real));
    addFracToComp(prod, &f);
    multFrac(&f, &(c1->imag), &(c2->imag));
    addFracToComp(prod, &f);
    prod->compChars = getCompChars(prod);
}
