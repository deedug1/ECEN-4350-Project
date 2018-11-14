#include <xc.h>
#include "mc_init.h"


void port_init() {
    
    // PORT A
    LATA = LAT_DEFAULT;
    ANSELA = ANSEL_DEFAULT;
    TRISA = TRIS_DEFAULT;
    WPUA = WPU_DEFAULT;
    ODCONA = ODCON_DEFAULT;
    SLRCONA = SLRCON_DEFAULT;
    
    // PORT B
    LATB = LAT_DEFAULT;
    ANSELB = ANSEL_DEFAULT;
    TRISB = TRIS_DEFAULT;
    WPUB = WPU_DEFAULT;
    ODCONB = ODCON_DEFAULT;
    SLRCONB = SLRCON_DEFAULT;
    
    // PORT C
    LATC = LAT_DEFAULT;
    ANSELC = 0xF0; // RC3, RC2, RC1, RC0
    TRISC = 0xFD;
    WPUC = WPU_DEFAULT;
    ODCONC = ODCON_DEFAULT;
    SLRCONC = SLRCON_DEFAULT;
    
}

void pps_init() {
    char state = GIE;
    GIE = 0;
    PPSLOCK = 0x55; // Unlock PPS 
    PPSLOCK = 0XAA;
    PPSLOCK = 0X00;
    
    // Begin PPS
    
    // I2C
    RC2PPS = 0x0E;      // RC2 --> SDO
    SSP1DATPPS = 0x12;  // RC2 --> SDI
    RC3PPS = 0x0D;      // RC3 --> SCKI
    SSP1CLKPPS = 0x13;  // RC3 --> SCKO
    
    // UART
    RX1PPS = 0x10;      // RC0 --> Rx
    RC1PPS = 0x09;      // RC1 --> Tx

    
    
    // End PPS
    
    PPSLOCK = 0x55; // Lock PPS
    PPSLOCK = 0XAA;
    PPSLOCK = 0X01;
    GIE = state;
}
void oscillator_init() {
    // HFINTOSC
    OSCCON1 =   0x60;
    OSCCON3 =   0x00;
    // 16 Mhz
    OSCFRQ =    0x05;
    // Center frequency
    OSCTUNE =   0x00; 
}
//void timer_init() {
//    T0CON0 = 0x11;
//    T0CON1 = 0X40;
//    T0CON0 = 0x91;
//}
void controller_init() {
    oscillator_init();
    pps_init();
//    timer_init();
    port_init();
}
