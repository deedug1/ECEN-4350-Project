#include <xc.h>
#include "../headers/ph.h"

// Required register bits
#define ANALOG_RIGHT_JUSTIFY    ADCON0bits.ADFM
#define ANALOG_CONVERT          ADCON0bits.GO
#define ANALOG_CLOCK_SELECT     ADCON0bits.ADCS
#define ANALOG_CHANNEL_SELECT   ADPCH
#define ANALOG_ON               ADCON0bits.ADON
#define RESULT_LOWER            ADRESL
#define RESULT_HIGHER           ADRESH

// Preprocessor constants
#define PH_READ_LIMIT           5

static double ph_reads[PH_READ_LIMIT];
void ph_init() {
    int i;
    ADCON0 = 0x94;
    for(i = 0; i < PH_READ_LIMIT; i++) {
        ph_read();
    }
}

double ptov(int ph) {
    double result;
    result = (double)ph / (double)310;
    result = result * -5.0;
    result = result + 19.25;
    return result;
}

double ph_avg() {
    int i;
    double avg = 0.0;
    for(i = 0; i < PH_READ_LIMIT; i++) {
        avg += ph_reads[i];
    }
    return avg / (double)PH_READ_LIMIT;
}

void ph_read() {
    static int i = 0;
    int result;
    ANALOG_CONVERT = 1;
    while(ANALOG_CONVERT);
    result = RESULT_LOWER;
    result += (RESULT_HIGHER << 8);
    ph_reads[i] = ptov(result);
    i = (i + 1) % PH_READ_LIMIT;
}