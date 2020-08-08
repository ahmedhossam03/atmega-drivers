#ifndef IR_H_
#define IR_H_

#ifndef F_CPU
	#define F_CPU	8000000UL
#endif

#ifndef	NULL
	#define NULL   ( (void*)0 )
#endif

#include	"avr/io.h"
#include	"../ext_interrupt/ext_interrupt.h"
#include	"util/delay.h"

#define IR_DDR	DDRD
#define IR_PORT	PIND
#define	IR_PIN	0

#define IR_MODE_INT 0
#define IR_MODE_PIN 1

typedef enum
{
	ir_no_obstacle,
	ir_obstacle,
	ir_no_change
}ir_state;

void ir_init(unsigned char);
ir_state ir_get_state(unsigned char);

#endif /* IR_H_ */
