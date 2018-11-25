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
#include "../headers/stopwatch.h"

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
    stopwatch_init();
    lcd_clear();
    lcd_puts("Starting");
    lcd_newline();
    lcd_update();
    stopwatch_start(1);
    while(1) {
        if(stopwatch_is_stopped()){
            stopwatch_start(5);
            lcd_putc('.');
            lcd_update();
        }
    }
    
    
    
    
    
   
}

