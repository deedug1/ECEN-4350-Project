#include <xc.h>
#include <string.h>
#include "../headers/util.h"
#include "../headers/esp8266.h"
#include "../headers/uart.h"
#include "../headers/lcd.h"
#include "../headers/stopwatch.h"


#define DEBUG 1


#define ESP8266_SEND_STRING(A) UART_putc('\"');UART_puts(A);UART_putc('\"')
#define ESP8266_COMMA() UART_putc(',')
#define ESP8266_COMMAND_END() UART_puts("\r\n")
#define ESP8266_LINE_LIMIT 32
#define ESP8266_MAX_TIMEOUT 10
static char is_connected = 0;
char * SOCKETS[] = {"TCP", "UDP", "SSL"};
char ESP8266_lookfor(const char * str, int timeout);

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
//    if(is_connected) {
//        return;
//    }
    UART_puts(ATCWJAP);
    ESP8266_SEND_STRING(name);
    ESP8266_COMMA();
    ESP8266_SEND_STRING(pass);
    ESP8266_COMMAND_END();
    while(!ESP8266_lookfor("WIFI GOT IP", 10));
    while(!ESP8266_lookfor("OK", 10));
    is_connected = 1;
//    is_connected = ESP8266_responseOK();
}

void ESP8266_open_socket(ESP8266_socket_type type, char * ip, int port) {
    char buffer[10];
    itoa(port, buffer, 10);
    UART_puts(ATCIPSTART);
    ESP8266_SEND_STRING(SOCKETS[type]);
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
    ESP8266_lookfor(">", ESP8266_MAX_TIMEOUT);
    UART_puts(data);
    ESP8266_lookfor("SEND OK", ESP8266_MAX_TIMEOUT);

}
void ESP8266_close_socket(){
    UART_puts(ATCIPCLOSE);
    ESP8266_COMMAND_END();
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
            if(i >= ESP8266_LINE_LIMIT) { // Oh no! Buffer overflow!
                i = 0;
            }
        }
    }
    if(found && DEBUG) {
        lcd_newline();
        lcd_puts(buffer);
        lcd_update();
    }
    return found;
}