
int ndigits(int i)
{
    // absolute value
    i = i < 0 ? -i : i;

    int n = 0;
    while (i > 0) 
    {
        i /= 10;
        n++;
    }

    return n;
}

void itoa(int i, char* buf)
{
    int neg = i < 0;
    int last_index = ndigits(i) + neg;

    if (neg) 
    {
        buf[0] = '-';
        i = -i;
    } 
    else if (i == 0) 
    {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    buf[last_index--] = '\0';

    while (last_index >= neg)
    {
        buf[last_index--] = '0' + (i % 10);
        i /= 10;
    }
}

int strlen(char* buf)
{
    int i = -1;
    while (buf[++i] != '\0');
    return i;
}

int strcmp(char* a, char* b)
{
    int i;
    for (i = 0; a[i] == b[i]; i++)
    {
        if (a[i] == '\0') return 0;
    }
    return a[i] - b[i];
}

void strcat(char* dest, char* src)
{
    int i = strlen(dest);
    
    for (int j = 0; j < strlen(src); j++)
    {
        dest[i++] = src[j];
    }
}

void strcpy(char* dest, char* src)
{
    for (int i = 0; i < strlen(src); i++)
    {
        dest[i] = src[i];
    }
}

void strpop(char* buf)
{
    buf[strlen(buf) - 1] = '\0';
}