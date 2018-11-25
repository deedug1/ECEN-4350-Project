#include <xc.h>
#include "../headers/i2c_master.h"
#include "../headers/Si7021.h"

#define HUMIDITY_READ_LIMIT 5
#define TEMP_READ_LIMIT 5

#define SI7021_WRITE() I2C_master_write(Si7021_buf, 1, SI7021_ADDR)
#define SI7021_READ() I2C_master_read(Si7021_buf, 2, SI7021_ADDR)
#define SI7021_GET_CODE(A) A = Si7021_buf[1]; A += (Si7021_buf[0] << 8)

static char Si7021_buf[2];
static int  Si7021_temps[TEMP_READ_LIMIT];
static int  Si7021_humids[HUMIDITY_READ_LIMIT];
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
void Si7021_init() {
    int i;
    // Populate buffers so that averages aren't garbage
    for(i = 0; i < TEMP_READ_LIMIT; i++) {
        Si7021_read_temp();
    }
    for(i = 0; i < HUMIDITY_READ_LIMIT; i++) {
        Si7021_read_humidity();
    }
}
int Si7021_avg_humidity() {
    int i;
    int result = 0;
    for(i = 0; i < HUMIDITY_READ_LIMIT; i++) {
        result += Si7021_humids[i];
    }
    result = result / HUMIDITY_READ_LIMIT;
    return result;
}
int Si7021_avg_temp() {
    int i;
    int result = 0;
    for(i = 0; i < TEMP_READ_LIMIT; i++) {
        result += Si7021_temps[i];
    }
    result = result / TEMP_READ_LIMIT;
    return result;
}
void Si7021_reset() {
    Si7021_buf[0] = CMD_RESET;
    SI7021_WRITE();
}

void Si7021_read_humidity() {
    static int i = 0;
    Si7021_buf[0] = CMD_READ_HUMIDITY;
    SI7021_WRITE();
    
    while(SI7021_READ() == RECEIVE_ERROR);
    
    Si7021_humids[i] = convert_humidity();
    i = (i + 1) % HUMIDITY_READ_LIMIT;
}

void Si7021_read_temp() {
    static int i = 0;
    Si7021_buf[0] = CMD_READ_TEMP;
    SI7021_WRITE();
    
    while(SI7021_READ() == RECEIVE_ERROR);
    
    Si7021_temps[i] = convert_temp();
    i = (i + 1) % TEMP_READ_LIMIT;
}

