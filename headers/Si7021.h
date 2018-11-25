/* 
 * File:   Si7021.h
 * Author: jstpa
 *
 * Created on November 24, 2018, 11:14 AM
 */

#ifndef SI7021_H
#define	SI7021_H

#define SI7021_ADDR         0x40
#define CMD_RESET           0xFE
#define CMD_READ_HUMIDITY   0xF5
#define CMD_READ_TEMP       0xF3
#define CMD_SET_HEATER      0x51
#define CMD_READ_HEATER     0x11

void Si7021_init(void);
void Si7021_reset(void);
void Si7021_read_humidity(void);
void Si7021_read_temp(void);
int Si7021_avg_humidity(void);
int Si7021_avg_temp(void);
int Si7021_set_heater(char heat);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SI7021_H */

