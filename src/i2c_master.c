#include <xc.h>
#include "../headers/i2c_master.h"

#define START_ENABLE SSP1CON2bits.SEN
#define STOP_ENABLE  SSP1CON2bits.PEN
#define RECEIVE_ENABLE SSP1CON2bits.RCEN
#define ACKNOWLEDGE_STATUS SSP1CON2bits.ACKSTAT
#define ACKNOWLEDGE_ENABLE SSP1CON2bits.ACKEN
#define ACKNOWLEDGE_DATA SSP1CON2bits.ACKDT

#define SEND(a) (SSP1BUF = a)
#define RECEIVE(a) (a = SSP1BUF)
#define I2C_MASTER_BAUD 0x21

typedef enum {
    IDLE, SEND_ADDRESS, ACKNOWLEDGE_ADDR, SEND_DATA, RECEIVE_DATA, ACKNOWLEDGE_RECV, STOPPED
}I2C_master_status;

typedef struct {
    char * data;
    int length;
    char address;
    I2C_master_result result;
} I2C_transmit_data;

static volatile I2C_transmit_data current_packet;
static volatile I2C_master_status I2C_status;

void I2C_master_init() {
    SSP1MSK = 0x00; // Not used in Master mode
    
    SSP1ADD = I2C_MASTER_BAUD;
    
    SSP1STAT = 0x80; // No slew rate control
    
    SSP1CON3 = 0x00; // Not used in Master mode
    
    SSP1CON2 = 0x00; // All status bits
    
    SSP1CON1 = 0x28; // Enable MSSP and set to I2C Master mode
    
    // Enable interrupts
    SSP1IF = 0;
    PIE3bits.SSP1IE = 1;
}
void I2C_stop(I2C_master_result result) {
    current_packet.result = result;
    current_packet.length = 0;
    STOP_ENABLE = 1;
    I2C_status = STOP;
}
void I2C_wait() {
    while(current_packet.result == PENDING) {
        // WAIT FOR XFER COMPLETE
    }
    while(I2C_status != IDLE) {
        // WAIT FOR STOP COMPLETE
    }
}
void I2C_MASTER_ISR() {
    static int xfer_count = 0;
    
    SSP1IF = 0;
    switch(I2C_status) {
        case IDLE:
            if(current_packet.length != 0) {
                // Start transmission
                xfer_count = 0;
                START_ENABLE = 1;
                I2C_status = SEND_ADDRESS;
            }
            break;
        case SEND_ADDRESS:
            SEND(current_packet.address);
            if(current_packet.address & 0x1) {
                // Read; check if a device is there
               I2C_status = ACKNOWLEDGE_ADDR; 
            } else {
                // Write; start sending bits
               I2C_status = SEND_DATA;
            }
            break;
        case ACKNOWLEDGE_ADDR:
            if(ACKNOWLEDGE_STATUS) {
                // No device acknowledge send STOP
                ACKNOWLEDGE_STATUS = 0;
                I2C_stop(RECEIVE_ERROR);
            } else {
                RECEIVE_ENABLE = 1;
                I2C_status = ACKNOWLEDGE_RECV;
            }
            break;
        case SEND_DATA:
            if(ACKNOWLEDGE_STATUS) {
                // No device acknowledge send STOP
                ACKNOWLEDGE_STATUS = 0;
                I2C_stop(SEND_ERROR);
            } else {
                // Device acknowledge send data;
                if(xfer_count < current_packet.length) {
                    // Still more to send
                    SEND(*(current_packet.data + xfer_count));
                    // Increment send counter
                    xfer_count++;
                    I2C_status = SEND_DATA;
                } else {
                    // Done sending
                    I2C_stop(SUCCESS);
                }
            }
            break;
        case RECEIVE_DATA:
            RECEIVE_ENABLE = 1;
            I2C_status = ACKNOWLEDGE_RECV;
            break;
        case ACKNOWLEDGE_RECV:
            RECEIVE(*(current_packet.data + xfer_count));
            xfer_count++;
            if(xfer_count < current_packet.length) {
                // Still more to receive
                ACKNOWLEDGE_DATA = 0;
                ACKNOWLEDGE_ENABLE = 1;
                I2C_status = RECEIVE_DATA;
            } else {
                // Done receiving don't acknowledge
                ACKNOWLEDGE_DATA = 1;
                ACKNOWLEDGE_ENABLE = 1;
                I2C_stop(SUCCESS);
            }
            break;
        case STOPPED:
            xfer_count = 0; // Reset xfer count;
            I2C_status = IDLE;
            break;
        default:
            break;
    } 
}
char I2C_master_enabled() {
    return (SSP1CON1bits.SSPEN);
}

void create_read_packet(char * buffer, int length, char address) {
    current_packet.data = buffer;
    current_packet.length = length;
    current_packet.address = (address << 1);
    current_packet.address |= 0x01; // Make read packet
    current_packet.result = PENDING;
}
void create_write_packet(char * data, int length, char address) {
    current_packet.data = data;
    current_packet.length = length;
    current_packet.address = (address << 1); // Make write packet
    current_packet.result = PENDING;
}

I2C_master_result I2C_master_write(char * data, int length, char address) {
    if(!I2C_master_enabled()) {
        return SEND_ERROR;
    }
    create_write_packet(data, length, address);
    SSP1IF = 1;
    I2C_wait();
    return current_packet.result;
}
I2C_master_result I2C_master_read(char * buffer, int length, char address) {
    if(!I2C_master_enabled()) {
        return RECEIVE_ERROR;
    }
    create_read_packet(buffer, length, address);
    SSP1IF = 1;
    I2C_wait();
    return current_packet.result;
}

