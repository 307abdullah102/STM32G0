/*
 *	Lab 5 Problem 02
 *	Abdullah MEMİŞOĞLU 171024001
 */

#include "stm32g0xx.h"

void SystemInitial();
void InitTimer();
void LedInit();
void Delay(volatile uint32_t);

uint32_t i=0 ;
uint8_t flag_for_up_or_down=0;
volatile int button =0;
volatile int check_the_interrupt=0;
volatile uint32_t number=0;

int main(void) {
	SystemInitial();


    while(1) {
    }

    return 0;
}


void SystemInitial(){

    LedInit();
	InitTimer();
}
void LedInit(){
	 /* Enable GPIOB and GPIOA clock */
	    RCC->IOPENR |= (3U << 0);
	 /* Setup PA6 as alternate function */

		GPIOA->MODER &= ~(3U << 2*6);
		GPIOA->MODER |=  (2<< 2*6) ;

		GPIOA->AFR[0]  &= ~(0xFU<<4*6);
		GPIOA->AFR[0]  |=  (1<<4*6);

}


void InitTimer(){
		RCC->APBENR1 |=(1U<<1); // timer3 clock is enabled

		TIM3->CR1=0;
		TIM3->CR1 |=(1<<7); //Setting ARPE bit
		TIM3->CNT =0;
		TIM3->PSC=10;
		TIM3->ARR=(16000); // 1 sn
		TIM3->DIER |=(1<<0); // enable interrupts

		TIM3->CCMR1 |=(1<<3);

		TIM3->CCMR1 &= ~ (1u<<16); //0110  bits 16-6-5-4 for PWM mode 1
		TIM3->CCMR1 |=(1u<<6);
		TIM3->CCMR1 |= (1u<<5);
		TIM3->CCMR1 &= ~(1u<<4);

		TIM3->CCER |=(1<<0);


		TIM3->CCR1 =0x0;


		TIM3->EGR |= (1<<0);
		TIM3->CR1 |= (1<<0);

		NVIC_SetPriority(TIM3_IRQn,1); // Setting Priority for timer handler
		NVIC_EnableIRQ(TIM3_IRQn);

}
void TIM3_IRQHandler(){

	/*
	 * When the duty cycle goes from 0 to 16000, it is seen that the LED is lit step by step brighter.
 	 *If it reaches 16000, it will gradually decrease and turn off again.
	 */
	if(i==16000)
		flag_for_up_or_down=1;
	else if(i==0)
		flag_for_up_or_down=0;

	if (!flag_for_up_or_down)
		i=i+200;

	else if(flag_for_up_or_down)
		i=i-200;

	TIM3->CCR1 =i;

	TIM3->SR &=  ~(1U<<0);
	TIM3->SR &=  ~(1U<<1);
}

void Delay(volatile uint32_t s) {
    for(; s>0; s--);
}
