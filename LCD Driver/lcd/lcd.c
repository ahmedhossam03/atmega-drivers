#include "lcd.h"

#define	LCD_4BIT_INIT 0x02
void lcd_init()
{
	//define ctrl bits as output
	LCD_CTRL_DIRC |= (1 << LCD_RS);
	LCD_CTRL_DIRC |= (1 << LCD_RW);
	LCD_CTRL_DIRC |= (1 << LCD_EN);

	//define data bits / port as output
	#if (LCD_FUNC == 0x28)		//4 bit mode only last 4 bits are defined as output
		LCD_DATA_DIRC |= (1 << 4);
		LCD_DATA_DIRC |= (1 << 5);
		LCD_DATA_DIRC |= (1 << 6);
		LCD_DATA_DIRC |= (1 << 7);
	#else						//8 bit mode all port is defined as output
		LCD_DATA_DIRC = 0xFF;
	#endif
	
	//wait for power up
	_delay_ms(30);
	
	//define function mode
	#if (LCD_FUNC == 0x28)			//4 bit mode, divide command into two
		lcd_send_cmd(LCD_4BIT_INIT);
		lcd_send_cmd(LCD_FUNC);
		_delay_ms(1);
	#else							//8 bit mode, send command once
		lcd_send_cmd(LCD_FUNC);
		_delay_ms(1);
	#endif
	
	//initialize display mode
	lcd_send_cmd(LCD_DISP);
	_delay_ms(1);
	
	//clear display
	lcd_send_cmd(LCD_CLR);
	_delay_ms(2);
	
	//initialize entry mode
	lcd_send_cmd(LCD_ENTRY);
}

void lcd_send_cmd(unsigned char cmd)
{
	#if (LCD_FUNC == 0x28)	//4 bit mode selected
		//send high nibble of cmd
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (cmd & 0xF0);	//only high nibble is altered rest is the same
		LCD_CTRL_PORT &= ~(1 << LCD_RS);
		LCD_CTRL_PORT |= (1 << LCD_EN);
		_delay_ms(1);
		LCD_CTRL_PORT &= ~(1 << LCD_EN);
		//send low nibble of cmd
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((cmd << 4) & 0xF0);	//only high nibble is altered rest is the same
		LCD_CTRL_PORT &= ~(1 << LCD_RS);
		LCD_CTRL_PORT |= (1 << LCD_EN);
		_delay_ms(1);
		LCD_CTRL_PORT &= ~(1 << LCD_EN);
	#else					//8 bit mode selected
		LCD_DATA_PORT = cmd;
		LCD_CTRL_PORT &= ~(1 << LCD_RS);
		LCD_CTRL_PORT |= (1 << LCD_EN);
		_delay_ms(1);
		LCD_CTRL_PORT &= ~(1 << LCD_EN);
	#endif
}

void lcd_send_char(unsigned char data)
{
	#if (LCD_FUNC == 0x28)		//4 bit mode selected
		//send high nibble of data
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);	//only high nibble is altered rest is the same
		LCD_CTRL_PORT |= (1 << LCD_RS);
		LCD_CTRL_PORT |= (1 << LCD_EN);
		_delay_ms(1);
		LCD_CTRL_PORT &= ~(1 << LCD_EN);
		//send low nibble of data
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data << 4) & 0xF0); //only high nibble is altered rest is the same
		LCD_CTRL_PORT |= (1 << LCD_RS);
		LCD_CTRL_PORT |= (1 << LCD_EN);
		_delay_ms(1);
		LCD_CTRL_PORT &= ~(1 << LCD_EN);
	#else						//8 bit mode selected
		LCD_DATA_PORT = data;
		LCD_CTRL_PORT |= (1 << LCD_RS);
		LCD_CTRL_PORT |= (1 << LCD_EN);
		_delay_ms(1);
		LCD_CTRL_PORT &= ~(1 << LCD_EN);
	#endif
}

void lcd_send_str(unsigned char str[], unsigned char str_size)
{
	unsigned char loopCounter = 0;
	//send each byte of the string 
	for(loopCounter = 0; loopCounter < str_size; loopCounter++)
	{
		lcd_send_char(str[loopCounter]);
	}
}

void lcd_send_itoa(unsigned short int_num)
{
	//2 byte integer number has 5 digits max
	unsigned char int_to_char[5] = {'0', '0', '0', '0', '0'};
	//counting from 4 to 0
	unsigned char loopCounter = 4;
	
	while(int_num)
	{
		//get the last digit from the integer and put it in the last element of the array
		int_to_char[loopCounter] = (int_num % 10) + '0';
		//divide by 10 to remove the digit already put in the array
		int_num = int_num / 10;
		//move to the element before
		loopCounter--;
	}
	//send the array of integer digits converted in char
	lcd_send_str(int_to_char, 5);
}

void lcd_goto_xy(unsigned char x, unsigned char y)
{
	//y represents each line 0-1, x represents each place on a line 0-15
	if (y == 0)
	{
		lcd_send_cmd( (0x80) + x ); //0x80 is the command of place zero on line 0
	}
	else if (y == 1)
	{
		lcd_send_cmd( (0xC0) + x );	//0xC0 is the command of place zero on line 1
	}
}
