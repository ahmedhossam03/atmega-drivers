#include <avr/io.h>
#include "lcd/lcd.h"

int main(void)
{
	//init lcd
	lcd_init();
	//init int number
	unsigned short x = 12058;
    while(1)
    {
      //go to line 1 place 5
      lcd_goto_xy(5, 1);
      //print integer
      lcd_send_itoa(x);
      _delay_ms(1000);
      //clear screen
      lcd_send_cmd(LCD_CLR);
      _delay_ms(2);
    }
}
