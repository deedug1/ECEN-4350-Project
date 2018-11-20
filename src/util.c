#include <string.h>
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
void itoa(int num, char * buf, int radix) {
    signed char sign;
    int i = 0;
    if((sign = num) < 0) {
        num = -num;
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
}

