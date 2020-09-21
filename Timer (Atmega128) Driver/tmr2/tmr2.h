#ifndef TMR2_H_
#define TMR2_H_

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "avr/interrupt.h"

//timer mode macros
#define TMR2_MODE_NORMAL			0
#define TMR2_MODE_PHASE_CORRECT		1
#define TMR2_MODE_CTC				2
#define TMR2_MODE_FAST_PWM			3

#define TMR2_DISCONNECT_OCR			0
//timer compare output mode macros
#define TMR2_CTC_TOGGLE_OCR			1
#define TMR2_CTC_CLEAR_OCR			2
#define TMR2_CTC_SET_OCR			3

//timer fast pwm output modes
#define TMR2_FPWM_NON_INVERTING		2
#define TMR2_FPWM_INVERTING			3

//timer phase correct pwm output modes
#define TMR2_PCPWM_UP_CLEAR_COMPARE		2
#define TMR2_PCPWM_UP_SET_COMPARE		3

//timer prescaler values
#define TMR2_PRESCALER_0				0
#define TMR2_PRESCALER_1				1
#define TMR2_PRESCALER_8				2
#define TMR2_PRESCALER_64				3
#define TMR2_PRESCALER_256				4
#define TMR2_PRESCALER_1024				5
#define TMR2_PRESCALER_EXT_FALLING		6
#define TMR2_PRESCALER_EXT_RISING		7

//interrupt enable macros
#define TMR2_OVERFLOW_INT_EN		1
#define TMR2_OVERFLOW_INT_DIS		0
#define TMR2_COMPARE_INT_EN			1
#define TMR2_COMPARE_INT_DIS		0

//function prototypes
void tmr2_init(unsigned char, unsigned char, unsigned char, unsigned char);
void tmr2_start_timer(unsigned char);
void tmr2_stop_timer();
void tmr2_disable_interrupts();
void tmr2_set_ocr(unsigned char);
void tmr2_set_counter(unsigned char);
void tmr2_overflow_isr_callback( void (*ptr_callback)(void) );
void tmr2_compare_isr_callback( void (*ptr_callback)(void) );
void tmr2_set_duty_cycle(unsigned char);

#endif
