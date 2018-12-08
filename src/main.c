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
void send_data_double(double ph, double temp, double humid); // FIX ME int -> double 
//void send_data_int(int field, int val);
/*
 * 
 */
int main() {
//    char c;
    int c = 0;
    double ph, humid, temp;
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
            c = TIMER0_get_count();
            TIMER0_stop(); 
            if( c % 5 == 0) {
                // Calculate results
                ph = ph_avg();
                humid = Si7021_avg_humidity();
                temp = Si7021_avg_temp();

                // Send data
                send_data_double(ph, temp, humid);

                // Update lcd
                lcd_newline();
                lcd_puts("DATA SENT");
                lcd_update();
                
            } else {
                // Update all values
                ph_read();
                Si7021_read_temp();
                Si7021_read_humidity();
                lcd_newline();
                lcd_puts("DATA UPDATED");
                lcd_update();
                
            }
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

void send_data_double(double ph, double temp, double humid) {
    static char strbuf[100];
    char numbuf[10];
    strbuf[0] = '\0';
    // Get field number
    itoa(PH_FIELD, numbuf, 10);
    strcat(strbuf, "GET /update?api_key=ONF84FNQ1XDZB5KH&field");
    strcat(strbuf, numbuf);
    
    // Send ph value
    strcat(strbuf, "=");
    dtoa(ph, numbuf, 10);
    strcat(strbuf, numbuf);
    strcat(strbuf, "&");
    
    // Send humid value
    itoa(HUMIDITY_FIELD, numbuf, 10);
    strcat(strbuf, "field");
    strcat(strbuf, numbuf);
    dtoa(humid, numbuf, 10);
    strcat(strbuf, "=");
    strcat(strbuf, numbuf);
    strcat(strbuf, "&");
    
    // Send tmpe value
    itoa(TEMP_FIELD, numbuf, 10);
    strcat(strbuf, "field");
    strcat(strbuf, numbuf);
    dtoa(temp, numbuf, 10);
    strcat(strbuf, "=");
    strcat(strbuf, numbuf);
    strcat(strbuf, "\r\n\r\n");
    
    // Transmit data
    // NOTE SOCKET MUST BE OPEN
    
    ESP8266_open_socket(TCP, "api.thingspeak.com", 80);
    ESP8266_send_data(strbuf);
//    ESP8266_close_socket();
    // delay 5 second
}