#include <string.h>
#include <math.h>
#include "../headers/util.h"



void reverse(char * s) {
    int i, j; 
    char c;
    for(i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[j];
        s[j] = s[i];
        s[i] = c;
    }
}
int itoa(int num, char * buf, int radix) {
    signed char sign;
    int i = 0;
    if((sign = num) < 0) {
        num = -num;
    } else if(num == 0) {
        *(buf + i) = '0';
        i++;
    }
    while(num > 0 ) {
        *(buf + i) = (num % radix) | 0x30;   // ASCII
        i++;
        num /= radix;
    }
    if(sign < 0){
        *(buf + i) = '-';
        i++;
    }
    *(buf + i) = '\0';
    reverse(buf);
    
    return i;
}
void dtoa(double num, char * buf, int radix) {
    int ipart = (int) num;
    double dpart = num - (double)ipart;
    int i = itoa(ipart, buf, radix);
    *(buf + i) = '.';
    
    dpart = dpart  * pow(10, 2); // 2 decimal points
    
    itoa((int)dpart, buf + i + 1, 10);
    
    
}
