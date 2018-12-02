
#include <xc.h>
#include "../headers/lcd.h"
#include "../headers/i2c_master.h"
#include "../headers/character.h"

// Helper macros
#define SETBIT(A, O) A |= (1 << O)
#define CLEARBIT(A, O) A &= ~(1 << O)
#define INVBIT(A, O)  A ^= (1 << O)

// LCD Commands
#define SET_CONTRAST            0x81 // 2 byte
#define SET_DISPLAYALLON_RESUME 0xA4 // 1 byte
#define SET_DISPLAYALLON        0xA5 // 1 byte
#define SET_NORMALDISPLAY       0xA6 // 1 byte
#define SET_INVERSEDISPLAY      0xA7 // 1 byte
#define SET_DISPLAYOFF          0xAE // 1 byte
#define SET_DISPLAYON           0xAF // 1 byte
#define SET_LOWCOL              0x00 // 1 byte
#define SET_HIGHCOL             0x10 // 1 byte
#define SET_MEMORYMODE          0x20 // 2 byte
#define SET_COLADDR             0x21 // 3 byte
#define SET_PAGEADDR            0x22 // 3 byte
#define SET_PAGESTART           0xB0 // 1 byte
#define SET_DISPLAYSTART        0x40 // 1 byte
#define SET_SEGMENTREMAP        0xA0 // 1 byte
#define SET_MULTIPLEX           0xA8 // 2 byte
#define SET_COMOUTPUT           0xC0 // 1 byte
#define SET_COMOUTPUT_REVERSE   0xC8 // 1 byte
#define SET_DISPLAYOFFSET       0xD3 // 2 byte
#define SET_COMPINS             0xDA // 2 byte
#define SET_DISPLAYCLK          0xD5 // 2 byte
#define SET_PRECHARGE           0xD9 // 2 byte
#define SET_VCOMH               0xDB // 2 byte
#define SET_CHARGEPUMP          0x8D // 2 byte
#define DISABLE_SCROLL          0x2E // 1 byte
#define LCDNOP                  0xE3 // Why though

// Preprocesser Constants
#define CONTROL_CMD             0x00
#define CONTROL_DATA            0x40
#define LCD_ADDR 0x3C
#define ROWS 0x04
#define COLS 0x80
#define PAGES 0x04
#define LCDWIDTH 128
#define LCDHEIGHT 32

// LCD buffer
char lcd_buffer [ROWS * COLS] = {
   0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
   0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
   0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
   0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
   0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
   0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
   0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
   0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
   0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
   0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
   0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
   0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
   0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
   0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
   0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
   0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
   0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
   0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
   0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
   0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
   0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
   0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
   0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
   0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
   0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
   0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
   0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
   0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
}; // 32 x 128 pixels    

// Cursor variables
static int cursor_x = 0;
static int cursor_y = 0;

/**
 * Writes a command to the LCD
 * @param cmd 
 * the command to write
 */
void command(unsigned char cmd) {
    char msg[2];
    msg[0] = CONTROL_CMD;
    msg[1] = cmd;
    I2C_master_write(msg, 2, LCD_ADDR);
}
/**
 * Initialize the display
 */
void lcd_init() {
    // Turn off the display to configure it
    command(SET_DISPLAYOFF);
    
    // Set displays clock speed
    command(SET_DISPLAYCLK);
    command(0x80); // Recommended clock divider via datasheet
    
    // Set display cursor
    command(SET_DISPLAYOFFSET);
    command(0x00);
    
    // Set display size
    command(SET_MULTIPLEX);
    command(LCDWIDTH - 1);
    
    // Set display cursor
    command(SET_DISPLAYSTART | 0x0);
    
    // Set display memory mode
    command(SET_MEMORYMODE);
    command(0x00);
    
    // Set display segmentation mode
    command(SET_SEGMENTREMAP);
    
    // Set dipslay height
    command(SET_COMOUTPUT);
    
    command(SET_COMPINS);
    command(0x02);
    
    command(SET_CONTRAST);
    command(0xCF);
    
    command(SET_DISPLAYALLON_RESUME);
    
    command(SET_NORMALDISPLAY);
    
    // Turn on charge pump for 7.5V power
    command(SET_CHARGEPUMP);
    command(0x14); // ON
    
    command(DISABLE_SCROLL);
    
    // Display init finished turn on display
    command(SET_DISPLAYON);
    
}
/**
 * Update the display with the lcd_buffer
 */
void lcd_update() {
    int i, j, max;
    char data[33];
    // Set column start
    command(SET_COLADDR);
    command(0x00);
    command(LCDWIDTH - 1);
    
    // Set page start
    command(SET_PAGEADDR);
    command(0x00);
    command(0xFF);
    max = ROWS * COLS;
    for(i = 0; i < max; i += 32) {
        data[0] = CONTROL_DATA;
        for(j = 0; j < 32; j++) {
            data[j + 1] = lcd_buffer[i + j];
        }
        I2C_master_write(data, 33, LCD_ADDR);
    }
}

void lcd_clear() {
    int i;
    for(i = 0; i < ROWS * COLS; i++) {
        lcd_buffer[i] = 0x00;
    }
    cursor_x = 0;
    cursor_y = 0;
    lcd_update();
}

void lcd_putc(char c) {
    int i = 0, index = cursor_x + cursor_y * COLS;
    int char_index;
    if (c < 32 ) c = ' ';
	char_index = ((c - 32) * 6);
    for(i = 0; i < 6; i++) {
        lcd_buffer[index + i] = lcd_font[char_index + i];   
    }
    cursor_x += CHAR_WIDTH;
    if(cursor_x > 120) {
        cursor_x = 0;
        cursor_y += 1;
    }
    if(cursor_y > 3) {
        cursor_y = 0;
    }
}

void lcd_puts(char * s) {
    while(*s) {
        lcd_putc(*s);
        s++;
    }
}

void lcd_newline() {
    if(cursor_y >= 3) {
        cursor_x = 0;
        cursor_y = 3;
        lcd_vertical_shift();
    } else {
        cursor_y += 1;
        cursor_x = 0;
    }
}

void lcd_vertical_shift() {
    int i = 0;
    for(i = 0; i < 3 * COLS; i++) {
        lcd_buffer[i] = lcd_buffer[i + COLS]; 
    }
    for(; i < ROWS * COLS; i++) {
        lcd_buffer[i] = 0;
    }
}