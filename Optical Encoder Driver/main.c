#include <avr/io.h>
#include "encoder/encoder.h"


//PORT FOR PINS OF ENCODER 
#define ENC_PIN_INPUT		PIND
#define ENC_PIN_INPUT_DIR	DDRD	
//encoder resolution
#define ENC_RES			10		//from encoder data sheet

int main(void)
{
	//for the action to be taken
	DDRA |= (1 << 0);
	//init encoder with pins and the operating mode
	encoder_init(0, 1, ENC_MODE_PIN);
	//enable global interrupt
	SREG |= (1 << 7);
	//variable to get the motor angle in
	unsigned short int angle = 0;
  while(1)
  {
    //get motor angle
          angle = encoder_get_angle(ENC_MODE_PIN);
    //actions to be done at certain angles
    if(angle == 90)
      PORTA |= (1 << 0);
    else if(angle == 180)
      PORTA |= (1 << 0);
    else
      PORTA &= ~(1 << 0);
 }
}
