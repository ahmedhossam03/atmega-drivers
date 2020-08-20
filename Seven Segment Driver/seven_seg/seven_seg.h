#ifndef SEG_H_
#define SEG_H_

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "util/delay.h"

//SEVEN SEGMENT PORTS
//PORTC will be data port so we put its addresses
#define SEG_DATA_DIRC	DDRC
#define SEG_DATA_PORT	PORTC
//PORTA will be ctrl port so we put its addresses
#define SEG_CTRL_DIRC	DDRA
#define SEG_CTRL_PORT	PORTA

//CTRL PINS, tested on common anode 7 segment where you put low to activate led
//you can add more ctrl pins to same ctrl port to operate 2 segments using same data port
#define SEG_CTRL_PIN0	0			
#define SEG_CTRL_PIN1	1
#define SEG_CTRL_PIN2	2
#define SEG_CTRL_PIN3	3

//numbers without decimal point
#define SEG_0			0xC0
#define SEG_1			0xF9
#define SEG_2			0xA4
#define SEG_3			0xB0
#define SEG_4			0x99
#define SEG_5			0x92
#define SEG_6			0x82
#define SEG_7			0xF8
#define SEG_8			0x80
#define SEG_9			0x90

//numbers with decimal point
#define SEGD_0			0x40
#define SEGD_1			0x79
#define SEGD_2			0x24
#define SEGD_3			0x30
#define SEGD_4			0x19
#define SEGD_5			0x12
#define SEGD_6			0x02
#define SEGD_7			0x78
#define SEGD_8			0x00
#define SEGD_9			0x10

//FUNCTION PROTOTYPES
void seg_init();
void seg_disp_digit(unsigned char, unsigned char);
//use these functions only with 4-digit seven segments
void seg_disp_4digits(unsigned short);
void seg_disp_4digits_float(float);

#endif
