#include <xc.h>
#include "../headers/mc_init.h"
#include "../headers/i2c_master.h"
#include "../headers/uart.h"
#include "../headers/interrupt.h"
#include "../headers/stopwatch.h"
#include "../headers/timer0.h"

// Configuration bits: selected in the GUI

// CONFIG1L
#pragma config FEXTOSC = OFF    // External Oscillator mode Selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_1MHZ    // Power-up default value for COSC bits->HFINTOSC with HFFRQ = 4 MHz and CDIV = 4:1

// CONFIG1H
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled
#pragma config CSWEN = ON    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor enabled

// CONFIG2L
#pragma config MCLRE = EXTMCLR    // Master Clear Enable bit->MCLR pin (RE3) is MCLR
#pragma config PWRTE = OFF    // Power-up Timer Enable bit->Power up timer disabled
#pragma config LPBOREN = OFF    // Low-power BOR enable bit->Low power BOR is disabled
#pragma config BOREN = SBORDIS    // Brown-out Reset Enable bits->Brown-out Reset enabled , SBOREN bit is ignored

// CONFIG2H
#pragma config BORV = VBOR_190    // Brown Out Reset Voltage selection bits->Brown-out Reset Voltage (VBOR) set to 1.90V
#pragma config ZCD = OFF    // ZCD Disable bit->ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON
#pragma config PPS1WAY = ON    // PPSLOCK bit One-Way Set Enable bit->PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle
#pragma config STVREN = ON    // Stack Full/Underflow Reset Enable bit->Stack full/underflow will cause Reset
#pragma config DEBUG = OFF    // Debugger Enable bit->Background debugger disabled
#pragma config XINST = OFF    // Extended Instruction Set Enable bit->Extended Instruction Set and Indexed Addressing Mode disabled

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31    // WDT Period Select bits->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE = OFF    // WDT operating mode->WDT Disabled

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC    // WDT input clock selector->Software Control

// CONFIG4L
#pragma config WRT0 = OFF    // Write Protection Block 0->Block 0 (000800-001FFFh) not write-protected
#pragma config WRT1 = OFF    // Write Protection Block 1->Block 1 (002000-003FFFh) not write-protected
#pragma config WRT2 = OFF    // Write Protection Block 1->Block 2 (004000-005FFFh) not write-protected
#pragma config WRT3 = OFF    // Write Protection Block 1->Block 3 (006000-007FFFh) not write-protected

// CONFIG4H
#pragma config WRTC = OFF    // Configuration Register Write Protection bit->Configuration registers (300000-30000Bh) not write-protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block (000000-0007FFh) not write-protected
#pragma config WRTD = OFF    // Data EEPROM Write Protection bit->Data EEPROM not write-protected
#pragma config SCANE = ON    // Scanner Enable bit->Scanner module is available for use, SCANMD bit can control the module
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored

// CONFIG5L
#pragma config CP = OFF    // UserNVM Program Memory Code Protection bit->UserNVM code protection disabled
#pragma config CPD = OFF    // DataNVM Memory Code Protection bit->DataNVM code protection disabled

// CONFIG6L
#pragma config EBTR0 = OFF    // Table Read Protection Block 0->Block 0 (000800-001FFFh) not protected from table reads executed in other blocks
#pragma config EBTR1 = OFF    // Table Read Protection Block 1->Block 1 (002000-003FFFh) not protected from table reads executed in other blocks
#pragma config EBTR2 = OFF    // Table Read Protection Block 1->Block 2 (004000-005FFFh) not protected from table reads executed in other blocks
#pragma config EBTR3 = OFF    // Table Read Protection Block 1->Block 3 (006000-007FFFh) not protected from table reads executed in other blocks

// CONFIG6H
#pragma config EBTRB = OFF    // Boot Block Table Read Protection bit->Boot Block (000000-0007FFh) not protected from table reads executed in other blocks


void system_init() {
    controller_init();
    interrupt_init();
    UART_init();
    I2C_master_init();
    stopwatch_init();
    TIMER0_init();
}
void port_init() {
    
    // PORT A
    LATA = LAT_DEFAULT;
    ANSELA = ANSEL_DEFAULT; // RA0 == Analog pH
    TRISA = TRIS_DEFAULT;  // RA0 == INPUT
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
