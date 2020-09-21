#include "tmr3.h"

static void (*tmr3_compare_a_isr_ptr)(void);
static void (*tmr3_compare_b_isr_ptr)(void);
static void (*tmr3_compare_c_isr_ptr)(void);
static void (*tmr3_overflow_isr_ptr)(void);
static void (*tmr3_capture_isr_ptr)(void);

void tmr3_init(unsigned char mode, unsigned char channel_select, unsigned char compare_mode, unsigned char icu_mode, unsigned char overflow_int_mode, unsigned char compare_int_mode)
{
	switch(mode)
	{
		case TMR3_MODE_NORMAL:
		//clear all wave generation bits
		TCCR3A &= ~(1 << WGM30);
		TCCR3A &= ~(1 << WGM31);
		TCCR3B &= ~(1 << WGM32);
		TCCR3B &= ~(1 << WGM33);
		break;
		
		case TMR3_MODE_PHASE_CORRECT_8:
		//clear all wave generation bits and set the first bit
		TCCR3A |= (1 << WGM30);
		TCCR3A &= ~(1 << WGM31);
		TCCR3B &= ~(1 << WGM32);
		TCCR3B &= ~(1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_PHASE_CORRECT_9:
		//clear all wave generation bits and set the second bit
		TCCR3A &= ~(1 << WGM30);
		TCCR3A |= (1 << WGM31);
		TCCR3B &= ~(1 << WGM32);
		TCCR3B &= ~(1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_PHASE_CORRECT_10:
		//clear all wave generation bits and set the first 2 bits
		TCCR3A |= (1 << WGM30);
		TCCR3A |= (1 << WGM31);
		TCCR3B &= ~(1 << WGM32);
		TCCR3B &= ~(1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 5);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_CTC_OCR_TOP:
		//clear all wave generation bits and set the third bit
		TCCR3A &= ~(1 << WGM30);
		TCCR3A &= ~(1 << WGM31);
		TCCR3B |= (1 << WGM32);
		TCCR3B &= ~(1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 5);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_FAST_PWM_8:
		//clear all wave generation bits and set the first & third bit
		TCCR3A |= (1 << WGM30);
		TCCR3A &= ~(1 << WGM31);
		TCCR3B |= (1 << WGM32);
		TCCR3B &= ~(1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 5);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_FAST_PWM_9:
		//clear all wave generation bits and set the second & third bit
		TCCR3A &= ~(1 << WGM30);
		TCCR3A |= (1 << WGM31);
		TCCR3B |= (1 << WGM32);
		TCCR3B &= ~(1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 5);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_FAST_PWM_10:
		//clear all wave generation bits and set the first 3 bits
		TCCR3A |= (1 << WGM30);
		TCCR3A |= (1 << WGM31);
		TCCR3B |= (1 << WGM32);
		TCCR3B &= ~(1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 5);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_PHASE_FREQ_CORRECT_ICR_TOP:
		//clear all wave generation bits and set the fourth bit
		TCCR3A &= ~(1 << WGM30);
		TCCR3A &= ~(1 << WGM31);
		TCCR3B &= ~(1 << WGM32);
		TCCR3B |= (1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 5);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_PHASE_FREQ_CORRECT_OCR_TOP:
		//clear all wave generation bits and set the first & fourth bit
		TCCR3A |= (1 << WGM30);
		TCCR3A &= ~(1 << WGM31);
		TCCR3B &= ~(1 << WGM32);
		TCCR3B |= (1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 5);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_PHASE_CORRECT_ICR_TOP:
		//clear all wave generation bits and set the second & fourth bit
		TCCR3A &= ~(1 << WGM30);
		TCCR3A |= (1 << WGM31);
		TCCR3B &= ~(1 << WGM32);
		TCCR3B |= (1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 5);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_PHASE_CORRECT_OCR_TOP:
		//clear all wave generation bits and set the first 2 bits & fourth bit
		TCCR3A |= (1 << WGM30);
		TCCR3A |= (1 << WGM31);
		TCCR3B &= ~(1 << WGM32);
		TCCR3B |= (1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 5);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_CTC_ICR_TOP:
		//clear all wave generation bits and set the last 2 bits
		TCCR3A &= ~(1 << WGM30);
		TCCR3A &= ~(1 << WGM31);
		TCCR3B |= (1 << WGM32);
		TCCR3B |= (1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 5);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_FAST_PWM_ICR_TOP:
		//clear all wave generation bits and set the last 3 bits
		TCCR3A &= ~(1 << WGM30);
		TCCR3A |= (1 << WGM31);
		TCCR3B |= (1 << WGM32);
		TCCR3B |= (1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 5);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
		
		case TMR3_MODE_FAST_PWM_OCR_TOP:
		//set all bits
		TCCR3A |= (1 << WGM30);
		TCCR3A |= (1 << WGM31);
		TCCR3B |= (1 << WGM32);
		TCCR3B |= (1 << WGM33);
		//select output channel
		switch (channel_select)
		{
			case TMR3_OCRA:
			//define OC1A as output
			DDRE |= (1 << 3);
			//mode select
			TCCR3A |= (compare_mode << COM3A0);
			break;
			
			case TMR3_OCRB:
			//define OC1B as output
			DDRE |= (1 << 4);
			//mode select
			TCCR3A |= (compare_mode << COM3B0);
			break;
			
			case TMR3_OCRC:
			//define OC1C as output
			DDRE |= (1 << 5);
			//mode select
			TCCR3A |= (compare_mode << COM3C0);
			break;
		}
		break;
	}
	
	//enable icu
	if(icu_mode == TMR3_ICU_EN_RISING)
	{
		TCCR3B |= (1 << ICES3);
		//enable icu interrupt as well
		ETIMSK |= (1 << TICIE3);
	}
	else if(icu_mode == TMR3_ICU_EN_FALLING)
	{
		TCCR3B &= ~(1 << ICES3);
		//enable icu interrupt as well
		ETIMSK |= (1 << TICIE3);
	}
	
	//enable overflow interrupt
	if(overflow_int_mode == TMR3_OVERFLOW_INT_EN)
	{
		ETIMSK |= (1 << TOIE3);
	}
	
	//enable compare interrupt
	if(compare_int_mode == TMR3_COMPARE_INT_EN)
	{
		switch(channel_select)
		{
			case TMR3_OCRA:
			ETIMSK |= (1 << OCIE3A);
			break;
			
			case TMR3_OCRB:
			ETIMSK |= (1 << OCIE3B);
			break;
			
			case TMR3_OCRC:
			ETIMSK |= (1 << OCIE3C);
			break;
		}
	}
}

void tmr3_start_timer(unsigned char prescaler_value)
{
	TCCR3B |= (prescaler_value << CS30);
}

void tmr3_stop_timer()
{
	//clear prescaler values
	TCCR3B &= 0xF8;
}

void tmr3_disable_interrupts()
{
	ETIMSK &= ~(1 << TOIE3);
	ETIMSK &= ~(1 << OCIE3A);
	ETIMSK &= ~(1 << OCIE3B);
	ETIMSK &= ~(1 << OCIE3C);
}

void tmr3_set_ocr(unsigned char channel_select, unsigned short ocr_value)
{
	switch(channel_select)
	{
		case TMR3_OCRA:
		OCR3A = ocr_value;
		break;
		
		case TMR3_OCRB:
		OCR3B = ocr_value;
		break;
		
		case TMR3_OCRC:
		OCR3C = ocr_value;
		break;
	}
}

void tmr3_set_icr(unsigned short icr_value)
{
	ICR3 = icr_value;
}

void tmr3_set_counter(unsigned short counter_value)
{
	TCNT3 = counter_value;
}

void tmr3_set_duty_cycle(unsigned char channel_select, unsigned short counter_top, unsigned char duty_cycle)
{
	unsigned short dc = 0;
	dc = ( duty_cycle * (counter_top / 100.0) ) - 1;
	switch(channel_select)
	{
		case TMR3_OCRA:
		tmr3_set_ocr(TMR3_OCRA, dc);
		break;
		
		case TMR3_OCRB:
		tmr3_set_ocr(TMR3_OCRB, dc);
		break;
		
		case TMR3_OCRC:
		tmr3_set_ocr(TMR3_OCRC, dc);
		break;
	}
}

void tmr3_change_capture_edge(unsigned char edge_select)
{
	if(edge_select == TMR3_ICU_EN_RISING)
	{
		TCCR3B |= (1 << ICES3);
	}
	else if(edge_select == TMR3_ICU_EN_FALLING)
	{
		TCCR3B &= ~(1 << ICES3);
	}
	else
	{
		TCCR3B ^= (1 << ICES3);
	}
}

void tmr3_compare_a_isr_callback( void (*ptr_isr)(void) )
{
	tmr3_compare_a_isr_ptr = ptr_isr;
}

void tmr3_compare_b_isr_callback( void (*ptr_isr)(void) )
{
	tmr3_compare_b_isr_ptr = ptr_isr;
}

void tmr3_compare_c_isr_callback( void (*ptr_isr)(void) )
{
	tmr3_compare_c_isr_ptr = ptr_isr;
}

void tmr3_overflow_isr_callback( void (*ptr_isr)(void) )
{
	tmr3_overflow_isr_ptr = ptr_isr;
}

void tmr3_capture_isr_callback( void (*ptr_isr)(void) )
{
	tmr3_capture_isr_ptr = ptr_isr;
}

ISR(TIMER3_CAPT_vect)
{
	(*tmr3_capture_isr_ptr)();
}

ISR(TIMER3_COMPA_vect)
{
	(*tmr3_compare_a_isr_ptr)();
}

ISR(TIMER3_COMPB_vect)
{
	(*tmr3_compare_b_isr_ptr)();
}

ISR(TIMER3_COMPC_vect)
{
	(*tmr3_compare_c_isr_ptr)();
}

ISR(TIMER3_OVF_vect)
{
	(*tmr3_overflow_isr_ptr)();
}
