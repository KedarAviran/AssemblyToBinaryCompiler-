#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "conversion.h"
#define MAXBITS 10
#define MAX 80
char base32[32] = {'!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};
int test;
/* revese the string*/
void revstr(char* str)
{
    int i, len, temp;
    len = strlen(str);  
    for (i = 0; i < len / 2; i++)
    {
        temp = *(str+i);
        *(str+i) = *(str+len - i - 1);
        *(str+len - i - 1) = temp;
    }
}
/* converts binary to decimal*/
char* binToDec(char bin[])
{
    char* result;
    int num, decimal_num = 0, base = 1, rem;
    num = atoi(bin);
    while (num > 0)
    {
        rem = num % 10;
        decimal_num = decimal_num + rem * base;
        num = num / 10;
        base = base * 2;
    }
    result= (char*)malloc(MAX);
    sprintf(result, "%d", decimal_num);
    /* itoa(decimal_num, result, 10); */
    return result;
}
/* converts decimal to binary*/
char* numToBin(char num[], int bits)
{
    int data;
    unsigned int i;
    char* bin_str;
    data = atoi(num);
    bin_str = (char*)malloc(MAX);
    for (i = 0; i < bits; i++)
    {
        unsigned int mask = 1u << (bits - 1 - i);
        bin_str[i] = (data & mask) ? '1' : '0';
    }
    bin_str[bits] = '\0';
    return bin_str;
}
/* converts register to binary*/
char* registerToBin(char data[], int bits)
{
    return numToBin(data + 1, bits);
}
/* converts command to binary*/
char* opToBin(char data[])
{
    struct DataItem* opCMD = search(data);
    return numToBin(getOp(opCMD),4);
}
/* converts decimal to base32*/
char* numToBase32(char* data)
{
    int i;
    char* bin;
    int addZero;
    int num;
    addZero = 0;
    num = atoi(data);
    if (num < 32)
        addZero = 1;
    bin = (char*)malloc(sizeof(char) * MAXBITS);
    if (num == 0)
    {
        bin = "!!";
        return bin;
    }
    for (i=0; num > 0; i++) 
    {
        *(bin + i) = base32[num % 32];
        num = num / 32;
    }
    *(bin + i) = '\0';
    revstr(bin);
    if (addZero == 1)
    {
        char* fix;
        fix = (char*)malloc(sizeof(char) * MAXBITS);
        fix[0] = base32[0];
        *(fix + i) = '\0';
        strcat(fix, bin);
        return fix;
    }
    return bin;
}
/* converts char to binary*/
char* charToBin(char data)
{
    int asciiData;
    char* bin;
    asciiData = data;
    bin = (char*)calloc(11,sizeof(char));
    sprintf(bin, "%d", asciiData);
    /* itoa(asciiData, bin, 10); */
    return numToBin(bin,10);
}
/* converts binary to base32*/
char* binToBase32(char* data)
{
    return numToBase32(binToDec(data));
}
