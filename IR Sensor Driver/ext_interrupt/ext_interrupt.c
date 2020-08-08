#include "ext_interrupt.h"
#include "avr/io.h"
#include "avr/interrupt.h"

void exti_init(unsigned char exti_select)
{
	//interrupt pin as input
	if(exti_select < 4)
	{
		DDRD &= ~(1 << exti_select);		//input
		#if (EXTI_PULLUP_INPUT == 1)
			PORTD |= (1 << exti_select);	//activate pull up
		#endif
	}
	else if(exti_select >= 4)
	{
		DDRE &= ~(1 << exti_select);		//input
		#if (EXTI_PULLUP_INPUT == 1)
			PORTE |= (1 << exti_select);	//activate pull up
		#endif
	}
}

void exti_onoff(unsigned char exti_select, unsigned char status)
{
	if(status == 1)			    //enabling interrupt
		EIMSK |= (1 << exti_select);
	else if(status == 0)		//disabling interrupt
		EIMSK &= ~(1 << exti_select);
}

void exti_change_mode(unsigned char exti_select, unsigned char exti_mode)
{
	//interrupt trigger action
	if(exti_select < 4)
	{
		EICRA |= ( exti_mode << (exti_select * 2) );
	}
	else if(exti_select >= 4)
	{
		EICRB |= ( exti_mode << ( (exti_select - 4) * 2 ) );
	}
}

void (*ptr_to_callback[8])(void);
void exti_callback(void (*ptr_service_func)(void), unsigned char exti_select)
{
	ptr_to_callback[exti_select] = ptr_service_func;
}

ISR(INT0_vect)
{
	//execute the function made by user
	(*ptr_to_callback[0])();
}

ISR(INT1_vect)
{
	//execute the function made by user
	(*ptr_to_callback[1])();
}

ISR(INT2_vect)
{
	//execute the function made by user
	(*ptr_to_callback[2])();
}

ISR(INT3_vect)
{
	//execute the function made by user
	(*ptr_to_callback[3])();
}

ISR(INT4_vect)
{
	//execute the function made by user
	(*ptr_to_callback[4])();
}

ISR(INT5_vect)
{
	//execute the function made by user
	(*ptr_to_callback[5])();
}

ISR(INT6_vect)
{
	//execute the function made by user
	(*ptr_to_callback[6])();
}

ISR(INT7_vect)
{
	//execute the function made by user
	(*ptr_to_callback[7])();
}
