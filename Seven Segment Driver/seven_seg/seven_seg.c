#include "seven_seg.h"

void seg_init()
{
	//segment data port output
	SEG_DATA_DIRC = 0xFF;
	
	//segment ctrl pin output if any more ctrl pins are added define them as output here
	SEG_CTRL_DIRC |= (1 << SEG_CTRL_PIN0);
	SEG_CTRL_DIRC |= (1 << SEG_CTRL_PIN1);
	SEG_CTRL_DIRC |= (1 << SEG_CTRL_PIN2);
	SEG_CTRL_DIRC |= (1 << SEG_CTRL_PIN3);
	
	//segment initially off
	SEG_DATA_PORT = 0xFF;
}

static unsigned char seg_num[10] = {SEG_0, SEG_1, SEG_2, SEG_3, SEG_4, SEG_5, SEG_6, SEG_7, SEG_8, SEG_9};
static unsigned char seg_num_dp[10] = {SEGD_0, SEGD_1, SEGD_2, SEGD_3, SEGD_4, SEGD_5, SEGD_6, SEGD_7, SEGD_8, SEGD_9};

void seg_disp_digit(unsigned char num, unsigned char digit_select)
{
	//select digit to display number on
	SEG_CTRL_PORT |= (1 << digit_select);
	//check if number sent has the last bit as one, indicator to print decimal point with number
	if( ( (num >> 7) & 1 ) == 1 )
	{
		num &= ~(1 << 7);
		SEG_DATA_PORT = seg_num_dp[num];
	}
	else
	{
		SEG_DATA_PORT = seg_num[num];
	}
	//display for 1ms
	_delay_ms(1);
	//remove select
	SEG_CTRL_PORT &= ~(1 << digit_select);
}

void seg_disp_4digits(unsigned short int_num)
{
	unsigned char loopCounter = 3;
	unsigned char printed_digit = 0;
	while (loopCounter != 255)  //255 overflow after decrementing from zero
	{
		//get last digit
		printed_digit = int_num % 10;
		//display it
		seg_disp_digit(printed_digit, loopCounter);
		//remove last digit
		int_num = int_num / 10;
		//move to the digit before
		loopCounter--;
	}
}

void seg_disp_4digits_float(float float_num)
{
	float float_num_copy = float_num;
	unsigned char decimal_point_finder = 0;
	unsigned char loopCounter = 4;
	unsigned char printed_digit = 0;
	
	//look for decimal point after which digit if number is above 1
	while(float_num > 1)
	{
		float_num = float_num / 10;
		decimal_point_finder++;
	}
	
	//multiply by the number of digits to make no decimal point at all in the digits to be printed
	for(loopCounter = 0; loopCounter < (4 - decimal_point_finder); loopCounter++)
	{
		if(float_num_copy < 1)	//number below 1, decimal point after first digit
		{
			float_num_copy = float_num_copy * 1000;
		}
		else if(decimal_point_finder != 0) //number above 1, decimal point can be after any digit
		{
			float_num_copy = float_num_copy * 10;
		}
	}
	
	//printing the float number after getting the dp place and all the digits
	loopCounter = 3;
	while (loopCounter != 255) //255 overflow after decrementing from zero
	{
		printed_digit = (unsigned int)float_num_copy % 10;			//cast into unsigned int
		if(loopCounter == decimal_point_finder - 1)					//check for the digit to put dp after for numbers bigger than 1
		{
			printed_digit |= (1 << 7);		//put one on last bit to print decimal point after it
			seg_disp_digit(printed_digit, loopCounter);
		}
		else if(decimal_point_finder == 0 && loopCounter == 0)		//check dp should be put after 0 in the last digit for numbers less than 1
		{
			printed_digit |= (1 << 7);		//put one on last bit to print decimal point after it
			seg_disp_digit(printed_digit, loopCounter);
		}
		else														//print normally with no dp
		{
			seg_disp_digit(printed_digit, loopCounter);
		}
		//remove the printed digit
		float_num_copy = float_num_copy / 10;
		//move to the number before
		loopCounter--;
	}
}
