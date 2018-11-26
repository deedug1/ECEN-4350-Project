/* 
 * File:   main.c
 * Author: jstpa
 *
 * Created on November 8, 2018, 6:21 PM
 */

#include <xc.h>
#include <string.h>
#include "../headers/mc_init.h"
#include "../headers/lcd.h"
#include "../headers/esp8266.h"
#include "../headers/util.h"
#include "../headers/Si7021.h"
#include "../headers/ph.h"
#include "../headers/timer0.h"

#define TEMP_FIELD 3
#define HUMIDITY_FIELD 2
#define PH_FIELD 1
#define TEST_FIELD 4
#define UPDATES 5
int PORT = 80;
char * SSID = "test_ap";
char * PASS = "incredible14!";
char * IP = "api.thingspeak.com";


void connect_to_wifi(void);
void send_data_double(int field, double val); // FIX ME int -> double 
//void send_data_int(int field, int val);
/*
 * 
 */
int main() {
//    char c;
    int c = 0;
    double ph, temp, humidity;
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
            TIMER0_stop(); // Disable timer to do work
            c = TIMER0_get_count();
            // Open socket
            if(c >= UPDATES) { // Every ~2 minutes
                TIMER0_reset(); 
                
                // Process averages
                temp = Si7021_avg_temp();
                humidity = Si7021_avg_humidity();
                ph = ph_avg();
                
                // Send data
                send_data_double(TEMP_FIELD, temp);
                send_data_double(HUMIDITY_FIELD, humidity);
                send_data_double(PH_FIELD, ph);
                
                // Close socket
                
                
                // Update lcd
                lcd_newline();
                lcd_puts("DATA SENT");
                lcd_update();
                
                
            } else { // Every ~30 seconds
                ph_read();
                Si7021_read_temp();
                Si7021_read_humidity();
                lcd_newline();
                lcd_puts("DATA UPDATED");
                lcd_update();
            }
            TIMER0_start(); // Enable timer
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
    ESP8266_close_socket();
}