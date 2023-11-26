#include "adc.h"

void ADC_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIOInitStructure;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIOInitStructure.GPIO_OType = GPIO_OType_PP;
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIOInitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIOInitStructure);
	
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF);
	
	ADC_CommonInitTypeDef ADCCommonInitStructure;
	ADCCommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADCCommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADCCommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
	ADCCommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	
	ADC_CommonInit(&ADCCommonInitStructure);
	
	ADC_InitTypeDef ADCInitStructure;
	ADCInitStructure.ADC_ContinuousConvMode = ENABLE;
	ADCInitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADCInitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADCInitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADCInitStructure.ADC_NbrOfConversion = 1;
	ADCInitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADCInitStructure.ADC_ScanConvMode = DISABLE;
	
	ADC_Init(ADC1, &ADCInitStructure);
	
	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_18, 1, ADC_SampleTime_480Cycles);
	
	
	
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_SoftwareStartConv(ADC1);
}
uint16_t ADC_GetConv(void)
{
	return ADC_GetConversionValue(ADC1);
}


