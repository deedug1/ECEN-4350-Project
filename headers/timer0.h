/* 
 * File:   timer0.h
 * Author: jstpa
 *
 * Created on November 25, 2018, 3:04 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

#define TIMER0_INTE PIE0bits.TMR0IE
#define TIMER0_INTF PIR0bits.TMR0IF

void TIMER0_init(void);
void TIMER0_ISR(void);
void TIMER0_reset(void);
int TIMER0_get_count(void);
char TIMER0_is_read(void);
void TIMER0_stop(void);
void TIMER0_start(void);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TIMER0_H */

