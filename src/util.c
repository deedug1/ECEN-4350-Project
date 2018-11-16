#include <string.h>
#include "../headers/util.h"



void reverse(char * s) {
    int i = 0, j = strlen(s) - 1;
    char c;
    for(; i < j; i++, j--) {
        c = s[j];
        s[j] = s[i];
        s[i] = c;
    }
}
void itoa(int num, char * buf, int radix) {
    signed char sign;
    if((sign = num) < 0) {
        num = -num;
    }
    while(num > 0 ) {
        *buf = (num % 10) | 0x30;   // ASCII
        buf++;
        num /= 10;
    }
    if(sign < 0){
        *buf = '-';
        buf++;
    }
    *buf = '\0';
    reverse(buf);
}

