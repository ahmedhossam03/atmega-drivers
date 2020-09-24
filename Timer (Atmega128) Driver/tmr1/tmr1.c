#include "tmr1.h"

static void (*tmr1_compare_a_isr_ptr)(void);
static void (*tmr1_compare_b_isr_ptr)(void);
static void (*tmr1_compare_c_isr_ptr)(void);
static void (*tmr1_overflow_isr_ptr)(void);
static void (*tmr1_capture_isr_ptr)(void);

void tmr1_init(unsigned char mode, unsigned char channel_select, unsigned char compare_mode, unsigned char icu_mode, unsigned char overflow_int_mode, unsigned char compare_int_mode)
{
	switch(mode)
	{
		case TMR1_MODE_NORMAL:
			//clear all wave generation bits
			TCCR1A &= ~(1 << WGM10);
			TCCR1A &= ~(1 << WGM11);
			TCCR1B &= ~(1 << WGM12);
			TCCR1B &= ~(1 << WGM13);
		break;
		
		case TMR1_MODE_PHASE_CORRECT_8:
			//clear all wave generation bits and set the first bit
			TCCR1A |= (1 << WGM10);
			TCCR1A &= ~(1 << WGM11);
			TCCR1B &= ~(1 << WGM12);
			TCCR1B &= ~(1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_PHASE_CORRECT_9:
			//clear all wave generation bits and set the second bit
			TCCR1A &= ~(1 << WGM10);
			TCCR1A |= (1 << WGM11);
			TCCR1B &= ~(1 << WGM12);
			TCCR1B &= ~(1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_PHASE_CORRECT_10:
			//clear all wave generation bits and set the first 2 bits
			TCCR1A |= (1 << WGM10);
			TCCR1A |= (1 << WGM11);
			TCCR1B &= ~(1 << WGM12);
			TCCR1B &= ~(1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
					case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_CTC_OCR_TOP:
			//clear all wave generation bits and set the third bit
			TCCR1A &= ~(1 << WGM10);
			TCCR1A &= ~(1 << WGM11);
			TCCR1B |= (1 << WGM12);
			TCCR1B &= ~(1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_FAST_PWM_8:
			//clear all wave generation bits and set the first & third bit
			TCCR1A |= (1 << WGM10);
			TCCR1A &= ~(1 << WGM11);
			TCCR1B |= (1 << WGM12);
			TCCR1B &= ~(1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_FAST_PWM_9:
			//clear all wave generation bits and set the second & third bit
			TCCR1A &= ~(1 << WGM10);
			TCCR1A |= (1 << WGM11);
			TCCR1B |= (1 << WGM12);
			TCCR1B &= ~(1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_FAST_PWM_10:
			//clear all wave generation bits and set the first 3 bits
			TCCR1A |= (1 << WGM10);
			TCCR1A |= (1 << WGM11);
			TCCR1B |= (1 << WGM12);
			TCCR1B &= ~(1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_PHASE_FREQ_CORRECT_ICR_TOP:
			//clear all wave generation bits and set the fourth bit
			TCCR1A &= ~(1 << WGM10);
			TCCR1A &= ~(1 << WGM11);
			TCCR1B &= ~(1 << WGM12);
			TCCR1B |= (1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_PHASE_FREQ_CORRECT_OCR_TOP:
			//clear all wave generation bits and set the first & fourth bit
			TCCR1A |= (1 << WGM10);
			TCCR1A &= ~(1 << WGM11);
			TCCR1B &= ~(1 << WGM12);
			TCCR1B |= (1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_PHASE_CORRECT_ICR_TOP:
			//clear all wave generation bits and set the second & fourth bit
			TCCR1A &= ~(1 << WGM10);
			TCCR1A |= (1 << WGM11);
			TCCR1B &= ~(1 << WGM12);
			TCCR1B |= (1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_PHASE_CORRECT_OCR_TOP:
			//clear all wave generation bits and set the first 2 bits & fourth bit
			TCCR1A |= (1 << WGM10);
			TCCR1A |= (1 << WGM11);
			TCCR1B &= ~(1 << WGM12);
			TCCR1B |= (1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_CTC_ICR_TOP:
			//clear all wave generation bits and set the last 2 bits
			TCCR1A &= ~(1 << WGM10);
			TCCR1A &= ~(1 << WGM11);
			TCCR1B |= (1 << WGM12);
			TCCR1B |= (1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_FAST_PWM_ICR_TOP:
			//clear all wave generation bits and set the last 3 bits
			TCCR1A &= ~(1 << WGM10);
			TCCR1A |= (1 << WGM11);
			TCCR1B |= (1 << WGM12);
			TCCR1B |= (1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
		
		case TMR1_MODE_FAST_PWM_OCR_TOP:
			//set all bits
			TCCR1A |= (1 << WGM10);
			TCCR1A |= (1 << WGM11);
			TCCR1B |= (1 << WGM12);
			TCCR1B |= (1 << WGM13);
			//select output channel
			switch (channel_select)
			{
				case TMR1_OCRA:
					//define OC1A as output
					DDRB |= (1 << 5);
					//mode select
					TCCR1A |= (compare_mode << COM1A0);
				break;
				
				case TMR1_OCRB:
					//define OC1B as output
					DDRB |= (1 << 6);
					//mode select
					TCCR1A |= (compare_mode << COM1B0);
				break;
				
				case TMR1_OCRC:
					//define OC1C as output
					DDRB |= (1 << 7);
					//mode select
					TCCR1A |= (compare_mode << COM1C0);
				break;
			}
		break;
	}
	
	//enable icu
	if(icu_mode == TMR1_ICU_EN_RISING)
	{
		TCCR1B |= (1 << ICES1);
		//enable icu interrupt as well
		TIMSK |= (1 << TICIE1);
	}
	else if(icu_mode == TMR1_ICU_EN_FALLING)
	{
		TCCR1B &= ~(1 << ICES1);
		//enable icu interrupt as well
		TIMSK |= (1 << TICIE1);
	}
	
	//enable overflow interrupt
	if(overflow_int_mode == TMR1_OVERFLOW_INT_EN)
	{
		TIMSK |= (1 << TOIE1);
	}
	
	//enable compare interrupt
	if(compare_int_mode == TMR1_COMPARE_INT_EN)
	{
		switch(channel_select)
		{
			case TMR1_OCRA:
				TIMSK |= (1 << OCIE1A);
			break;
			
			case TMR1_OCRB:
				TIMSK |= (1 << OCIE1B);
			break;
			
			case TMR1_OCRC:
				ETIMSK |= (1 << OCIE1C);
			break;
		}
	}
}

void tmr1_start_timer(unsigned char prescaler_value)
{
	TCCR1B |= (prescaler_value << CS10);
}

void tmr1_stop_timer()
{
	//clear prescaler values
	TCCR1B &= 0xF8;
}

void tmr1_disable_interrupts()
{
	TIMSK &= ~(1 << TOIE1);
	TIMSK &= ~(1 << OCIE1A);
	TIMSK &= ~(1 << OCIE1B);
	ETIMSK &= ~(1 << OCIE1C);
}

void tmr1_set_ocr(unsigned char channel_select, unsigned short ocr_value)
{
	switch(channel_select)
	{
		case TMR1_OCRA:
			OCR1A = ocr_value;
		break;
		
		case TMR1_OCRB:
			OCR1B = ocr_value;
		break;
		
		case TMR1_OCRC:
			OCR1C = ocr_value;
		break;	
	}
}

void tmr1_set_icr(unsigned short icr_value)
{
	ICR1 = icr_value;
}

void tmr1_set_counter(unsigned short counter_value)
{
	TCNT1 = counter_value;
}

void tmr1_set_duty_cycle(unsigned char channel_select, unsigned short counter_top, unsigned char duty_cycle)
{
	unsigned short dc = 0;
	dc = duty_cycle * (counter_top / 100.0);
	switch(channel_select)
	{
		case TMR1_OCRA:
			tmr1_set_ocr(TMR1_OCRA, dc);
		break;
		
		case TMR1_OCRB:
			tmr1_set_ocr(TMR1_OCRB, dc);
		break;
		
		case TMR1_OCRC:
			tmr1_set_ocr(TMR1_OCRC, dc);
		break;
	}
}

void tmr1_change_capture_edge(unsigned char edge_select)
{
	if(edge_select == TMR1_ICU_EN_RISING)
	{
		TCCR1B |= (1 << ICES1);
	}
	else if(edge_select == TMR1_ICU_EN_FALLING)
	{
		TCCR1B &= ~(1 << ICES1);
	}
	else
	{
		TCCR1B ^= (1 << ICES1);
	}
}

void tmr1_compare_a_isr_callback( void (*ptr_isr)(void) )
{
	tmr1_compare_a_isr_ptr = ptr_isr;
}

void tmr1_compare_b_isr_callback( void (*ptr_isr)(void) )
{
	tmr1_compare_b_isr_ptr = ptr_isr;
}

void tmr1_compare_c_isr_callback( void (*ptr_isr)(void) )
{
	tmr1_compare_c_isr_ptr = ptr_isr;
}

void tmr1_overflow_isr_callback( void (*ptr_isr)(void) )
{
	tmr1_overflow_isr_ptr = ptr_isr;
}

void tmr1_capture_isr_callback( void (*ptr_isr)(void) )
{
	tmr1_capture_isr_ptr = ptr_isr;
}

ISR(TIMER1_CAPT_vect)
{
	(*tmr1_capture_isr_ptr)();
}

ISR(TIMER1_COMPA_vect)
{
	(*tmr1_compare_a_isr_ptr)();
}

ISR(TIMER1_COMPB_vect)
{
	(*tmr1_compare_b_isr_ptr)();
}

ISR(TIMER1_COMPC_vect)
{
	(*tmr1_compare_c_isr_ptr)();
}

ISR(TIMER1_OVF_vect)
{
	(*tmr1_overflow_isr_ptr)();
}
