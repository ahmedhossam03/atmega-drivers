#include "tmr0.h"

static void (*tmr0_overflow_isr_ptr)(void);
static void (*tmr0_compare_isr_ptr)(void);

void tmr0_init(unsigned char mode, unsigned char compare_mode, unsigned char overflow_int_enable, unsigned char compare_int_enable)
{
	switch(mode)
	{
		case TMR0_MODE_NORMAL:
			//clear waveform generation bits
			TCCR0 &= ~(1 << WGM00);
			TCCR0 &= ~(1 << WGM01);
		break;
		
		case TMR0_MODE_PHASE_CORRECT:
			//clear bit 1 and set bit 0 waveform generation
			TCCR0 |= (1 << WGM00);
			TCCR0 &= ~(1 << WGM01);
			//make compare pin output
			DDRB |= (1 << 4);
			//compare mode
			TCCR0 |= (compare_mode << COM00);
		break;
		
		case TMR0_MODE_CTC:
			//set bit 1 and clear bit 0 waveform generation
			TCCR0 &= ~(1 << WGM00);
			TCCR0 |= (1 << WGM01);
			//make compare pin output
			DDRB |= (1 << 4);
			//compare mode
			TCCR0 |= (compare_mode << COM00);
		break;
		
		case TMR0_MODE_FAST_PWM:
			//set waveform generation bits
			TCCR0 |= (1 << WGM00);
			TCCR0 |= (1 << WGM01);
			//make compare pin output
			DDRB |= (1 << 4);
			//compare mode
			TCCR0 |= (compare_mode << COM00);
		break;
	}
	//enable overflow interrupt
	if(overflow_int_enable == TMR0_OVERFLOW_INT_EN)
	{
		TIMSK |= (1 << TOIE0);
	}
	//enable output compare interrupt
	if(compare_int_enable == TMR0_COMPARE_INT_EN)
	{
		TIMSK |= (1 << OCIE0);
	}
}

void tmr0_start_timer(unsigned char prescaler_value)
{
	//setting clock starts timers
	TCCR0 |= (prescaler_value << CS00);
}

void tmr0_stop_timer()
{
	//clear prescaler to stop timer
	TCCR0 &= 0xF8;
}

void tmr0_disable_interrupts()
{
	//disable interrupts
	TIMSK &= ~(1 << TOIE0);
	TIMSK &= ~(1 << OCIE0);
}

void tmr0_set_ocr(unsigned char ocr_value)
{
	OCR0 = ocr_value;
}

void tmr0_set_counter(unsigned char counter_value)
{
	TCNT0 = counter_value;
}

void tmr0_set_duty_cycle(unsigned char duty_cycle)
{
	//256 is 100%
	tmr0_set_ocr( (duty_cycle * 255UL) / 100 );
}

void tmr0_overflow_isr_callback( void (*ptr_callback)(void) )
{
	tmr0_overflow_isr_ptr = ptr_callback;
}

void tmr0_compare_isr_callback( void (*ptr_callback)(void) )
{
	tmr0_compare_isr_ptr = ptr_callback;
}

ISR(TIMER0_COMP_vect)
{
	(*tmr0_compare_isr_ptr)();
}

ISR(TIMER0_OVF_vect)
{
	(*tmr0_overflow_isr_ptr)();
}
