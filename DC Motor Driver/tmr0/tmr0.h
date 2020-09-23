#ifndef TMR0_H_
#define TMR0_H_

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "avr/interrupt.h"

//timer mode macros
#define TMR0_MODE_NORMAL			0
#define TMR0_MODE_PHASE_CORRECT		1
#define TMR0_MODE_CTC				2
#define TMR0_MODE_FAST_PWM			3

#define TMR0_DISCONNECT_OCR			0
//timer compare output mode macros
#define TMR0_CTC_TOGGLE_OCR			1
#define TMR0_CTC_CLEAR_OCR			2
#define TMR0_CTC_SET_OCR			3

//timer fast pwm output modes
#define TMR0_FPWM_NON_INVERTING		2
#define TMR0_FPWM_INVERTING			3

//timer phase correct pwm output modes
#define TMR0_PCPWM_UP_CLEAR_COMPARE		2
#define TMR0_PCPWM_UP_SET_COMPARE		3

//timer prescaler values
#define TMR0_PRESCALER_0			0
#define TMR0_PRESCALER_1			1		
#define TMR0_PRESCALER_8			2
#define TMR0_PRESCALER_32			3
#define TMR0_PRESCALER_64			4
#define TMR0_PRESCALER_128			5
#define TMR0_PRESCALER_256			6
#define TMR0_PRESCALER_1024			7

//interrupt enable macros
#define TMR0_OVERFLOW_INT_EN		1
#define TMR0_OVERFLOW_INT_DIS		0
#define TMR0_COMPARE_INT_EN			1
#define TMR0_COMPARE_INT_DIS		0

//function prototypes
void tmr0_init(unsigned char, unsigned char, unsigned char, unsigned char);
void tmr0_start_timer(unsigned char);
void tmr0_stop_timer();
void tmr0_disable_interrupts();
void tmr0_set_ocr(unsigned char);
void tmr0_set_counter(unsigned char);
void tmr0_overflow_isr_callback( void (*ptr_callback)(void) );
void tmr0_compare_isr_callback( void (*ptr_callback)(void) );
void tmr0_set_duty_cycle(unsigned char);

#endif
