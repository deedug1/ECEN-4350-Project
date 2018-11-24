#include <xc.h>
#include "../headers/i2c_master.h"
#include "../headers/Si7021.h"



#define SI7021_WRITE() I2C_master_write(Si7021_buf, 1, SI7021_ADDR)
#define SI7021_READ() I2C_master_read(Si7021_buf, 2, SI7021_ADDR)
#define SI7021_GET_CODE(A) A = Si7021_buf[1]; A += (Si7021_buf[0] << 8)

static char Si7021_buf[2];

int convert_humidity() {
    int result, rh_code;
    SI7021_GET_CODE(rh_code);
    result = (((long)125 * rh_code) >> 16) - 6;
    // Truncating as per data sheet
    if(result < 0) {
        return 0;
    } else if (result > 100) {
        return 100;
    } else {        
    return result;
    }
}

int convert_temp() {
    int result, temp_code;
    SI7021_GET_CODE(temp_code);
    result = (((long)176 * temp_code) >> 16) - 47;
    return result; 
}

void Si7021_reset() {
    Si7021_buf[0] = CMD_RESET;
    SI7021_WRITE();
}

int Si7021_read_humidity() {
    Si7021_buf[0] = CMD_READ_HUMIDITY;
    SI7021_WRITE();
    
    while(SI7021_READ() == RECEIVE_ERROR);
    
    return convert_humidity();
}

int Si7021_read_temp() {
    Si7021_buf[0] = CMD_READ_TEMP;
    SI7021_WRITE();
    
    while(SI7021_READ() == RECEIVE_ERROR);
    
    return convert_temp();
}

