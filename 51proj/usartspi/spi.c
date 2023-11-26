#include "spi.h"

void spis8bit(u8 cmd, u8 dat)
{
	sclk = 0;
	_nop_();
	cs = 0;
	
}



