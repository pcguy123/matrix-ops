#include "number.h"


int gcd(int v1, int v2)
{
    int rem = v1 % v2;
    if(rem == 0)
        return v2;
    else
        return gcd(v2, rem);
}

// returns the absolute value of n
int abs(int n)
{
    if(n < 0)
        return -1 * n;
    return n;
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
