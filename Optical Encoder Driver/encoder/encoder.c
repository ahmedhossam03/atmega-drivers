#include "avr/io.h"
#include "encoder.h"
#include "../ext_interrupt/ext_interrupt.h"

//interrupt mode functions
static void encoder_ang_calc_a_int(void);
static void encoder_ang_calc_b_int(void);

//normal pin mode functions and variables
static void encoder_ang_calc_pin(void);
static unsigned char encoder_pin_a_new_state = 0;
static unsigned char encoder_pin_b_new_state = 0;
static unsigned char encoder_pin_a_old_state = 0;
static unsigned char encoder_pin_b_old_state = 0;

//used by both modes
//the dirc variable is to make sure that no incrementing / decrementing happens twice
//because two same edges come after each other on the 2 channels
//2 is the sync number for rotating anti-clockwise
//1 is the sync number for rotating clockwise
//0 is the number to avoid any confusion for both sync cases
static unsigned char dirc = 0;
static unsigned char encoder_pin_a = 0;
static unsigned char encoder_pin_b = 0;
static unsigned short int motor_angle = 0;

//no pull up needed
#define EXTI_PULLUP_INPUT 0
//choosing trigger event of the encoder
#define EXTI_MODE EXTI_RISING

void encoder_init(unsigned char enc_pin_a, unsigned char enc_pin_b, unsigned char mode)
{
	//select pins for the encoder
	encoder_pin_a = enc_pin_a;
	encoder_pin_b = enc_pin_b;
	//check which interrupt or normal
	switch(mode)
	{
		//using interrupts
		case ENC_MODE_INT:
			//initialize interrupts for encoder pin A and B
			exti_void_init(encoder_pin_a);
			exti_void_init(encoder_pin_b);
			//enable interrupts for pins
			exti_void_onoff(encoder_pin_a, 1);
			exti_void_onoff(encoder_pin_b, 1);
			//send to isr to calc
			exti_void_callback(encoder_ang_calc_a_int, encoder_pin_a);
			exti_void_callback(encoder_ang_calc_b_int, encoder_pin_b);
		break;
		
		case ENC_MODE_PIN:
			//define pins as input with no pullup
			ENC_PIN_INPUT_DIR &= ~(1 << encoder_pin_a);
			ENC_PIN_INPUT_DIR &= ~(1 << encoder_pin_b);
		break;
	}
}

void encoder_ang_calc_pin()
{
	//reading states of pin a and b
	encoder_pin_a_new_state = (ENC_PIN_INPUT >> encoder_pin_a) & 0x01;
	encoder_pin_b_new_state = (ENC_PIN_INPUT >> encoder_pin_b) & 0x01;
	//check for rising edge for pin a
	if(encoder_pin_a_new_state == 1 && encoder_pin_a_old_state == 0)
	{
		if(encoder_pin_b_new_state == 0) //rotating clock wise
		{
			//check if this is the first rising edge or not
			if(dirc == 1)
			{
				//second rising edge
				if(motor_angle == 360)
					motor_angle = 0;
				motor_angle += ENC_RES;
				//angle incrementing complete clear var to check for new case
				dirc = 0;
			}
			else
			{
				//first rising edge
				dirc = 1;
			}
		}
		else if(encoder_pin_b_new_state == 1) //rotating anti-clock
		{
			if(dirc == 2)
			{
				//second rising edge
				if(motor_angle == 0)
					motor_angle = 360;
				motor_angle -= ENC_RES;
				//angle decrementing complete clear var to check for new case
				dirc = 0;
			}
			else
			{
				//first rising edge
				dirc = 2;
			}
		}
	} 
	//check for rising edge for pin b
	else if(encoder_pin_b_new_state == 1 && encoder_pin_b_old_state == 0)
	{
		if(encoder_pin_a_new_state == 1) //rotating clockwise
		{
			if(dirc == 1)
			{
				if(motor_angle == 360)
					motor_angle = 0;
				motor_angle += ENC_RES;
				dirc = 0;
			}
			else
			{
				dirc = 1;
			}
		}
		else if(encoder_pin_a_new_state == 0) //rotating anti-clockwise
		{
			if(dirc == 2)
			{
				if(motor_angle == 0)
					motor_angle = 360;
				motor_angle -= ENC_RES;
				dirc = 0;
			}
			else
			{
				dirc = 2;
			}
		}
	}
	//put new state in old state
	encoder_pin_a_old_state = encoder_pin_a_new_state;
	encoder_pin_b_old_state = encoder_pin_b_new_state;
}

unsigned short int encoder_get_angle(unsigned char mode)
{
	switch(mode)
	{
		case ENC_MODE_INT:
			//do nothing the interrupt does it all
		break;
		
		case ENC_MODE_PIN:
			//call calc function
			encoder_ang_calc_pin();
		break;
	}
	
	return motor_angle;
}

void encoder_ang_calc_a_int(void)
{
	//check if it's rotating clockwise or anti-clockwise to add or subtract
	if( ( (ENC_PIN_INPUT >> encoder_pin_b) & 1 ) == 1 )			//anti-clockwise
	{
		if(dirc == 2)
		{
			if(motor_angle == 0)
				motor_angle = 360;
			motor_angle -= ENC_RES;
			dirc = 0;
		}
		else
		{
			dirc = 2;
		}
	}
	else if( ( (ENC_PIN_INPUT >> encoder_pin_b) & 1 ) == 0 )	//clockwise
	{
		if(dirc == 1)
		{
			if(motor_angle == 360)
				motor_angle = 0;
			motor_angle += ENC_RES;
			dirc = 0;
		}
		else
		{
			dirc = 1;
		}
	}
}

void encoder_ang_calc_b_int(void)
{
	//check if it's rotating clockwise or anti-clockwise to add or subtract
	if( ( (ENC_PIN_INPUT >> encoder_pin_a) & 1 ) == 1 )			//clockwise
	{
		if(dirc == 1)
		{
			if(motor_angle == 360)
				motor_angle = 0;
			motor_angle += ENC_RES;
			dirc = 0;
		}
		else
		{
			dirc = 1;
		}
	}
	else if( ( (ENC_PIN_INPUT >> encoder_pin_a) & 1 ) == 0 )	//anti-clockwise
	{
		if(dirc == 2)
		{
			if(motor_angle == 0)
				motor_angle = 360;
			motor_angle -= ENC_RES;
			dirc = 0;
		}
		else
		{
			dirc = 2;
		}
	}
}
