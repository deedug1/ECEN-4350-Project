#include <xc.h>
#include "../headers/i2c_master.h"
#include "../headers/Si7021.h"

#define HUMIDITY_READ_LIMIT 5
#define TEMP_READ_LIMIT 5

#define SI7021_WRITE() I2C_master_write(Si7021_buf, 1, SI7021_ADDR)
#define SI7021_READ() I2C_master_read(Si7021_buf, 2, SI7021_ADDR)
#define SI7021_GET_CODE(A) A = Si7021_buf[1]; A += (Si7021_buf[0] << 8)

static char Si7021_buf[2];
static double  Si7021_temps[TEMP_READ_LIMIT];
static double  Si7021_humids[HUMIDITY_READ_LIMIT];
double convert_humidity() {
    int rh_code;
    double result;
    SI7021_GET_CODE(rh_code);
    result = ((125.0 * (double)rh_code) / 65536.0) - 6;
    // Truncating as per data sheet
    if(result < 0) {
        return 0.0;
    } else if (result > 100) {
        return 100.0;
    } else {        
        return result;
    }
}

double convert_temp() {
    int temp_code;
    double result;
    SI7021_GET_CODE(temp_code);
    result = ((176.0 * (double)temp_code) / 65536.0) - 47;
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
double Si7021_avg_humidity() {
    int i;
    double result = 0;
    for(i = 0; i < HUMIDITY_READ_LIMIT; i++) {
        result += Si7021_humids[i];
    }
    result = result / (double)HUMIDITY_READ_LIMIT;
    return result;
}
double Si7021_avg_temp() {
    int i;
    double result = 0;
    for(i = 0; i < TEMP_READ_LIMIT; i++) {
        result += Si7021_temps[i];
    }
    result = result / (double)TEMP_READ_LIMIT;
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

