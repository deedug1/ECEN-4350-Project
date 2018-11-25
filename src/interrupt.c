#include <xc.h>
#include "../headers/i2c_master.h"
#include "../headers/uart.h"
#include "../headers/stopwatch.h"

void interrupt_init() {
    INTCONbits.IPEN = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}
void __interrupt() MAIN_ISR() {
   
    if(INTCONbits.PEIE == 1) {
        if(I2C_INTE == 1 && I2C_INTF == 1) {
            I2C_MASTER_ISR();
        } else if(RX_INTE == 1 && RX_INTF == 1) {
            UART_RX_ISR();
        } else if(TX_INTE == 1 && TX_INTF == 1) {
            UART_TX_ISR();
        } else if(STOPWATCH_INTE == 1 && STOPWATCH_INTF == 1) {
            STOPWATCH_ISR();
        } else {
            // Unhandled Interrupt
        }
    }
}