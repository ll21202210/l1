#include "led.h"
#include "stm32f4xx.h"

/*
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 时钟使能函数，参数1：AHB1，具体要看是什么外设
	// AHB1：【IO口A～K】【SRAM】...
	// APB1：【USART2、3】【UART4、5】【SPI2、3】【TIM2～7，12、13、14】
	// APB2：【USART1】【SPI1、4】【TIM1、8】
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	// PG12、PG15
	// Mode：输入、输出、复用、模拟
	// OType：推挽、开路
	// PuPd：不上拉和下拉、上拉、下拉
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOG, GPIO_Pin_12 | GPIO_Pin_15);
	//GPIO_ResetBits();
}
*/

void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10设置高，灯灭

}

