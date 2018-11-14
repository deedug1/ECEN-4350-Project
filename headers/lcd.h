/* 
 * File:   lcd.h
 * Author: jstpa
 *
 * Created on November 6, 2018, 2:31 PM
 */

#ifndef LCD_H
#define	LCD_H

// Commands
#define SET_CONTRAST 0x81 // 2 byte
#define SET_DISPLAYALLON_RESUME 0xA4 // 1 byte
#define SET_DISPLAYALLON 0xA5 // 1 byte
#define SET_NORMALDISPLAY 0xA6 // 1 byte
#define SET_INVERSEDISPLAY 0xA7 // 1 byte
#define SET_DISPLAYOFF 0xAE // 1 byte
#define SET_DISPLAYON 0xAF // 1 byte
#define SET_LOWCOL 0x00 // 1 byte
#define SET_HIGHCOL 0x10 // 1 byte
#define SET_MEMORYMODE 0x20 // 2 byte
#define SET_COLADDR 0x21 // 3 byte
#define SET_PAGEADDR 0x22 // 3 byte
#define SET_PAGESTART 0xB0 // 1 byte
#define SET_DISPLAYSTART 0x40 // 1 byte
#define SET_SEGMENTREMAP 0xA0 // 1 byte
#define SET_MULTIPLEX 0xA8 // 2 byte
#define SET_COMOUTPUT 0xC0 // 1 byte
#define SET_COMOUTPUT_REVERSE 0xC8 // 1 byte
#define SET_DISPLAYOFFSET 0xD3 // 2 byte
#define SET_COMPINS 0xDA // 2 byte
#define SET_DISPLAYCLK 0xD5 // 2 byte
#define SET_PRECHARGE 0xD9 // 2 byte
#define SET_VCOMH 0xDB // 2 byte
#define SET_CHARGEPUMP 0x8D // 2 byte
#define LCDNOP 0xE3 // Why though
// Control
#define CONTROL_CMD 0x00
#define CONTROL_DATA 0x40
// Colors
#define BLACK 0
#define WHITE 1
#define INVER 2
#define SETBIT(A, O) A |= (1 << O)
#define CLEARBIT(A, O) A &= ~(1 << O)
#define INVBIT(A, O)  A ^= (1 << O)


void lcd_putc(unsigned char c);
void lcd_puts(unsigned char * s);
void set_pixel(unsigned char i, unsigned char j, unsigned char val);
void lcd_init(void);
void lcd_update(void);
void lcd_clear(void);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

