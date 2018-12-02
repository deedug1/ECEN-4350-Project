/* 
 * File:   lcd.h
 * Author: jstpa
 *
 * Created on November 6, 2018, 2:31 PM
 */

#ifndef LCD_H
#define	LCD_H

// Colors
#define BLACK 0
#define WHITE 1
#define INVER 2

#define SETBIT(A, O) A |= (1 << O)
#define CLEARBIT(A, O) A &= ~(1 << O)
#define INVBIT(A, O)  A ^= (1 << O)


void lcd_putc(char c);
void lcd_puts(char * s);
void set_pixel(unsigned char i, unsigned char j, unsigned char val);
void lcd_init(void);
void lcd_update(void);
void lcd_clear(void);
void lcd_newline(void);
void lcd_vertical_shift(void);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

