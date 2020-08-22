#ifndef BIPOLAR_STEPPER_H_
#define BIPOLAR_STEPPER_H_

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "util/delay.h"

//STEPPER PORT DEFINITIONS AND PINS
#define BI_STEPPER_DDR		DDRG
#define BI_STEPPER_PORT		PORTG
#define BI_STEPPER_RED		0		//red wire
#define BI_STEPPER_GRN		1		//green wire
#define BI_STEPPER_YLW		2		//yellow wire
#define BI_STEPPER_BLU		3		//blue wire

//STEPPER SPECS
#define BI_STEP_ANGLE		1.8						//full step
#define BI_STEP_HALF		(BI_STEP_ANGLE / 2)		//half step
#define BI_360_STEPS		(360.0 / BI_STEP_ANGLE)	//number of steps for full rev
#define BI_360_HALF			(360.0 / BI_STEP_HALF)	//number of half steps for full rev
#define BI_STEP_DELAY		100						//minimum delay time between each step

//STEPPER OPERATION MODES
#define BI_HALF_STEP_MODE	0
#define BI_FULL_STEP_MODE_1	1
#define BI_FULL_STEP_MODE_2	2

//FUNCTION PROTOTYPES
void bi_stepper_init(unsigned char);
void bi_stepper_inc_clkwise(unsigned char); 
void bi_stepper_inc_anticlk(unsigned char); 

void bi_stepper_goto_zero_clkwise(unsigned char); 
void bi_stepper_goto_zero_anticlk(unsigned char); 

void bi_stepper_goto_90_clkwise(unsigned char); 
void bi_stepper_goto_90_anticlk(unsigned char);	

void bi_stepper_goto_180_clkwise(unsigned char); 
void bi_stepper_goto_180_anticlk(unsigned char); 

void bi_stepper_goto_270_clkwise(unsigned char); 
void bi_stepper_goto_270_anticlk(unsigned char);

#endif /* BIPOLAR_STEPPER_H_ */
