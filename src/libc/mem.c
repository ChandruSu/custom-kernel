#include "mem.h"

void memcpy(void* src, void* dest, int n)
{
    unsigned char* d = (unsigned char*)dest;
    unsigned char* s = (unsigned char*)src;

    for (int i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

void memset(void* dest, int n, char v)
{
    unsigned char* d = (unsigned char*)dest;

    for (int i = 0; i < n; i++) {
        d[i] = v;
    }
}
