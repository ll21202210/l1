#include "stm32f4xx.h"
#include "stdio.h"
#include "oled.h"
#include "iic.h"
#include "menu.h"
#include "adc.h"

uint8_t gram[1024];
float advalue;
uint16_t conv;
uint8_t * strbuff[20];
void delay(uint32_t t)
{
	while(t--);
}


void sample(void)
{
	conv = ADC_GetConv();
	sprintf((char *)strbuff, "ch1 %4.3f v", conv / 4096.0 * 3.3);
//	OLED_ShowNum(gram, 321, 10, 0, 0);
	
	OLED_ShowStr(gram, (char *)strbuff, 0, 16);
	advalue = conv / 4096.0 * 3.3;
	sprintf((char *)strbuff, "tmp %4.2f C    ", (advalue - 0.76) / 0.0025 + 25);
	OLED_ShowStr(gram, (char *)strbuff, 0, 48);
	OLED_ShowNum(gram, conv, 5, 0, 32);
	
}


int main(void)
{
	
	delay(800000); // wait oled 
    OLED_Init();
	OLED_DMAConfig(gram);
	
//	ADC_Config();
	OLED_ShowStr(gram, "ADC", 0, 0);
	
	while(1)
    {
//		sample();
		__enable_irq();
		delay(2000000);
    }
}
