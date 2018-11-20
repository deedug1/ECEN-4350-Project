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

char * garbage = "GET /update?api_key=ONF84FNQ1XDZB5KH&field1=21/r/n/r/n";
static char should_send = 0;
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
    controller_init();
    interrupt_init();
    I2C_master_init();
    UART_init();
    lcd_init();
    
     lcd_clear();
//     Begin WIFI
    ESP8266_reset();
    lcd_puts("RESET");
    lcd_newline();
    lcd_update();
    ESP8266_init();
    lcd_puts("INIT");
    lcd_newline();
    lcd_update();
    ESP8266_connect("test_ap", "incredible14!");
    lcd_puts("CONNECT");
    lcd_newline();
    lcd_update();
    ESP8266_open_socket(TCP, "api.thingspeak.com", 80);
    lcd_puts("SOCKET");
    lcd_newline();
    lcd_update();
    ESP8266_send_data(garbage);
    ESP8266_close_socket();
    while(1) {

    }
   
}

