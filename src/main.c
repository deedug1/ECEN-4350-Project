/* 
 * File:   main.c
 * Author: jstpa
 *
 * Created on November 8, 2018, 6:21 PM
 */

#include <xc.h>
#include <string.h>
#include "../headers/mc_init.h"
#include "../headers/uart.h"
#include "../headers/lcd.h"
#include "../headers/esp8266.h"
#include "../headers/util.h"
#include "../headers/Si7021.h"
#include "../headers/ph.h"
#include "../headers/timer0.h"
#include "../headers/stopwatch.h"

#define TEMP_FIELD 3
#define HUMIDITY_FIELD 2
#define PH_FIELD 1
#define TEST_FIELD 4
#define UPDATES 5
#define types 3
int PORT = 80;
char * SSID = "test_ap";
char * PASS = "incredible14!";
char * IP = "api.thingspeak.com";

char * labels[] = {"PH", "HUMIDITY", "TEMP"};
void connect_to_wifi(void);
void send_data_double(int field, double val); // FIX ME int -> double 
//void send_data_int(int field, int val);
/*
 * 
 */
int main() {
//    char c;
    int c = 0;
    double result;
    system_init();
    lcd_init();
    lcd_clear();
    lcd_puts("Starting");
    lcd_newline();
    lcd_update();
    
    // Populate buffers
    Si7021_init();
    ph_init();
    
    // finalize system setup
    connect_to_wifi();
    TIMER0_start();
    
    while(1) {
        // END 
        if(!TIMER0_is_read()) {
            // Disable timer to do work
            TIMER0_stop(); 
            c = TIMER0_get_count() % 3;
           
            // Calculate one of the types
            switch(c) {
                case 0:
                    result = ph_avg();
                    break;
                case 1:
                    result = Si7021_avg_humidity();
                    break;
                case 2:
                    result = Si7021_avg_temp();
                    break;
                default:
                    result = ph_avg();
                    c = 0;
            }
            
            // Send data
            send_data_double(c + 1, result);
            
            // Update lcd
            lcd_newline();
            lcd_puts(labels[c]);
            lcd_puts(" DATA SENT");
            lcd_update();

            // Update all values
            ph_read();
            Si7021_read_temp();
            Si7021_read_humidity();
            
            // Enable timer
            TIMER0_start(); 
        }
    }
    
    
}

void connect_to_wifi() {
    ESP8266_reset();
    ESP8266_init();
    ESP8266_connect(SSID, PASS);
}

//void send_data_int(int field, int val) {
//    static char strbuf[60];
//    char numbuf[10];
//    strbuf[0] = '\0';
//    // Get field number
//    itoa(field, numbuf, 10);
//    strcat(strbuf, "GET /update?api_key=ONF84FNQ1XDZB5KH&field");
//    strcat(strbuf, numbuf);
//    
//    // Get send value
//    strcat(strbuf, "=");
//    itoa(val, numbuf, 10);
//    strcat(strbuf, numbuf);
//    strcat(strbuf, "\r\n\r\n");
//    
//    // Transmit data
//    // NOTE SOCKET MUST BE OPEN
//    ESP8266_open_socket(TCP, "api.thingspeak.com", 80);
//    ESP8266_send_data(strbuf);
//    ESP8266_close_socket();
//}

void send_data_double(int field, double val) {
    static char strbuf[60];
    char numbuf[10];
    strbuf[0] = '\0';
    // Get field number
    itoa(field, numbuf, 10);
    strcat(strbuf, "GET /update?api_key=ONF84FNQ1XDZB5KH&field");
    strcat(strbuf, numbuf);
    
    // Get send value
    strcat(strbuf, "=");
    dtoa(val, numbuf, 10);
    strcat(strbuf, numbuf);
    strcat(strbuf, "\r\n\r\n");
    
    // Transmit data
    // NOTE SOCKET MUST BE OPEN
    ESP8266_open_socket(TCP, "api.thingspeak.com", 80);
    ESP8266_send_data(strbuf);
//    ESP8266_close_socket();
    // delay 5 second
}