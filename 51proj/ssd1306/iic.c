#include "iic.h"

void iicstart(void)
{
	sda = 1;
	scl = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	sda = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
}
void iicstop(void)
{
	
	sda = 0;
	scl = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	sda = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
}
void iics8bit(u8 da)
{
	u8 i;
	scl = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	for(i = 0; i<8; i++)
	{
		sda = da>>7;
		da = da<<1;
		_nop_();_nop_();_nop_();_nop_();_nop_();//5us
		scl = 1;
		_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
		scl = 0;
		_nop_();_nop_();_nop_(); //5us
	}
}
void iicwait(void)
{
	u8 i = 250;
	sda = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	scl = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	while(sda && i--)
	{
		_nop_();_nop_(); 
	} //1ms
	sda = 0;
	_nop_();_nop_();_nop_();_nop_();
}

void ssdscmd(u8 cmd)
{
	iicstart();
	iics8bit(0x78);
	iicwait();
	iics8bit(0x00);
	iicwait();
	iics8bit(cmd);
	iicwait();
	iicstop();
}
void ssdsdat(u8 dat)
{
	iicstart();
	iics8bit(0x78);
	iicwait();
	iics8bit(0x40);
	iicwait();
	iics8bit(dat);
	iicwait();
	iicstop();
}
void ssd1306init(void)
{
//		ssdscmd(0x8D);
//		ssdscmd(0x14);
//		ssdscmd(0xAF);
//		ssdscmd(0xA5);
	ssdscmd(0xAE);   //display off
	ssdscmd(0x20);	//Set Memory Addressing Mode	
	ssdscmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	ssdscmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	ssdscmd(0xc8);	//Set COM Output Scan Direction
	ssdscmd(0x00);//---set low column address
	ssdscmd(0x10);//---set high column address
	ssdscmd(0x40);//--set start line address
	ssdscmd(0x81);//--set contrast control register
	ssdscmd(0x7f);
	ssdscmd(0xa1);//--set segment re-map 0 to 127
	ssdscmd(0xa6);//--set normal display
	ssdscmd(0xa8);//--set multiplex ratio(1 to 64)
	ssdscmd(0x3F);//
	ssdscmd(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	ssdscmd(0xd3);//-set display offset
	ssdscmd(0x00);//-not offset
	ssdscmd(0xd5);//--set display clock divide ratio/oscillator frequency
	ssdscmd(0xf0);//--set divide ratio
	ssdscmd(0xd9);//--set pre-charge period
	ssdscmd(0x22); //
	ssdscmd(0xda);//--set com pins hardware configuration
	ssdscmd(0x12);
	ssdscmd(0xdb);//--set vcomh
	ssdscmd(0x20);//0x20,0.77xVcc
	ssdscmd(0x8d);//--set DC-DC enable
	ssdscmd(0x14);//
	ssdscmd(0xaf);//--turn on oled panel 
}

