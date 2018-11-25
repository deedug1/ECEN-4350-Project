/* 
 * File:   mc_init.h
 * Author: jstpa
 *
 * Created on October 10, 2018, 1:48 PM
 */

#ifndef MC_INIT_H
#define	MC_INIT_H

#define LAT_DEFAULT     0x00
#define ANSEL_DEFAULT   0xFF
#define WPU_DEFAULT     0x00
#define TRIS_DEFAULT    0xFF
#define ODCON_DEFAULT   0x00
#define SLRCON_DEFAULT  0xFF

void pps_init(void);
void port_init(void);
void controller_init(void);
void oscillator_init(void);
void system_init(void);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MC_INIT_H */

