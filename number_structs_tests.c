#include <stdio.h>
#include "number.h"
#include "tests.h"

void fracReductionTests()
{
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
}

void compAdditionTests()
{
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
}

void compMultiplicationTests()
{
    // COMPLEX NUMBER MULTIPLICATION TESTING
    printf("*****MULTIPLICATION TESTING*****\n\n");
    
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
}

void compNumberTests()
{
    printf("COMPLEX NUMBER ADDITION TESTING\n\n");
    compAdditionTests();
    compMultiplicationTests();
}

void allNumberTests()
{
    fracReductionTests();
    compNumberTests();
}
