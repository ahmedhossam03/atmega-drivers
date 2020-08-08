#ifndef STEPPER_H_
#define STEPPER_H_

#ifndef F_CPU
	#define F_CPU	8000000UL
#endif

#ifndef	NULL
	#define NULL   ( (void*)0 )
#endif

#include	"avr/io.h"
#include	"util/delay.h"

#define UNI_STEPPER_1_DDR		DDRF
#define UNI_STEPPER_1_PORT		PORTF
#define UNI_STEPPER_1_PIN_1		0
#define UNI_STEPPER_1_PIN_2		1
#define UNI_STEPPER_1_PIN_3		2
#define UNI_STEPPER_1_PIN_4		3

#define UNI_STEPPER_DELAY		100

#define UNI_STEP_ANGLE			5.625     //half step from the datasheet of the motor used
#define UNI_360_STEPS			360.0 / UNI_STEP_ANGLE

void uni_stepper_init();
void uni_stepper_increment_clkwise();
void uni_stepper_increment_anticlk();

void uni_stepper_goto_zero_clkwise();
void uni_stepper_goto_zero_anticlk();

void uni_stepper_goto_90_clkwise();
void uni_stepper_goto_90_anticlk();

void uni_stepper_goto_180_clkwise();
void uni_stepper_goto_180_anticlk();

#endif /* STEPPER_H_ */
