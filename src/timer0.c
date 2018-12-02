#include <xc.h>
#include "../headers/timer0.h"

// Module variables
static volatile int count = 0;
static volatile char read = 1;

void TIMER0_init() {
    // Setup ~7 second timer
    T0CON0 = 0x1F; // POST-SCALER 15
    T0CON1 = 0x46; // PRE-SCALER 32
}

void TIMER0_reset() {
    read = 1;
    count = 0;
}

int TIMER0_get_count() {
   read = 1;
   return count; 
}

char TIMER0_is_read() {
    return read;
}

void TIMER0_stop() {
    TIMER0_INTE = 0;
    T0CON0 &= 0x7F;
}
void TIMER0_start() {
    T0CON0 |= 0x80;
    TIMER0_INTE = 1;
}

void TIMER0_ISR() {
    TIMER0_INTF = 0;
    count++;
    read = 0;
}
