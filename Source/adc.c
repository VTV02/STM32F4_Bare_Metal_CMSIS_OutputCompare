#include "adc.h"
#include<stm32f411xe.h>


#define ADC1EN		  (1U<<8)
#define GPIOAEN       (1U<<0)
#define ADC_CH1       (1U<<0)
#define ADC_SEQ_LEN_1 0x00;
#define CR2_ADON      (1U<<0)
#define CR2_SWSTART   (1U<<30)
#define SR_EOC        (1U<<1)
#define CR2_CONT      (1U<<1)

void pa1_adc_init(void)
{
   /************************Configure ADC GPIO pin*******************/
   /*Enable clock access to GPIOA*/
	RCC->AHB1ENR|=GPIOAEN;
  /*Set the mode of PA1 to analog*/
	GPIOA->MODER|=(1U<<2);
	GPIOA->MODER|=(1U<<3);

 /************************Configure ADC module*******************/
	/*Enable clock access to ADC*/
	RCC->APB2ENR|=ADC1EN;
	/*Conversion sequence start*/
	ADC1->SQR3|=ADC_CH1;
	/*Conversion sequence length*/
	ADC1->SQR1&=ADC_SEQ_LEN_1;
	/*Enable ADC module*/
	ADC1->CR2|=CR2_ADON;
}

void star_conversion(void)
{
	while(!(ADC1->CR2&CR2_ADON));
	/*Enable continuous conversion*/
	ADC1->CR2|=CR2_CONT;
	/*Start adc conversion*/
	ADC1->CR2|=ADC_CR2_SWSTART;
}

uint32_t adc_read(void)
{
	while(!(ADC1->SR&SR_EOC));
	return ADC1->DR;
}

