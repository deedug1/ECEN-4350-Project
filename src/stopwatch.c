#include <xc.h>
#include "../headers/stopwatch.h"


typedef struct {
    char started;
    int time;
} stopwatch;

static volatile stopwatch global_stopwatch;
void STOPWATCH_ISR() {
    // Stop stopwatch
    STOPWATCH_INTF = 0;
    global_stopwatch.started = 0;
    STOPWATCH_CON &= 0x7F; // Turn off stopwatch
    STOPWATCH_CMP = 0;
    STOPWATCH_INTE = 0;
}
void stopwatch_init() {
    STOPWATCH_CON = 0x7E; // POST-SCALER = 15; PRE-SCALER = 128
    STOPWATCH_HLT = 0x00; // No Hardware limiting; Free running mode;
    STOPWATCH_CS =  0x05; // Clock select (31250);
    STOPWATCH_RST = 0x00; // No reset;
}
void stopwatch_start(int seconds) {
    char cmp = 0;
    if(global_stopwatch.started) {
        return; // Timer already started do not restart
    }
    // Calculate tmr register compare value
    cmp = (char)((seconds * 31250) / 1920); // t * 31250 / (128 * 15)
    STOPWATCH_CMP = cmp;
    // Set stopwatch values
    global_stopwatch.time = seconds;
    global_stopwatch.started = 1;
    // Turn on stopwatch
    STOPWATCH_INTE = 1;
    STOPWATCH_CON |= 0x80; 
}
void stopwatch_stop() {
    STOPWATCH_INTE = 0;
    STOPWATCH_CON &= 0x7F;
    global_stopwatch.started = 0;
}
int stopwatch_get_time() {
    return global_stopwatch.time;
}
char stopwatch_is_started() {
    return global_stopwatch.started;
}
char stopwatch_is_stopped() {
    return !global_stopwatch.started;
}