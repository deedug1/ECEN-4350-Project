/* 
 * File:   main.c
 * Author: jstpa
 *
 * Created on November 8, 2018, 6:21 PM
 */

#include <stdio.h>
#include <xc.h>
#include "mc_init.h"
#include "lcd.h"
#include "i2c_master.h"
#include "interrupt.h"
#include "uart.h"

void wait() {
    int i, j;
    for(i = 0; i < 255; i++) {
        for(j = 0; j < 255; j++) {
            NOP();
        }
    }
}
/*
 * 
 */
int main(int argc, char** argv) {
    char i;
    controller_init();
    interrupt_init();
    I2C_master_init();
    UART_init();
//    while(1) {
//        I2C_master_write("Hello", 5, 0x3D);
//    }
    
    for(i = 0; i < 255; i++) {
        UART_write(i);
    }
    while(1) {
        // Program complete
        SLEEP();
    }
   
}

