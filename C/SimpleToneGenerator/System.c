/*
 * Lab 6 Problem 1
 * Abdullah MEMİŞOĞLU 171024001
 * System.c
 */

#include "System.h"

#include "stm32g0xx.h"
#include "SSD.h"
#include "Keypad.h"
#include "math.h"

/*
 * System Functions and Variables in here.
 */

int first_digit;
int second_digit;
int third_digit;
uint32_t check;
void TIM3_IRQHandler(){


	TIM3->SR &=  ~(1U<<0);
	TIM3->SR &=  ~(1U<<1);
}
void TIM2_IRQHandler(){

	TIM3->ARR=check;
	TIM3->EGR |= (1U<<0);
	FindNumberPlaces(check);

	TIM2->SR &=  ~(1U<<0);
	TIM2->SR &=  ~(1U<<1);
}

/*
 * Initialization for all system.
 */
void SystemInitial(){

	SystemCoreClockUpdate();
	SSDInit();
    KeypadInitForOutput();
    KeypadInitForInput();
	InitTimer();
	InitTimer2();
	SpeakerInit();

}

void InitTimer(){

		RCC->APBENR1 |=(1U<<1);
		TIM3->CR1=0;
		TIM3->CR1 |=(1<<7);
		TIM3->CNT =0;
		TIM3->PSC=0;
		TIM3->ARR=(16000);
		TIM3->DIER |=(1<<0);
		TIM3->CCMR1 |=(1<<3);

		TIM3->CCMR1 &= ~ (1u<<16); //0
		TIM3->CCMR1 |=(1u<<6); //1
		TIM3->CCMR1 |= (1u<<5); //1
		TIM3->CCMR1 &= ~(1u<<4);  // 0

		TIM3->CCER |=(1<<0);// (capture compare 1) enable


		TIM3->CCR1 =255;

		//TIM3->AF1 |=(1<<14); //TİM3 af1 register ertsel comp1 output(?)
		TIM3->EGR |= (1<<0); // update genration
		TIM3->CR1 |= (1<<0);

		NVIC_SetPriority(TIM3_IRQn,2);
		NVIC_EnableIRQ(TIM3_IRQn);

}
void InitTimer2(){
		RCC->APBENR1 |=(1U<<0);
		TIM2->CR1=0;
		TIM2->CNT =0;
		TIM2->PSC=0;
		TIM2->ARR=(8000);
		TIM2->DIER |=(1<<0);
		TIM2->CR1 |= (1<<0);

		NVIC_SetPriority(TIM2_IRQn,1);
		NVIC_EnableIRQ(TIM2_IRQn);

}
void SpeakerInit(void){
	 /* Enable GPIOB and GPIOA clock */
	    RCC->IOPENR |= (3U << 0);
	 /* Setup PA6 as alternate function */

		GPIOA->MODER &= ~(3U << 2*6);  //PA6 RESET
		GPIOA->MODER |=  (2U<< 2*6) ;  //PA6 SET as alternate function

		GPIOA->AFR[0]  &= ~(0xFU<<4*6);  //reset the AF1
		GPIOA->AFR[0]  |=  (1<<4*6);// AF1 ---- PA6
}



void delay(volatile uint32_t s) {
    for(; s>0; s--);
}

