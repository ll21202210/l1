#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "spi.h"
#include "dma.h"
#include "key.h" 

#define WS2812_Low	0xc0
#define WS2812_High	0xf8


#define SEND_BUF_SIZE 48	// 2��LED �� 24λ����

u8 SendBuff[SEND_BUF_SIZE];	//�������ݻ�����

u8 count;
void change_LED()
{
	u16 i = 0;
	count++;
	switch(count)
	{
		case 1:
			SendBuff[0] = WS2812_High; // ������һLED����ɫ
			break;
		case 2:
			SendBuff[8] = WS2812_High; // ������һLED�ĺ�ɫ��G+R��
			break;
		case 3:
			SendBuff[16] = WS2812_High; // ������һLED����ɫ��G+R+B��
			break;
		case 4:
			SendBuff[24] = WS2812_High; // �����ڶ�LED����ɫ
			break;
		case 5:
			SendBuff[32] = WS2812_High; // �����ڶ�LED�ĺ�ɫ��G+R��
			break;
		case 6:
			SendBuff[40] = WS2812_High; // �����ڶ�LED����ɫ��G+R+B��
			break;
		case 7:
			count = 0;
			for(i = 0 ; i < SEND_BUF_SIZE ; i++)
				SendBuff[i] = WS2812_Low;
			break;
	}
}

int main(void)
{
	u8 key;	
	u16 i = 0;
	count = 0;
	
	for(i = 0 ; i < SEND_BUF_SIZE ; i++)
		SendBuff[i] = WS2812_Low;
	i = 0;
	
	delay_init(180); 
	LED_Init();
	KEY_Init();
	uart_init(115200);
	//SPI1_Init();
	SPI3_Init();
	//SPI3_SetSpeed(SPI_BaudRatePrescaler_4);		//����Ϊ21Mʱ��,����ģʽ 
	
	//DMA1,STEAM5,CH0,����ΪSPI3,�洢��ΪSendBuff,����Ϊ:SEND_BUF_SIZE.
	MYDMA_Config(DMA1_Stream5,DMA_Channel_0,(u32)&SPI3->DR,(u32)SendBuff,SEND_BUF_SIZE);
	
	SPI_I2S_DMACmd(SPI3, SPI_I2S_DMAReq_Tx, ENABLE);	// ʹ��SPI3��DMA���� 	
	MYDMA_Enable(DMA1_Stream5,SEND_BUF_SIZE);     		// ��ʼһ��DMA���䣡
	
  while(1){
    //printf("t:%d\r\n",t);
		//GPIO_SetBits(GPIOG, GPIO_Pin_12 | GPIO_Pin_15);
		//GPIO_ResetBits(GPIOG, GPIO_Pin_12 | GPIO_Pin_15);
		
		key=KEY_Scan(0);
		if(key==KEY0_PRES)//KEY0���£�KEY0_PRES��KEY1_PRES��KEY2_PRES��WKUP_PRES��
		{
			LED1 = !LED1;
			change_LED();
		}
		
		delay_ms(10);
		i++;
		if(i == 100)
		{
			LED0 = !LED0;
			i = 0;
		}
			
		if(DMA_GetFlagStatus(DMA1_Stream5,DMA_FLAG_TCIF5)!=RESET)//�ȴ�DMA1_Steam5�������
		{
			//���DMA1_Steam5������ɱ�־����Ԥ��DMA_FLAG_TCIF0���㣬�������Channel
			DMA_ClearFlag(DMA1_Stream5,DMA_FLAG_TCIF5);
			
			SPI_I2S_DMACmd(SPI3, SPI_I2S_DMAReq_Tx, ENABLE);	// ʹ��SPI3��DMA���� 	
			MYDMA_Enable(DMA1_Stream5,SEND_BUF_SIZE);     		// ��ʼһ��DMA���䣡
		}
	}
}







