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




void lcd_putc(char c);
void lcd_puts(char * s);
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

