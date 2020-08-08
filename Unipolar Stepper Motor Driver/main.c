#include "unipolar_stepper/unipolar_stepper.h
#include "util/delay.h"
#include "avr/io.h"

int main(void)
{
  //initialize stepper
	uni_stepper_init();
    	while(1)
    	{
		      uni_stepper_go_to_zero_clkwise();
    	}
}
