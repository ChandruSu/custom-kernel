#include "math.h"

int ipow(int base, int exp)
{
    int result = 1;
    
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

int min(int a, int b)
{
    return a < b ? a : b;
}


int max(int a, int b)
{
    return a > b ? a : b;
}