#include "bipolar_stepper/bipolar_stepper.h"

int main(void)
{
	bi_stepper_init(BI_HALF_STEP_MODE);
    while(1)
    {
		bi_stepper_goto_270_anticlk(BI_HALF_STEP_MODE);
		_delay_ms(1000);
		bi_stepper_goto_zero_clkwise(BI_HALF_STEP_MODE);
		_delay_ms(1000);
    }
}
