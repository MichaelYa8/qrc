
#include "itoa.h"

void itoa(char *buffer, unsigned int num)
{
    int i;
    unsigned int tmp;

    buffer[0] = '0';
    buffer[1] = 'x';
    i = 9;
    while(num)
    {
        tmp = num %16;
        if (tmp >= 10)
        {
            buffer[i] = tmp - 10 + 'A';
        }
        else
        {
            buffer[i] = tmp + '0';
        }
        i--;
        num /= 16;
    }
    while( i >= 2)
    {
        buffer[i--] = '0';
    }
    buffer[10] = 0;
}

