/* 
 * File:   main.c
 * Author: jstpa
 *
 * Created on November 8, 2018, 6:21 PM
 */

#include <xc.h>
#include "../headers/mc_init.h"
#include "../headers/lcd.h"
#include "../headers/i2c_master.h"
#include "../headers/interrupt.h"
#include "../headers/uart.h"
#include "../headers/esp8266.h"
#include "../headers/util.h"
#include "../headers/Si7021.h"
#include "../headers/ph.h"

void wait() {
    int i, j;
    for(i = 0; i < 255; i++) {
        for(j = 0; j < 255; j++) {
            NOP();
        }
    }
}
void empty_rx_buf() {
    char c;
    while(!UART_can_rx()) {
        
    }
    while(UART_can_rx()) {
        c = UART_getc();
        if(c == '\n') {
            lcd_newline();
        } else if(c < 32 || c > 127) {
            // do nothing
        } else {
            lcd_putc(c);
        }
    }
    lcd_update();
}
/*
 * 
 */
int main() {
//    char c;
    char buffer[15];
    double ph;
    controller_init();
    interrupt_init();
    I2C_master_init();
    lcd_init();
    ph_init();
    lcd_clear();
    
    
    while(1) {
        ph = ph_read();
        dtoa(ph, buffer, 10);
        lcd_puts("pH: ");
        lcd_puts(buffer);
        lcd_newline();
        lcd_update();    
        __delay_ms(2000);
    }
    
    
    
    
    
   
}

