#ifndef TMR1_H_
#define TMR1_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "avr/interrupt.h"

//timer mode macros
#define TMR1_MODE_NORMAL						0
#define TMR1_MODE_PHASE_CORRECT_8				1
#define TMR1_MODE_PHASE_CORRECT_9				2
#define TMR1_MODE_PHASE_CORRECT_10				3
#define TMR1_MODE_CTC_OCR_TOP					4
#define TMR1_MODE_FAST_PWM_8					5
#define TMR1_MODE_FAST_PWM_9					6
#define TMR1_MODE_FAST_PWM_10					7
#define TMR1_MODE_PHASE_FREQ_CORRECT_ICR_TOP	8
#define TMR1_MODE_PHASE_FREQ_CORRECT_OCR_TOP	9
#define TMR1_MODE_PHASE_CORRECT_ICR_TOP			10
#define TMR1_MODE_PHASE_CORRECT_OCR_TOP			11
#define TMR1_MODE_CTC_ICR_TOP					12
#define TMR1_MODE_FAST_PWM_ICR_TOP				14
#define TMR1_MODE_FAST_PWM_OCR_TOP				15

//ocr channel select macros
#define TMR1_OCRA								1
#define TMR1_OCRB								2
#define TMR1_OCRC								3
#define TMR1_DISCONNECT_OCR						0

//compare output modes
#define TMR1_CTC_TOGGLE_OCR						1
#define TMR1_CTC_CLEAR_OCR						2
#define TMR1_CTC_SET_OCR						3	

//fast pwm output mode
#define TMR1_FPWM_OCR_TOP_TOGGLE				1	
#define TMR1_FPWM_NON_INVERTING					2
#define TMR1_FPWM_INVERTING						3

//phase correct output mode
#define TMR1_PCPWM_OCR_TOP_TOGGLE				1
#define TMR1_PCPWM_UP_CLEAR_COMPARE				2
#define TMR1_PCPWM_UP_SET_COMPARE				3

//icu macro
#define TMR1_ICU_EN_RISING						1
#define TMR1_ICU_EN_FALLING						2
#define TMR1_ICU_DIS							0
#define TMR1_ICU_TOGGLE_EDGE					3

//overflow interrupt enable
#define TMR1_OVERFLOW_INT_EN					1
#define TMR1_OVERFLOW_INT_DIS					0

//compare interrupt enable
#define TMR1_COMPARE_INT_EN						1
#define TMR1_COMPARE_INT_DIS					0	

//prescalers
#define TMR1_PRESCALER_0						0
#define TMR1_PRESCALER_1						1
#define TMR1_PRESCALER_8						2
#define TMR1_PRESCALER_64						3
#define TMR1_PRESCALER_256						4
#define TMR1_PRESCALER_1024						5
#define TMR1_PRESCALER_EXT_FALLING				6
#define TMR1_PRESCALER_EXT_RISING				7

//function prototypes
void tmr1_init(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void tmr1_start_timer(unsigned char);
void tmr1_stop_timer();
void tmr1_disable_interrupts();
void tmr1_set_ocr(unsigned char, unsigned short);
void tmr1_set_icr(unsigned short);
void tmr1_set_counter(unsigned short);
void tmr1_set_duty_cycle(unsigned char, unsigned short, unsigned char);
void tmr1_change_capture_edge(unsigned char);
void tmr1_compare_a_isr_callback( void (*ptr_isr)(void) );
void tmr1_compare_b_isr_callback( void (*ptr_isr)(void) );
void tmr1_compare_c_isr_callback( void (*ptr_isr)(void) );
void tmr1_overflow_isr_callback( void (*ptr_isr)(void) );
void tmr1_capture_isr_callback( void (*ptr_isr)(void) );

#endif
