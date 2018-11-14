/* 
 * File:   uart.c
 * Author: jstpa
 *
 * Created on November 12, 2018, 6:08 PM
 */

#include <xc.h>
#include "../headers/uart.h"
#define UART_RECEIVE(A) (A = RC1REG) 
#define UART_SEND(A) (TX1REG = A)
#define UART_BUFFER_SIZE 8
typedef struct {
    char buffer[UART_BUFFER_SIZE];
    int size;
    int head;
    int tail;
} UART_buf;

static volatile UART_buf RX_buf;
static volatile UART_buf TX_buf;
void UART_init() {
    // Disable interrupts
    RX_INTE = 0;
    TX_INTE = 0;
    
    // No auto-baud, 16bit BRG
    BAUD1CON = 0x08;
    // Receive enable; Peripheral enable
    RC1STA = 0x90;
    // Transmit enable; High Baud rate
    TX1STA = 0x24;
    
    /* 
     * Fosc = 16 Mhz, Baudrate = 115200
     * SP1BRG = 16 Mhz /[4(115200 + 1)] = 34
     * ERROR = ((16 Mhz / [4(34 + 1)]) - 115200) / 115200 = -0.008  
     */
    SP1BRGH = 0x00;
    // 34
    SP1BRGL = 0x22;
    
    // initialize the buffers
    RX_buf.size = 0;
    RX_buf.tail = 0;
    RX_buf.head = 0;
    
    TX_buf.size = 0;
    TX_buf.tail = 0;
    TX_buf.head = 0;
    // Enable interrupts
    RX_INTE = 1;
    
}
void UART_RX_ISR() {
    
    // Buffer overwrites are ignored
    UART_RECEIVE(RX_buf.buffer[RX_buf.head++]);
    RX_buf.size++;
    // Wrap
    if(RX_buf.head >= UART_BUFFER_SIZE) {
        RX_buf.head = 0;
    }
}

void UART_TX_ISR() {
    if(TX_buf.size != 0) {
        // Transmit data in buffer
        UART_SEND(TX_buf.buffer[TX_buf.tail++]);
        TX_buf.size--;
        // Wrap
        if(TX_buf.tail >= UART_BUFFER_SIZE) {
            TX_buf.tail = 0;
        }
    } else {
        // Transmit complete turn off the interrupt
        TX_INTE = 0;
    }
}
void UART_putc(char data) {
    while(TX_buf.size >= UART_BUFFER_SIZE) {
        // Wait for room in TX_buf
    }
    // If nothing has been transmitted yet.
    if(TX_INTE == 0){
        UART_SEND(data);
    } else {
        // Add a byte to the queue
        TX_INTE = 0; // Prevent ISR from modifying the buffer
        TX_buf.buffer[TX_buf.head++] = data;
        TX_buf.size++;
        // Wrap
        if(TX_buf.head >= UART_BUFFER_SIZE) {
            TX_buf.head = 0;
        }
    }
    TX_INTE = 1;
}
void UART_puts(char * data, int len) {
    
    while(len --> 0) {
        UART_putc(*data);
        data++;
    }
}

char UART_getc() {
    char data = 0;
    
    // Wait for room in RX_buf
    while(RX_buf.size <= 0) {
        // Wait for byte in RX_buf
    }
    RX_INTE = 0; // Prevent ISR from modifying the buffer
    data = RX_buf.buffer[RX_buf.tail++];
    RX_buf.size--;
    // Wrap
    if(RX_buf.tail >= UART_BUFFER_SIZE) {
        RX_buf.head = 0;
    }
    RX_INTE = 1;
    return data;
}
void UART_gets(char * buf, int len) {
    while(len --> 0) {
        *buf = UART_getc();
        buf++;
    }
}
char UART_can_rx() {
    return RX_buf.size > 0;
}
char UART_can_tx() {
    return TX_buf.size < UART_BUFFER_SIZE;
}