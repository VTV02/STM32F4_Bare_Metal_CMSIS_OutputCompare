/*
 * tim.c
 *
 *  Created on: May 31, 2024
 *      Author: VOVAN
 */
#include<tim.h>
#include<stm32f411xe.h>

#define TIM2EN     (1U<<0)
#define CR1_CEN    (1U<<0)
#define OC_TOGGLE  (1U<<5)|(1U<<4)
#define CCER_CC1E  (1U<<0)
#define GPIOAEN	   (1U<<0)

void tim2_1hz_init(void)
{
	/*Enable clock access to tim2*/
	RCC->APB1ENR|= TIM2EN;
	/*Set prescaler value */
	TIM2->PSC= 1600-1;/*16 000 000/ 1 600=10 000*/
	/*Set auto-reload value*/
	TIM2->ARR= 10000-1;/*16 bit 0->65535, 10 000/10 000 = 1*/
	/*Clear counter*/
	TIM2->CNT=0;
	/*Enable timer*/
	TIM2->CR1|=CR1_CEN;
}

void tim2_pa5output_compare(void)
{
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR|=GPIOAEN;
	/*Configure PA5 as alternate function*/
	GPIOA->MODER|=(1U<<11);
	GPIOA->MODER&=~(1U<<10);
	/*Configure PA5 as alternate function type TIM2_CH1 AF01 */
	GPIOA->AFR[0]|=(1U<<20);
	GPIOA->AFR[0]&=~(1U<<21);
	GPIOA->AFR[0]&=~(1U<<22);
	GPIOA->AFR[0]&=~(1U<<23);
	/*Enable clock access to tim2*/
	RCC->APB1ENR|= TIM2EN;
	/*Set prescaler value */
	TIM2->PSC= 1600-1;/*16 000 000/ 1 600=10 000*/
	/*Set auto-reload value*/
	TIM2->ARR= 10000-1;/*16 bit 0->65535, 10 000/10 000 = 1*/

	/*Set output compare toggle mode*/
	TIM2->CCMR1|=OC_TOGGLE;
	TIM2->CCMR1&=~(1U<<6);/*Auto=0 if not configure*/
	/*Enable tim2 ch1 in compare mode*/
	TIM2->CCER|=CCER_CC1E;

	/*Clear counter*/
	TIM2->CNT=0;
	/*Enable timer*/
	TIM2->CR1|=CR1_CEN;
}

