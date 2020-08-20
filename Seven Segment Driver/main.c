#include <avr/io.h>
#include "seven_seg/seven_seg.h"

int main(void)
{
	seg_init();
    while(1)
    {
       seg_disp_4digits_float(0.6258);
    }
}
