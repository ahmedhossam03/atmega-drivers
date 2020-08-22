#include "bipolar_stepper.h"

static unsigned char full_step_array_1[] = {0x08, 0x02, 0x04, 0x01};
static unsigned char full_step_array_2[] = {0x09, 0x0A, 0x06, 0x05};
static unsigned char half_step_array[] = {0x09, 0x08, 0x0A, 0x02, 0x06, 0x04, 0x05, 0x01};
	
static unsigned char step_array_counter = 0;
static unsigned short current_step = 0;		//short because in half stepping mode 400 steps in rev

static void bi_stepper_clear_pins()
{
	BI_STEPPER_PORT &= ~(1 << BI_STEPPER_RED);
	BI_STEPPER_PORT &= ~(1 << BI_STEPPER_GRN);
	BI_STEPPER_PORT &= ~(1 << BI_STEPPER_YLW);
	BI_STEPPER_PORT &= ~(1 << BI_STEPPER_BLU);
}

static void bi_stepper_write_pins(unsigned char step)
{
	BI_STEPPER_PORT |= (step << BI_STEPPER_RED);
}

void bi_stepper_init(unsigned char step_angle_mode)
{
	//define stepper pins as output
	BI_STEPPER_DDR |= (1 << BI_STEPPER_RED);
	BI_STEPPER_DDR |= (1 << BI_STEPPER_GRN);
	BI_STEPPER_DDR |= (1 << BI_STEPPER_YLW);
	BI_STEPPER_DDR |= (1 << BI_STEPPER_BLU);
	//choose mode of operation
	switch(step_angle_mode)
	{
		case BI_HALF_STEP_MODE:
			step_array_counter = sizeof(half_step_array) - 1;
			bi_stepper_write_pins( half_step_array[step_array_counter] );
		break;
		
		case BI_FULL_STEP_MODE_1:
			step_array_counter = sizeof(full_step_array_1) - 1;
			bi_stepper_write_pins( full_step_array_1[step_array_counter] );
		break;
		
		case BI_FULL_STEP_MODE_2:
			step_array_counter = sizeof(full_step_array_2) - 1;
			bi_stepper_write_pins( full_step_array_2[step_array_counter] );
		break;
	}
}

void bi_stepper_inc_clkwise(unsigned char step_angle_mode)
{
	switch(step_angle_mode)
	{
		case BI_HALF_STEP_MODE:
			//moving backward on the array is rotating clockwise
			step_array_counter--;
			//make sure counter doesn't go out of range
			if(step_array_counter == 255) //255 is the underflow value after decrementing zero
			{
				step_array_counter = sizeof(half_step_array) - 1;	//index of last element
			}
			//clear pins before writing in
			bi_stepper_clear_pins();
			//write step output on pins
			bi_stepper_write_pins( half_step_array[step_array_counter] );
			//delay after the step
			_delay_ms(BI_STEP_DELAY);
			//increment current step of the stepper
			current_step++;
			//make sure current step is in a single revolution range
			if(current_step == BI_360_HALF)
			{
				current_step = 0;
			}
		break;
		
		case BI_FULL_STEP_MODE_1:
			//moving backward on the array is rotating clockwise
			step_array_counter--;
			//make sure counter doesn't go out of range
			if(step_array_counter == 255) //255 is the underflow value after decrementing zero
			{
				step_array_counter = sizeof(full_step_array_1) - 1;	//index of last element
			}
			//clear pins before writing in
			bi_stepper_clear_pins();
			//write step output on pins
			bi_stepper_write_pins( full_step_array_1[step_array_counter] );
			//delay after the step
			_delay_ms(BI_STEP_DELAY);
			//increment current step of the stepper
			current_step++;
			//make sure current step is in a single revolution range
			if(current_step == BI_360_STEPS)
			{
				current_step = 0;
			}
		break;
		
		case BI_FULL_STEP_MODE_2:
			//moving backward on the array is rotating clockwise
			step_array_counter--;
			//make sure counter doesn't go out of range
			if(step_array_counter == 255) //255 is the underflow value after decrementing zero
			{
				step_array_counter = sizeof(full_step_array_2) - 1;	//index of last element
			}
			//clear pins before writing in
			bi_stepper_clear_pins();
			//write step output on pins
			bi_stepper_write_pins( full_step_array_2[step_array_counter] );
			//delay after the step
			_delay_ms(BI_STEP_DELAY);
			//increment current step of the stepper
			current_step++;
			//make sure current step is in a single revolution range
			if(current_step == BI_360_STEPS)
			{
				current_step = 0;
			}
		break;
	}
}

void bi_stepper_inc_anticlk(unsigned char step_angle_mode)
{
	switch(step_angle_mode)
	{
		case BI_HALF_STEP_MODE:
			//moving forward on the array is rotating anti clockwise
			step_array_counter++;
			//make sure counter doesn't go out of range
			if( step_array_counter == sizeof(half_step_array) ) //size of the array is the index of the element after the lasr
			{
				step_array_counter = 0;	//index of first element
			}
			//clear pins before writing in
			bi_stepper_clear_pins();
			//write step output on pins
			bi_stepper_write_pins( half_step_array[step_array_counter] );
			//delay after the step
			_delay_ms(BI_STEP_DELAY);
			//make sure current step is in a single revolution range
			if(current_step == 0)
			{
				current_step = BI_360_HALF;
			}
			//decrement current step of the stepper
			current_step--;
		break;
		
		case BI_FULL_STEP_MODE_1:
			//moving forward on the array is rotating anti clockwise
			step_array_counter++;
			//make sure counter doesn't go out of range
			if( step_array_counter == sizeof(full_step_array_1) ) //size of the array is the index of the element after the lasr
			{
				step_array_counter = 0;	//index of first element
			}
			//clear pins before writing in
			bi_stepper_clear_pins();
			//write step output on pins
			bi_stepper_write_pins( full_step_array_1[step_array_counter] );
			//delay after the step
			_delay_ms(BI_STEP_DELAY);
			//make sure current step is in a single revolution range
			if(current_step == 0)
			{
				current_step = BI_360_STEPS;
			}
			//decrement current step of the stepper
			current_step--;
		break;
		
		case BI_FULL_STEP_MODE_2:
			//moving forward on the array is rotating anti clockwise
			step_array_counter++;
			//make sure counter doesn't go out of range
			if( step_array_counter == sizeof(full_step_array_2) ) //size of the array is the index of the element after the lasr
			{
				step_array_counter = 0;	//index of first element
			}
			//clear pins before writing in
			bi_stepper_clear_pins();
			//write step output on pins
			bi_stepper_write_pins( full_step_array_2[step_array_counter] );
			//delay after the step
			_delay_ms(BI_STEP_DELAY);
			//make sure current step is in a single revolution range
			if(current_step == 0)
			{
				current_step = BI_360_STEPS;
			}
			//decrement current step of the stepper
			current_step--;
		break;
	}
}

void bi_stepper_goto_zero_clkwise(unsigned char step_angle_mode)
{
	switch(step_angle_mode)
	{
		case BI_HALF_STEP_MODE:
			while(current_step != 0)
			{
				bi_stepper_inc_clkwise(BI_HALF_STEP_MODE);
			}
		break;
		
		case BI_FULL_STEP_MODE_1:
			while(current_step != 0)
			{
				bi_stepper_inc_clkwise(BI_FULL_STEP_MODE_1);
			}
		break;
		
		case BI_FULL_STEP_MODE_2:
			while(current_step != 0)
			{
				bi_stepper_inc_clkwise(BI_FULL_STEP_MODE_2);
			}
		break;
	}
}

void bi_stepper_goto_zero_anticlk(unsigned char step_angle_mode)
{
	switch (step_angle_mode)
	{
		case BI_HALF_STEP_MODE:
			while(current_step != 0)
			{
				bi_stepper_inc_anticlk(BI_HALF_STEP_MODE);
			}
		break;
		
		case BI_FULL_STEP_MODE_1:
		while(current_step != 0)
		{
			bi_stepper_inc_anticlk(BI_FULL_STEP_MODE_1);
		}
		break;
		
		case BI_FULL_STEP_MODE_2:
			while(current_step != 0)
			{
				bi_stepper_inc_anticlk(BI_FULL_STEP_MODE_2);
			}
		break;
	}
}

void bi_stepper_goto_90_clkwise(unsigned char step_angle_mode)
{
	switch(step_angle_mode)
	{
		case BI_HALF_STEP_MODE:
			while( current_step != (BI_360_HALF / 4) )
			{
				bi_stepper_inc_clkwise(BI_HALF_STEP_MODE);
			}
		break;
		
		case BI_FULL_STEP_MODE_1:
			while( current_step != (BI_360_STEPS / 4) )
			{
				bi_stepper_inc_clkwise(BI_FULL_STEP_MODE_1);
			}
		break;
		
		case BI_FULL_STEP_MODE_2:
			while( current_step != (BI_360_STEPS / 4) )
			{
				bi_stepper_inc_clkwise(BI_FULL_STEP_MODE_2);
			}
		break;
	}
}

void bi_stepper_goto_90_anticlk(unsigned char step_angle_mode)
{
	switch (step_angle_mode)
	{
		case BI_HALF_STEP_MODE:
			while( current_step != (BI_360_HALF / 4) )
			{
				bi_stepper_inc_anticlk(BI_HALF_STEP_MODE);
			}
		break;
		
		case BI_FULL_STEP_MODE_1:
			while( current_step != (BI_360_STEPS / 4) )
			{
				bi_stepper_inc_anticlk(BI_FULL_STEP_MODE_1);
			}
		break;
		
		case BI_FULL_STEP_MODE_2:
			while( current_step != (BI_360_STEPS / 4) )
			{
				bi_stepper_inc_anticlk(BI_FULL_STEP_MODE_2);
			}
		break;
	}
}

void bi_stepper_goto_180_clkwise(unsigned char step_angle_mode)
{
	switch(step_angle_mode)
	{
		case BI_HALF_STEP_MODE:
			while( current_step != (BI_360_HALF / 2) )
			{
				bi_stepper_inc_clkwise(BI_HALF_STEP_MODE);
			}
		break;
		
		case BI_FULL_STEP_MODE_1:
			while( current_step != (BI_360_STEPS / 2) )
			{
				bi_stepper_inc_clkwise(BI_FULL_STEP_MODE_1);
			}
		break;
		
		case BI_FULL_STEP_MODE_2:
			while( current_step != (BI_360_STEPS / 2) )
			{
				bi_stepper_inc_clkwise(BI_FULL_STEP_MODE_2);
			}
		break;
	}
}

void bi_stepper_goto_180_anticlk(unsigned char step_angle_mode)
{
	switch (step_angle_mode)
	{
		case BI_HALF_STEP_MODE:
			while( current_step != (BI_360_HALF / 2) )
			{
				bi_stepper_inc_anticlk(BI_HALF_STEP_MODE);
			}
		break;
		
		case BI_FULL_STEP_MODE_1:
			while( current_step != (BI_360_STEPS / 2) )
			{
				bi_stepper_inc_anticlk(BI_FULL_STEP_MODE_1);
			}
		break;
		
		case BI_FULL_STEP_MODE_2:
			while( current_step != (BI_360_STEPS / 2) )
			{
				bi_stepper_inc_anticlk(BI_FULL_STEP_MODE_2);
			}
		break;
	}
}

void bi_stepper_goto_270_clkwise(unsigned char step_angle_mode)
{
	switch(step_angle_mode)
	{
		case BI_HALF_STEP_MODE:
			while( current_step != ( (BI_360_HALF / 4) * 3 ) )
			{
				bi_stepper_inc_clkwise(BI_HALF_STEP_MODE);
			}
		break;
		
		case BI_FULL_STEP_MODE_1:
			while( current_step != ( (BI_360_STEPS / 4) * 3 ) )
			{
				bi_stepper_inc_clkwise(BI_FULL_STEP_MODE_1);
			}
		break;
		
		case BI_FULL_STEP_MODE_2:
			while( current_step != ( (BI_360_STEPS / 4) * 3 ) )
			{
				bi_stepper_inc_clkwise(BI_FULL_STEP_MODE_2);
			}
		break;
	}
}

void bi_stepper_goto_270_anticlk(unsigned char step_angle_mode)
{
	switch (step_angle_mode)
	{
		case BI_HALF_STEP_MODE:
			while( current_step != ( (BI_360_HALF / 4) * 3 ) )
			{
				bi_stepper_inc_anticlk(BI_HALF_STEP_MODE);
			}
		break;
		
		case BI_FULL_STEP_MODE_1:
			while( current_step != ( (BI_360_STEPS / 4) * 3 ) )
			{
				bi_stepper_inc_anticlk(BI_FULL_STEP_MODE_1);
			}
		break;
		
		case BI_FULL_STEP_MODE_2:
			while( current_step != ( (BI_360_STEPS / 4) * 3 ) )
			{
				bi_stepper_inc_anticlk(BI_FULL_STEP_MODE_2);
			}
		break;
	}
}
