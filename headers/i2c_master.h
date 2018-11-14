/* 
 * File:   i2c_master.h
 * Author: jstpa
 *
 * Created on October 29, 2018, 12:51 PM
 */

#ifndef I2C_MASTER_H
#define	I2C_MASTER_H

#define I2C_INTE PIE3bits.SSP1IE
#define I2C_INTF SSP1IF
typedef enum {
    SUCCESS, SEND_ERROR, RECEIVE_ERROR, PENDING
}I2C_master_result;
void I2C_master_init(void);
void I2C_MASTER_ISR(void);
I2C_master_result I2C_master_write(char * data, int length, char address);
I2C_master_result I2C_master_read(char * buffer, int length, char address);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* I2C_HEADER_H */

