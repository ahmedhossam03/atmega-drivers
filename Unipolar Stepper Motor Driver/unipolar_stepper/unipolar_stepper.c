#include "unipolar_stepper.h"

unsigned char steps[] = {0x09, 0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01};
unsigned char step_counter_1 = 0;
unsigned char current_step_1 = 0;

void uni_stepper_init()
{
	//initialize stepper pins as output
	setBit(UNI_STEPPER_1_DDR, UNI_STEPPER_1_PIN_1);
	setBit(UNI_STEPPER_1_DDR, UNI_STEPPER_1_PIN_2);
	setBit(UNI_STEPPER_1_DDR, UNI_STEPPER_1_PIN_3);
	setBit(UNI_STEPPER_1_DDR, UNI_STEPPER_1_PIN_4);
}

void uni_stepper_increment_clkwise()
{
	step_counter_1++;
	if(step_counter_1 == 8)
	{
		step_counter_1 = 0;	
	}
	//clear bits to write in
	UNI_STEPPER_1_PORT &= 0xF0;
	//put angle step on port
	UNI_STEPPER_1_PORT |= steps[step_counter_1];
	//minimum delay for motor req
	_delay_ms(UNI_STEPPER_DELAY);
  if(current_step_1 == UNI_360_STEPS)
	{
		current_step_1 = 0;
	}
	current_step_1++;
}

void uni_stepper_increment_anticlk()
{
	step_counter_1--;
	if(step_counter_1 == 255)
	{
		step_counter_1 = 7;
	}
	//clear bits to write in
	UNI_STEPPER_1_PORT &= 0xF0;
	//put angle step on port
	UNI_STEPPER_1_PORT |= steps[step_counter_1];
	//minimum delay for motor req
	_delay_ms(UNI_STEPPER_DELAY);
	if(current_step_1 == 0)
	{
		current_step_1 = UNI_360_STEPS;
	}
	current_step_1--;
}

void uni_stepper_goto_zero_clkwise()
{
	while(current_step_1 != 0)
	{
		uni_stepper_increment_clkwise();
	}
}

void uni_stepper_goto_zero_anticlk()
{
	while(current_step_1 != 0)
	{
		uni_stepper_increment_anticlk();
	}
}

void uni_stepper_goto_90_clkwise()
{
	while(current_step_1 != 48) //48 is the number of steps to be taken to get to 270 from 0
	{
		uni_stepper_increment_clkwise();
	}
		
}

void uni_stepper_goto_90_anticlk()
{
	while(current_step_1 != 16) //16 is number of steps to be taken to get to 90 from 0
	{
		uni_stepper_increment_anticlk();
	}
}

void uni_stepper_goto_180_clkwise()
{
	while(current_step_1 != 32) //32 is number of steps to be taken to get to 180 from 0
	{
		uni_stepper_increment_clkwise();
	}
}

void uni_stepper_goto_180_anticlk()
{
	while(current_step_1 != 32) //32 is number of steps to be taken to get to 180 from 0
	{
		uni_stepper_increment_anticlk();
	}
}
