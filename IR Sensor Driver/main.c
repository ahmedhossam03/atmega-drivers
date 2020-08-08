#include "ir_sensor/ir.h"
#include "util/delay.h"
#include "avr/io.h"
#include "avr/interrupt.h"

int main(void)
{
  //initialize IR with mode
	ir_init(IR_MODE_PIN);
	//state to take value in
	ir_state state = ir_no_change;
	//for testing driver
	DDRG = 0xFF;
	//enable global interrupt
	sei();
  while(1)
  {
    //get new state
    state = ir_get_state(IR_MODE_PIN);
    //action to be done
    if(state == ir_obstacle)
    {
      PORTG |= (1 << 0);
    }
    else if(state == ir_no_obstacle)
    {
      PORTG &= ~(1 << 0);
    }
  }
}
