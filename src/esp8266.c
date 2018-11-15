#include <xc.h>
#include "../headers/esp8266.h"
#include "../headers/uart.h"



static char is_connected = 0;

void ESP8266_init(void) {
    
}

void ESP8266_connect(char * name, char * pass) {
    if(is_connected) {
        return;
    }
    UART_puts(ATCWJAP);
    UART_putc('\"');
    UART_puts(name);
    UART_putc('\"');
    UART_putc(',');
    UART_putc('\"');
    UART_puts(pass);
    UART_putc('\"');
    UART_puts(COMMAND_END);
    is_connected = ESP8266_responseOK();
}

void ESP8266_open_socket(int socket_type, char * ip, int port) {
    
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