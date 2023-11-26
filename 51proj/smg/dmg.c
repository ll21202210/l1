#include <intrins.h>
#include <reg52.h>
#define u8 unsigned char
#define u16 unsigned int
#define lsac ((lsabc *)0x90)

typedef struct 
{
	u8 vsl:3;
}lsabc;

void main()
{
	u8 i,j;
	P0 = 0x3f;
	while(1)
	{
		for(i = 0,j = 1; i< 8; i++,j++,P1 &= ~0x07)
		{
			P1 |= j;
			P0 = i;
			_nop_();_nop_();_nop_();_nop_();_nop_();
		}
	}
}