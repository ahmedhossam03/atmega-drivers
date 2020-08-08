#include "ir.h"

//ir is normally high and gives low when something on the way

//normal pin mode variables and functions
static unsigned char ir_new_state = 1;
static unsigned char ir_old_state = 1;
static void ir_read();

//interrupt mode variables & functions
volatile ir_state ir_edge_flag = 0;
static void ir_interrupt();

//used by both
volatile ir_state state = ir_no_change;

void ir_init(unsigned char mode)
{
	//enable external interrupt on falling edge
	switch(mode)
	{
		case IR_MODE_INT:
			//initialize interrupt
			exti_init(IR_PIN);
			//enable interrupt
			exti_onoff(IR_PIN, 1);
			//make mode falling
			exti_change_mode(IR_PIN, EXTI_FALLING);
			//send function to ISR
			exti_callback(ir_interrupt, IR_PIN);
		break;
		
		case IR_MODE_PIN:
			//define IR pin as input
			IR_DDR &= ~(1 << IR_PIN);
		break;
	}
}

void ir_read()
{
	//read and put data in new state
	ir_new_state = (IR_PORT >> IR_PIN) & 0x01;
	//check if any change occurred
	if(ir_new_state == 0 && ir_old_state == 1)
		state = ir_obstacle;
	else if(ir_new_state == 1 && ir_old_state == 0)
		state = ir_no_obstacle;
	//put new state in old state
	ir_old_state = ir_new_state;
}

void ir_interrupt()
{
	if(ir_edge_flag == 0)
	{
		ir_edge_flag = 1;
		exti_change_mode(IR_PIN, EXTI_RISING);
		state = ir_obstacle;
	}
	else if(ir_edge_flag == 1)
	{
		ir_edge_flag = 0;
		exti_change_mode(IR_PIN, EXTI_FALLING);
		state = ir_no_obstacle;
	}
}

ir_state ir_get_state(unsigned char mode)
{
	switch(mode)
	{
		case IR_MODE_INT:
		//do nothing interrupt does everything
		break;
		
		case IR_MODE_PIN:
		ir_read();
		break;
	}
	return state;
}
