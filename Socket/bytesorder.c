/**
 *  检测本机是大端还是小端
*/

#include<stdio.h>

int main()
{
    union{
        short value;
        char bytes[sizeof(short)];
    }test;
    test.value = 0x0102;
    if((test.bytes[0] == 1) && (test.bytes[1] == 2))
    {
        printf("big\n");
    }
    else if((test.bytes[0] == 2) && (test.bytes[1] == 1))
    {
        printf("small\n");
    }
    else
    {
        printf("unkown\n");
    }
    return 0;
}