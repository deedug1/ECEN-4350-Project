#include <xc.h>
#include <string.h>
#include "../headers/util.h"
#include "../headers/esp8266.h"
#include "../headers/uart.h"


#define ESP8266_SEND_STRING(A) UART_putc('\"');UART_puts(A);UART_putc('\"')
#define ESP8266_COMMA UART_putc(',')
#define ESP8266_COMMAND_END UART_puts("\r\n")
static char is_connected = 0;
char * SOCKETS[] = {"TCP", "UDP"};
void ESP8266_init(void) {
    UART_puts(ATCWMODE);
    UART_putc('1');
    ESP8266_COMMAND_END;
}

void ESP8266_connect(char * name, char * pass) {
    if(is_connected) {
        return;
    }
    UART_puts(ATCWJAP);
    ESP8266_SEND_STRING(name);
    ESP8266_COMMA;
    ESP8266_SEND_STRING(pass);
    ESP8266_COMMAND_END;
    is_connected = 1;
//    is_connected = ESP8266_responseOK();
}

void ESP8266_open_socket(ESP8266_socket_type type, char * ip, int port) {
    char buffer[10];
    itoa(port, buffer, 10);
    UART_puts(ATCIPSTART);
    ESP8266_SEND_STRING(SOCKETS[type]);
    ESP8266_COMMA;
    ESP8266_SEND_STRING(ip);
    ESP8266_COMMA;
    UART_puts(buffer);
    ESP8266_COMMAND_END;
}

void ESP8266_send_data(char * data) {
    char buffer[10];
    int len = strlen(data);
    itoa(len, buffer, 10);
    UART_puts(ATCIPSEND);
    UART_puts(buffer);
    ESP8266_COMMAND_END;
    // Send actual transmit data
    UART_puts(data);
    UART_putc('\n');
}
void ESP8266_close_socket(){
    UART_puts(ATCIPCLOSE);
    ESP8266_COMMAND_END;
}
char ESP8266_responseOK() {
    while(UART_can_rx()) {
        if(UART_getc() == 'O') {
            if(UART_getc() == 'K') {
                return 1;
            }
        }
    }
    return 0;
}