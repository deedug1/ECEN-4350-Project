# 1 "src/util.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "src/util.c" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\string.h" 1 3



# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\string.h" 2 3






# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\features.h" 1 3
# 10 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\string.h" 2 3
# 25 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\string.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 127 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned size_t;
# 409 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct __locale_struct * locale_t;
# 25 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\string.h" 2 3


void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);

char *strcpy (char *restrict, const char *restrict);
char *strncpy (char *restrict, const char *restrict, size_t);

char *strcat (char *restrict, const char *restrict);
char *strncat (char *restrict, const char *restrict, size_t);

int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);

int strcoll (const char *, const char *);
size_t strxfrm (char *restrict, const char *restrict, size_t);

char *strchr (const char *, int);
char *strrchr (const char *, int);

size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *restrict, const char *restrict);

size_t strlen (const char *);

char *strerror (int);
# 65 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\string.h" 3
char *strtok_r (char *restrict, const char *restrict, char **restrict);
int strerror_r (int, char *, size_t);
char *stpcpy(char *restrict, const char *restrict);
char *stpncpy(char *restrict, const char *restrict, size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);




void *memccpy (void *restrict, const void *restrict, int, size_t);
# 1 "src/util.c" 2

# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\math.h" 1 3
# 10 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\math.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 1 3
# 22 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 135 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 150 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 166 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef long int32_t;





typedef long long int64_t;
# 191 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 227 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 22 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 2 3


typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 131 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 131 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 2 3
# 10 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\math.h" 2 3





# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 37 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef float float_t;




typedef double double_t;
# 15 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\math.h" 2 3
# 46 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\math.h" 3
int __fpclassifyf(float);
# 97 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\math.h" 3
int __signbitf(float);
# 149 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\math.h" 3
double acos(double);
float acosf(float);
long double acosl(long double);





double acosh(double);
float acoshf(float);
long double acoshl(long double);





double asin(double);
float asinf(float);
long double asinl(long double);





double asinh(double);
float asinhf(float);
long double asinhl(long double);





double atan(double);
float atanf(float);
long double atanl(long double);





double atan2(double, double);
float atan2f(float, float);
long double atan2l(long double, long double);





double atanh(double);
float atanhf(float);
long double atanhl(long double);





double cbrt(double);
float cbrtf(float);
long double cbrtl(long double);





double ceil(double);
float ceilf(float);
long double ceill(long double);





double copysign(double, double);
float copysignf(float, float);
long double copysignl(long double, long double);





double cos(double);
float cosf(float);
long double cosl(long double);





double cosh(double);
float coshf(float);
long double coshl(long double);





double erf(double);
float erff(float);
long double erfl(long double);





double erfc(double);
float erfcf(float);
long double erfcl(long double);





double exp(double);
float expf(float);
long double expl(long double);





double exp2(double);
float exp2f(float);
long double exp2l(long double);





double expm1(double);
float expm1f(float);
long double expm1l(long double);





double fabs(double);
float fabsf(float);
long double fabsl(long double);





double fdim(double, double);
float fdimf(float, float);
long double fdiml(long double, long double);





double floor(double);
float floorf(float);
long double floorl(long double);





double fma(double, double, double);
float fmaf(float, float, float);
long double fmal(long double, long double, long double);





double fmax(double, double);
float fmaxf(float, float);
long double fmaxl(long double, long double);





double fmin(double, double);
float fminf(float, float);
long double fminl(long double, long double);





double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);





double frexp(double, int *);
float frexpf(float, int *);
long double frexpl(long double, int *);





double hypot(double, double);
float hypotf(float, float);
long double hypotl(long double, long double);





int ilogb(double);
int ilogbf(float);
int ilogbl(long double);





double ldexp(double, int);
float ldexpf(float, int);
long double ldexpl(long double, int);





double lgamma(double);
float lgammaf(float);
long double lgammal(long double);





long long llrint(double);
long long llrintf(float);
long long llrintl(long double);





long long llround(double);
long long llroundf(float);
long long llroundl(long double);





double log(double);
float logf(float);
long double logl(long double);





double log10(double);
float log10f(float);
long double log10l(long double);





double log1p(double);
float log1pf(float);
long double log1pl(long double);





double log2(double);
float log2f(float);
long double log2l(long double);





double logb(double);
float logbf(float);
long double logbl(long double);





long lrint(double);
long lrintf(float);
long lrintl(long double);





long lround(double);
long lroundf(float);
long lroundl(long double);





double modf(double, double *);
float modff(float, float *);
long double modfl(long double, long double *);





double nan(const char *);
float nanf(const char *);
long double nanl(const char *);





double nearbyint(double);
float nearbyintf(float);
long double nearbyintl(long double);





double nextafter(double, double);
float nextafterf(float, float);
long double nextafterl(long double, long double);





double nexttoward(double, long double);
float nexttowardf(float, long double);
long double nexttowardl(long double, long double);
# 498 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\math.h" 3
double pow(double, double);
__attribute__((nonreentrant)) float powf(float, float);
long double powl(long double, long double);





double remainder(double, double);
float remainderf(float, float);
long double remainderl(long double, long double);





double remquo(double, double, int *);
float remquof(float, float, int *);
long double remquol(long double, long double, int *);





double rint(double);
float rintf(float);
long double rintl(long double);





double round(double);
float roundf(float);
long double roundl(long double);





double scalbln(double, long);
float scalblnf(float, long);
long double scalblnl(long double, long);





double scalbn(double, int);
float scalbnf(float, int);
long double scalbnl(long double, int);





double sin(double);
float sinf(float);
long double sinl(long double);





double sinh(double);
float sinhf(float);
long double sinhl(long double);





double sqrt(double);
float sqrtf(float);
long double sqrtl(long double);





double tan(double);
float tanf(float);
long double tanl(long double);





double tanh(double);
float tanhf(float);
long double tanhl(long double);





double tgamma(double);
float tgammaf(float);
long double tgammal(long double);





double trunc(double);
float truncf(float);
long double truncl(long double);
# 631 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\math.h" 3
extern int signgam;

double j0(double);
double j1(double);
double jn(int, double);

double y0(double);
double y1(double);
double yn(int, double);
# 2 "src/util.c" 2

# 1 "src/../headers/util.h" 1
# 15 "src/../headers/util.h"
int itoa(int num, char * buf, int radix);
void dtoa(double num, char * buf, int radix);
# 3 "src/util.c" 2




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
        *(buf + i) = (num % radix) | 0x30;
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

    dpart = dpart * powf(10,2);

    itoa((int)dpart, buf + i + 1, 10);


}
