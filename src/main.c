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


int PORT = 80;
char * SSID = "test_ap";
char * PASS = "incredible14!";
char * IP = "api.thingspeak.com";
char * DATA = "GET /update?api_key=ONF84FNQ1XDZB5KH&field1=3.14\r\n\r\n";
/*
 * 
 */
int main() {
//    char c;
    controller_init();
    interrupt_init();
    I2C_master_init();
    stopwatch_init();
    UART_init();
    lcd_init();
    lcd_clear();
    lcd_puts("Starting");
    lcd_newline();
    lcd_update();
    
    
    // BEGIN WiFi
    ESP8266_reset();
    
    ESP8266_init();
    
    ESP8266_connect(SSID, PASS);
    ESP8266_query();
    ESP8266_open_socket(TCP, IP, PORT);
   
    ESP8266_send_data(DATA);
    ESP8266_close_socket();
    
    
    while(1) {
        // END 
    }
    
    
    
    
    
   
}

