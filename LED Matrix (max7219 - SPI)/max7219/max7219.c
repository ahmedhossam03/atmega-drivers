#include "max7219.h"

void max7219_init()
{
	//initialize spi
	spi_init(SPI_MODE_MASTER,
	SPI_INT_DIS,
	SPI_DORD_MSB_FIRST,
	SPI_CLK_4);
	//delay after initializing spi
	_delay_ms(10);
	//normal operation
	max7219_send_cmd(MAX7219_REG_SHUTDOWN, 0x01);
	//no decode
	max7219_send_cmd(MAX7219_REG_DECODE_MODE, 0x00);
	//maximum intensity
	max7219_send_cmd(MAX7219_REG_INTENSITY, 0x0F);
	//scan all digit registers
	max7219_send_cmd(MAX7219_REG_SCAN_LIMIT, 0x07);
	//normal operation
	max7219_send_cmd(MAX7219_REG_DISPLAY_TEST, 0x00);
}

void max7219_send_cmd(unsigned char reg, unsigned char data)
{
	//lower ss for spi to begin
	SPI_BEGIN_TRANSMITION;
	//send register you want to edit
	spi_mstr_tranceive(reg);
	//send data in the selected register above
	spi_mstr_tranceive(data);
	//raise ss to end spi
	SPI_END_TRANSMITION;
	//delay after each transmission
	_delay_ms(10);
}

static unsigned char disp_array[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
void max7219_scroll_chars(unsigned char char_arr[], unsigned char char_arr_size)
{
	for(unsigned char i = 0; i < 8; i++)
	{
		//put in first element
		if(i < char_arr_size)
		{
			disp_array[0] = char_arr[i];
		}
		//display on led matrix
		for(unsigned char j = 0; j < 8; j++)
		{
			//remove last display cols
			max7219_send_cmd(j + 1, 0x00);
			_delay_ms(1);
			//display new column
			max7219_send_cmd(j + 1, disp_array[j]);
		}
		//shift entire array by one
		for(unsigned char j = 7; j > 0; j--)
		{
			disp_array[j] = disp_array[j - 1];
		}
		//replace shift element by zero
		disp_array[0] = 0x00;
	}
}
