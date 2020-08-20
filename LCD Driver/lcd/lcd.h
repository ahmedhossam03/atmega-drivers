#ifndef LCD_H_
#define LCD_H_

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "util/delay.h"	//lcd needs delays for executing commands

//LCD PORTS
#define		LCD_DATA_PORT		PORTC
#define		LCD_DATA_DIRC		DDRC

#define		LCD_CTRL_PORT		PORTB
#define		LCD_CTRL_DIRC		DDRB

//CTRL PINS
#define		LCD_RS		5
#define		LCD_RW		6
#define		LCD_EN		7

//CTRL CMDS
#define		LCD_FUNC		0x28		//edit this according to LCD data sheet to change 4 bit / 8 bit
#define		LCD_DISP		0x0C		//edit this according to LCD data sheet to change display / cursor / blinking
#define		LCD_ENTRY		0x06		//edit this according to LCD data sheet to change increment / decrement or shifting mode
#define		LCD_CLR			0x01

//FUNCTION PROTOTYPES
void lcd_init();
void lcd_send_cmd(unsigned char);
void lcd_send_char(unsigned char);
void lcd_send_str(unsigned char[], unsigned char);
void lcd_send_itoa(unsigned short);
void lcd_goto_xy(unsigned char, unsigned char);

#endif /* LCD_H_ */
