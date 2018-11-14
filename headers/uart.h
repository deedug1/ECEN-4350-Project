/* 
 * File:   uart.h
 * Author: jstpa
 *
 * Created on November 12, 2018, 6:09 PM
 */

#ifndef UART_H
#define	UART_H

#define RX_INTE PIE3bits.RC1IE
#define TX_INTE PIE3bits.TX1IE

#define RX_INTF PIR3bits.RC1IF
#define TX_INTF PIR3bits.TX1IF

void UART_init();
void UART_RX_ISR();
void UART_TX_ISR();
void UART_write(char data);
char UART_read();
char UART_can_tx();
char UART_can_rx();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

