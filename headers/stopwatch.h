/* 
 * File:   stopwatch.h
 * Author: jstpa
 *
 * Created on November 24, 2018, 10:12 PM
 */

#ifndef STOPWATCH_H
#define	STOPWATCH_H

#define STOPWATCH_INTF PIR4bits.TMR2IF
#define STOPWATCH_INTE PIE4bits.TMR2IE
#define STOPWATCH_CON T2CON
#define STOPWATCH_CMP T2PR
#define STOPWATCH_HLT T2HLT
#define STOPWATCH_CS T2CLKCON
#define STOPWATCH_RST T2RST

void stopwatch_init(void);
void stopwatch_start(int seconds);
void stopwatch_stop(void);
char stopwatch_is_stopped(void);
char stopwatch_is_started(void);
int stopwatch_get_time(void);
void STOPWATCH_ISR(void);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* STOPWATCH_H */

