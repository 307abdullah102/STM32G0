/*
 * Lab7 Problem 1
 * Abdullah MEMİŞOĞLU 171024001
 * Problem1.c
 */
#include <stdio.h>
#include "Problem1.h"

#include "stm32g0xx.h"

uint16_t pot_DR; // Potantiometer data from ADC
float led1_CCR ; // Brightness value for LED1
float led2_CCR; // Brightness value for LED2


/*
 *TIM3 and TIM14 interrupts are selected from Table 14 in ARM CORTEX
 *TIM3  datasheet in accordance with the global interrupt free pins.
 */
void System_Init(){// all initialize are this function

    LEDInit();   // Potantiometer Initializing
    ADCInit();					// ADC Initializing
    InitTimer();				//TIM3 and TIM14 Initializing
    InitTimer2();
}
void ADCInit(){
	RCC->IOPENR |= (1U << 0);			//GPIOA activate
	GPIOA->MODER &= ~(3U << 2 * 0);		// PA0 as output
	GPIOA->MODER |= (3U << 2 * 0);

	RCC->APBENR2 |=(1<<20); //clock enable
	ADC1->CR |=(1<<28); //voltage regulator enable
	Delay(500);
	ADC1->CR |=(1<<31); //calibration
	while(((ADC1->CR>>31)==1)); // until calibration
	//ADC1->CFGR1 |= (1U << 4);

	//ADC1->ISR &= ~(1 << 0);
	ADC1->CR |= (1U << 0);	//enable adc
	while (ADC1->ISR & (1 << 0));  //adc ready flag

	ADC1->CHSELR |= (1U << 0);		//chanel selection for PA0
	ADC1->CFGR1 |= (1U << 13);    // contionous conversion
	ADC1->CR |= (1U << 2);     // ADC Start Conversion

}

void LEDInit(){
	 /* Enable GPIOB and GPIOA clock */
	    RCC->IOPENR |= (3U << 0);


		GPIOB->MODER &= ~(3U << 2*4);  //PB4 RESET
	    GPIOB->MODER |=  (2<< 2*4) ;  //PB4 SET AS alternate function 10


		GPIOB->AFR[0]  &= ~(0xFU<<4*4);  //af1... reset
		GPIOB->AFR[0]  |=  (1<<4*4);//PB4 af1

		 ///////////*  PA4 set as alternate function */
		GPIOB->MODER &= ~(3U << 2*5);  //PB5 RESET
		GPIOB->MODER |=  (2<< 2*5) ;  //PB5 SET AS alternate function 10


		GPIOB->AFR[0]  &= ~(0xFU<<4*5);  //af5... reset
		GPIOB->AFR[0]  |=  (1<<4*5);//PB5 af5
}
void InitTimer(){

		RCC->APBENR1 |=(1U<<1);
		TIM3->CR1=0;
		TIM3->CR1 |=(1<<7);
		TIM3->CNT =0;
		TIM3->PSC=0;
		TIM3->ARR=(16000);
		TIM3->DIER |=(1U<<0);
		TIM3->CCMR1 |=(1U<<3);

		TIM3->CCMR1 &= ~ (1U<<16); //0 for PWM MODE
		TIM3->CCMR1 |=(1U<<6); //1
		TIM3->CCMR1 |= (1U<<5); //1
		TIM3->CCMR1 &= ~(1U<<4);  // 0

		TIM3->CCER |=(1<<0);// (capture compare 1) enable


		TIM3->CCR1 =1600;		// DEFAULT CCR


		// CH2 PWM SETUP

		TIM3->CCMR1 |= (0X3U << 13);  	// OC2M 110: PWM mode 14:12
		TIM3->CCMR1 |= (1U << 11); 		//  OUTPUT COMPARE 2 PRELOAD ENABLE


		TIM3->CCER |= (1U << 4);		// capture/compare 2 output polarity
		TIM3->CCR2 = 1600;


		TIM3->EGR |= (1<<0); // update generation
		TIM3->CR1 |= (1<<0);

		NVIC_SetPriority(TIM3_IRQn,2);
		NVIC_EnableIRQ(TIM3_IRQn);

}
void InitTimer2(){
		RCC->APBENR2 |=(1U<<15);
		TIM14->CR1=0;
		TIM14->CR1 |=(1<<7);
		TIM14->CNT =0;
		TIM14->PSC=0;
		TIM14->ARR=(8000);
		TIM14->DIER |=(1<<0);
		TIM14->CR1 |= (1<<0);

		NVIC_SetPriority(TIM14_IRQn ,1);
		NVIC_EnableIRQ(TIM14_IRQn);

}

void TIM14_IRQHandler   (){
	pot_DR = ADC_DR();
	led1_CCR =(16000/4095)*pot_DR;
	led2_CCR=12285-led1_CCR; //MAX DR VALUE 4095 MAX(LED1+LED2) = 12285

	TIM3->CCR1 =led1_CCR;
	TIM3->CCR2 =led2_CCR;

	TIM14->SR &=  ~(1U<<0); // update sr registers
	TIM14->SR &=  ~(1U<<1);
}

void TIM3_IRQHandler(){
	TIM3->SR &=  ~(1U<<1);
	TIM3->SR &= ~(1U << 0);
}

uint16_t ADC_DR(){
	ADC1->CR |=(1<<2);

	    	if((ADC1->ISR>>2)&1){
	    			return ADC1->DR;
	    	}
}


void Delay(volatile uint32_t s) {
    for(; s>0; s--);
}

