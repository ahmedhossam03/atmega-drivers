#include "tmr2.h"

static void (*tmr2_overflow_isr_ptr)(void);
static void (*tmr2_compare_isr_ptr)(void);

void tmr2_init(unsigned char mode, unsigned char compare_mode, unsigned char overflow_int_enable, unsigned char compare_int_enable)
{
	switch(mode)
	{
		case TMR2_MODE_NORMAL:
		//clear waveform generation bits
		TCCR2 &= ~(1 << WGM20);
		TCCR2 &= ~(1 << WGM21);
		break;
		
		case TMR2_MODE_PHASE_CORRECT:
		//clear bit 1 and set bit 0 waveform generation
		TCCR2 |= (1 << WGM20);
		TCCR2 &= ~(1 << WGM21);
		//make compare pin output
		DDRB |= (1 << 7);
		//compare mode
		TCCR2 |= (compare_mode << COM20);
		break;
		
		case TMR2_MODE_CTC:
		//set bit 1 and clear bit 0 waveform generation
		TCCR2 &= ~(1 << WGM20);
		TCCR2 |= (1 << WGM21);
		//make compare pin output
		DDRB |= (1 << 7);
		//compare mode
		TCCR2 |= (compare_mode << COM20);
		break;
		
		case TMR2_MODE_FAST_PWM:
		//set waveform generation bits
		TCCR2 |= (1 << WGM20);
		TCCR2 |= (1 << WGM21);
		//make compare pin output
		DDRB |= (1 << 7);
		//compare mode
		TCCR2 |= (compare_mode << COM20);
		break;
	}
	//enable overflow interrupt
	if(overflow_int_enable == TMR2_OVERFLOW_INT_EN)
	{
		TIMSK |= (1 << TOIE2);
	}
	//enable output compare interrupt
	if(compare_int_enable == TMR2_COMPARE_INT_EN)
	{
		TIMSK |= (1 << OCIE2);
	}
}

void tmr2_start_timer(unsigned char prescaler_value)
{
	//setting clock starts timers
	TCCR2 |= (prescaler_value << CS20);
}

void tmr2_stop_timer()
{
	//clear prescaler to stop timer
	TCCR2 &= 0xF8;
}

void tmr2_disable_interrupts()
{
	//disable interrupts
	TIMSK &= ~(1 << TOIE2);
	TIMSK &= ~(1 << OCIE2);
}

void tmr2_set_ocr(unsigned char ocr_value)
{
	OCR2 = ocr_value;
}

void tmr2_set_counter(unsigned char counter_value)
{
	TCNT2 = counter_value;
}

void tmr2_set_duty_cycle(unsigned char duty_cycle)
{
	//256 is 100%
	tmr2_set_ocr( (duty_cycle * 255UL) / 100 );
}

void tmr2_overflow_isr_callback( void (*ptr_callback)(void) )
{
	tmr2_overflow_isr_ptr = ptr_callback;
}

void tmr2_compare_isr_callback( void (*ptr_callback)(void) )
{
	tmr2_compare_isr_ptr = ptr_callback;
}

ISR(TIMER2_COMP_vect)
{
	(*tmr2_compare_isr_ptr)();
}

ISR(TIMER2_OVF_vect)
{
	(*tmr2_overflow_isr_ptr)();
}
