/* 
 * File:   Si7021.h
 * Author: jstpa
 *
 * Created on November 24, 2018, 11:14 AM
 */

#ifndef SI7021_H
#define	SI7021_H


void Si7021_init(void);
void Si7021_reset(void);
void Si7021_read_humidity(void);
void Si7021_read_temp(void);
double Si7021_avg_humidity(void);
double Si7021_avg_temp(void);
int Si7021_set_heater(char heat);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SI7021_H */

