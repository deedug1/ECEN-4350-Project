#include <xc.h>
#include <string.h>
#include "../headers/util.h"
#include "../headers/esp8266.h"
#include "../headers/uart.h"
#include "../headers/lcd.h"


#define ESP8266_SEND_STRING(A) UART_putc('\"');UART_puts(A);UART_putc('\"')
#define ESP8266_COMMA UART_putc(',')
#define ESP8266_COMMAND_END UART_puts("\r\n")
static char is_connected = 0;
char * SOCKETS[] = {"TCP", "UDP"};
char ESP8266_waitfor(const char * str);

void ESP8266_query(void) {
    UART_puts("AT+CWMODE?");
    ESP8266_COMMAND_END;
    ESP8266_waitfor("OK");
    UART_puts("AT+CIPMUX?");
    ESP8266_COMMAND_END;
    ESP8266_waitfor("OK");
    UART_puts("AT+CIFSR");
    ESP8266_COMMAND_END;
    ESP8266_waitfor("OK");
}
void ESP8266_init(void) {
    UART_puts("ATE0");
    ESP8266_COMMAND_END;
    ESP8266_waitfor("OK");
    
    UART_puts(ATCWMODE);
    ESP8266_COMMAND_END;
    ESP8266_waitfor("OK");
    
    UART_puts(ATCIPMUX);
    ESP8266_COMMAND_END;
    ESP8266_waitfor("OK");
}
void ESP8266_reset() {
    UART_puts(ATRESET);
    ESP8266_COMMAND_END;
    ESP8266_waitfor("ready");
}
void ESP8266_connect(char * name, char * pass) {
//    if(is_connected) {
//        return;
//    }
    UART_puts(ATCWJAP);
    ESP8266_SEND_STRING(name);
    ESP8266_COMMA;
    ESP8266_SEND_STRING(pass);
    ESP8266_COMMAND_END;
    ESP8266_waitfor("WIFI GOT IP");
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
    ESP8266_waitfor("OK");
}

void ESP8266_send_data(char * data) {
    char buffer[10];
    int len = strlen(data);
    itoa(len, buffer, 10);
    UART_puts(ATCIPSEND);
    UART_puts(buffer);
    
    ESP8266_COMMAND_END;
//    ESP8266_waitfor(">");
    // Send actual transmit data
    UART_puts(data);
//    UART_getc();
}
void ESP8266_close_socket(){
    UART_puts(ATCIPCLOSE);
    ESP8266_COMMAND_END;
}
char ESP8266_waitfor(const char * str) {
    char buffer[64];
    char c;
    int i = 0;
    while(!UART_can_rx());
    do {
        i = 0;
        buffer[0] = '\0';
        while((c = UART_getc()) != '\n') {
            if(c != '\r') {
                buffer[i++] = c;
            }
            if(i >= 64) {
                i = 0;
            }
        }
        buffer[i] = '\0';
    } while(strcmp(buffer, str) != 0);
    lcd_puts(buffer);
    lcd_newline();
    lcd_update();
    return 0;
}