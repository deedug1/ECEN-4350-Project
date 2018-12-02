#include <xc.h>
#include <string.h>
#include "../headers/util.h"
#include "../headers/esp8266.h"
#include "../headers/uart.h"
#include "../headers/lcd.h"
#include "../headers/stopwatch.h"

// Helper macros
#define ESP8266_SEND_STRING(A) UART_putc('\"');UART_puts(A);UART_putc('\"')
#define ESP8266_COMMA() UART_putc(',')
#define ESP8266_COMMAND_END() UART_puts("\r\n")

// AT-Commands
#define ATCWMODE        "AT+CWMODE_CUR=3"   // Set as station / soft AP
#define ATCIPMODE_ON    "AT+CIPMODE=1"      // Set transparent transmission mode
#define ATCIPMODE_OFF   "AT+CIPMODE=0"      // Disable transparent transmission mode
#define ATCIPMUX        "AT+CIPMUX=0"       // Set single connection mode
#define ATCWJAP         "AT+CWJAP_CUR="     // Join access point
#define ATCIPSTART      "AT+CIPSTART="      // Start socket /* NOTE: '0' is for link is invalid bug */
#define ATCIPSEND       "AT+CIPSEND="
#define ATCIPSENDT      "AT+CIPSEND"  
#define ATCIPCLOSE      "AT+CIPClOSE"       // Close socket 
#define ATRESET         "AT+RST"            // Resets the module    

// Preprocessor constants
#define ESP8266_LINE_LIMIT 32
#define ESP8266_MAX_TIMEOUT 10

// Debug
#define DEBUG 1

// Helper functions
char ESP8266_lookfor(const char * str, int timeout);

// Constants
char * SOCKET_TYPES[] = {"TCP", "UDP", "SSL"};

void ESP8266_query(void) {
    UART_puts("AT+CIFSR");
    ESP8266_COMMAND_END();
    ESP8266_lookfor("OK", ESP8266_MAX_TIMEOUT);
}
void ESP8266_init(void) {
    UART_puts("ATE0");
    ESP8266_COMMAND_END();
    ESP8266_lookfor("OK", ESP8266_MAX_TIMEOUT);
    
    UART_puts(ATCWMODE);
    ESP8266_COMMAND_END();
    ESP8266_lookfor("OK", ESP8266_MAX_TIMEOUT);
    
    UART_puts(ATCIPMUX);
    ESP8266_COMMAND_END();
    ESP8266_lookfor("OK", ESP8266_MAX_TIMEOUT);
}
void ESP8266_reset() {
    UART_puts(ATRESET);
    ESP8266_COMMAND_END();
    
    ESP8266_lookfor("ready", ESP8266_MAX_TIMEOUT);
}
void ESP8266_connect(char * name, char * pass) {
    UART_puts(ATCWJAP);
    ESP8266_SEND_STRING(name);
    ESP8266_COMMA();
    ESP8266_SEND_STRING(pass);
    ESP8266_COMMAND_END();
    
    while(!ESP8266_lookfor("WIFI GOT IP", 1)); // Must wait
    while(!ESP8266_lookfor("OK", 1)); // Must wait
}

void ESP8266_open_socket(ESP8266_socket_type type, char * ip, int port) {
    char buffer[10];
    itoa(port, buffer, 10);
    UART_puts(ATCIPSTART);
    ESP8266_SEND_STRING(SOCKET_TYPES[type]);
    ESP8266_COMMA();
    ESP8266_SEND_STRING(ip);
    ESP8266_COMMA();
    UART_puts(buffer);
    ESP8266_COMMAND_END();
    
    ESP8266_lookfor("OK", ESP8266_MAX_TIMEOUT);
}

void ESP8266_send_data(char * data) {
    char buffer[10];
    int len = strlen(data);
    itoa(len, buffer, 10);
    UART_puts(ATCIPSEND);
    UART_puts(buffer);
    ESP8266_COMMAND_END();
    ESP8266_lookfor("OK", ESP8266_MAX_TIMEOUT);
    UART_puts(data);
    ESP8266_lookfor("SEND OK", ESP8266_MAX_TIMEOUT);

}

void ESP8266_close_socket(){
    UART_puts(ATCIPCLOSE);
    ESP8266_COMMAND_END();
    
    ESP8266_lookfor("OK", ESP8266_MAX_TIMEOUT);
}
char ESP8266_lookfor(const char * str, int timeout) {
    char c = 0, found = 0;
    char buffer[ESP8266_LINE_LIMIT];
    int i = 0;
    
    stopwatch_start(timeout);
    while(!found && stopwatch_is_started()) {
        if(UART_can_rx()) {
            c = UART_getc();
            // End line
            if( c == '\r' || c == '\n') {
                buffer[i] = '\0';
                found = strcmp(buffer, str) == 0;
                i = 0;
            } else {
                buffer[i] = c;
                i++;
            }
            // Stop buffer overflow
            if(i >= ESP8266_LINE_LIMIT) { 
                i = 0;
            }
        }
    }
    
#if DEBUG
    if(found) {
        lcd_newline();
        lcd_puts(buffer);
        lcd_update();
    }
#endif
    
    stopwatch_stop();
    return found;
}