#include <xc.h>


#define ANALOG_RIGHT_JUSTIFY ADCON0bits.ADFM
#define ANALOG_CONVERT ADCON0bits.GO
#define ANALOG_CLOCK_SELECT ADCON0bits.ADCS
#define ANALOG_CHANNEL_SELECT ADPCH
#define ANALOG_ON ADCON0bits.ADON
#define RESULT_LOWER ADRESL
#define RESULT_HIGHER ADRESH
#define PH_READS 8
static double ph_reads[PH_READS];
void ph_init() {
    ADCON0 = 0x94;
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
    for(i = 0; i < PH_READS; i++) {
        avg += ph_reads[i];
    }
    return avg / (double)PH_READS;
}
double ph_read() {
    int result, i;
    ANALOG_CONVERT = 1;
    for(i = 0; i < PH_READS; i++) {
        while(ANALOG_CONVERT);
    
        result = RESULT_LOWER;
        result += (RESULT_HIGHER << 8);
        ph_reads[i] = ptov(result);
    }
    
    return ph_avg();
}