#ifndef TMR3_H_
#define TMR3_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "avr/interrupt.h"

//timer mode macros
#define TMR3_MODE_NORMAL						0
#define TMR3_MODE_PHASE_CORRECT_8				1
#define TMR3_MODE_PHASE_CORRECT_9				2
#define TMR3_MODE_PHASE_CORRECT_10				3
#define TMR3_MODE_CTC_OCR_TOP					4
#define TMR3_MODE_FAST_PWM_8					5
#define TMR3_MODE_FAST_PWM_9					6
#define TMR3_MODE_FAST_PWM_10					7
#define TMR3_MODE_PHASE_FREQ_CORRECT_ICR_TOP	8
#define TMR3_MODE_PHASE_FREQ_CORRECT_OCR_TOP	9
#define TMR3_MODE_PHASE_CORRECT_ICR_TOP			10
#define TMR3_MODE_PHASE_CORRECT_OCR_TOP			11
#define TMR3_MODE_CTC_ICR_TOP					12
#define TMR3_MODE_FAST_PWM_ICR_TOP				14
#define TMR3_MODE_FAST_PWM_OCR_TOP				15

//ocr channel select macros
#define TMR3_OCRA								1
#define TMR3_OCRB								2
#define TMR3_OCRC								3
#define TMR3_DISCONNECT_OCR						0

//compare output modes
#define TMR3_CTC_TOGGLE_OCR						1
#define TMR3_CTC_CLEAR_OCR						2
#define TMR3_CTC_SET_OCR						3

//fast pwm output mode
#define TMR3_FPWM_OCR_TOP_TOGGLE				1
#define TMR3_FPWM_NON_INVERTING					2
#define TMR3_FPWM_INVERTING						3

//phase correct output mode
#define TMR3_PCPWM_OCR_TOP_TOGGLE				1
#define TMR3_PCPWM_UP_CLEAR_COMPARE				2
#define TMR3_PCPWM_UP_SET_COMPARE				3

//icu macro
#define TMR3_ICU_EN_RISING						1
#define TMR3_ICU_EN_FALLING						2
#define TMR3_ICU_DIS							0
#define TMR3_ICU_TOGGLE_EDGE					3

//overflow interrupt enable
#define TMR3_OVERFLOW_INT_EN					1
#define TMR3_OVERFLOW_INT_DIS					0

//compare interrupt enable
#define TMR3_COMPARE_INT_EN						1
#define TMR3_COMPARE_INT_DIS					0

//prescalers
#define TMR3_PRESCALER_0						0
#define TMR3_PRESCALER_1						1
#define TMR3_PRESCALER_8						2
#define TMR3_PRESCALER_64						3
#define TMR3_PRESCALER_256						4
#define TMR3_PRESCALER_1024						5
#define TMR3_PRESCALER_EXT_FALLING				6
#define TMR3_PRESCALER_EXT_RISING				7

//function prototypes
void tmr3_init(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void tmr3_start_timer(unsigned char);
void tmr3_stop_timer();
void tmr3_disable_interrupts();
void tmr3_set_ocr(unsigned char, unsigned short);
void tmr3_set_icr(unsigned short);
void tmr3_set_counter(unsigned short);
void tmr3_set_duty_cycle(unsigned char, unsigned short, unsigned char);
void tmr3_change_capture_edge(unsigned char);
void tmr3_compare_a_isr_callback( void (*ptr_isr)(void) );
void tmr3_compare_b_isr_callback( void (*ptr_isr)(void) );
void tmr3_compare_c_isr_callback( void (*ptr_isr)(void) );
void tmr3_overflow_isr_callback( void (*ptr_isr)(void) );
void tmr3_capture_isr_callback( void (*ptr_isr)(void) );

#endif
