/* 
 * File:   stopwatch.h
 * Author: jstpa
 *
 * Created on November 24, 2018, 10:12 PM
 */

#ifndef STOPWATCH_H
#define	STOPWATCH_H

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

