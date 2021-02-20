/*
 * Lab7 Problem 2
 * Abdullah MEMİŞOĞLU 171024001
 * Problem2.c
 */
#include <stdio.h>
#include "Problem2.h"
#include "stm32g0xx.h"
#include "SSD.h"

int counter = 0;
uint16_t mic_DR; // Potantiometer data from ADC

/*
 *TIM3 and TIM14 interrupts are selected from Table 14 in ARM CORTEX
 *TIM3  datasheet in accordance with the global interrupt free pins.
 */
void System_Init(){// all initialize are this function

    ADCInit();					// ADC Initializing
    InitTimer2();			// TIM14 Initializing
    UartInit(9600);
    SSDInit();
    ButtonInit();
}
void ButtonInit(void){
	/* Activate GPIOA and GPIOB */
	 RCC->IOPENR |= (3U << 0);
    /* Arange PA6 as input */
    GPIOA->MODER &= ~(3U << 2*6);
}
int ButtonRead(void){
	int x = ((GPIOA->IDR >> 6) & 0x01);

	if(x) return 1;
	else return 0;


}
void ADCInit(){
	RCC->IOPENR |= (1U << 0);			//GPIOA activate
	GPIOA->MODER &= ~(3U << 2 * 7);		// PA7 as output
	GPIOA->MODER |= (3U << 2 * 7);

	RCC->APBENR2 |=(1<<20); //clock enable
	ADC1->CR |=(1<<28); //voltage regulator enable
	Delay(500);

	ADC1->CR |=(1U<<31); //calibration
	while(((ADC1->CR>>31)==1)); // until calibration

	ADC1->CFGR1 |= (1U << 4);
	ADC1->CHSELR |= (1U << 7);		//chanel selection for PA7
	ADC1->CFGR1 |= (1U << 13);    // contionous conversion


	ADC1->CR |= (1U << 0);	//enable adc
	while (ADC1->ISR & (1 << 0));  //adc ready flag

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

void InitTimer2(){
		RCC->APBENR2 |=(1U<<15);
		TIM14->CR1=0;
		TIM14->CR1 |=(1<<7);
		TIM14->CNT =0;
		TIM14->PSC=0;
		TIM14->ARR=(16000);
		TIM14->DIER |=(1<<0);
		TIM14->CR1 |= (1<<0);

		NVIC_SetPriority(TIM14_IRQn ,1);
		NVIC_EnableIRQ(TIM14_IRQn);

}

void TIM14_IRQHandler   (){
	mic_DR = ADC_DR();

	if(ButtonRead()){
		counter = 0;
		Delay(320000);
	}
	if(mic_DR > 128){
		++counter;
		Delay(320000);
	}
	FindNumberPlaces(counter);
	TIM14->SR &=  ~(1U<<0); // update sr registers
	TIM14->SR &=  ~(1U<<1);
	//PrintMyNumber();

}


uint16_t ADC_DR(){
	ADC1->CR |=(1<<2);

	    	if((ADC1->ISR>>2)&1){
	    			return ADC1->DR;
	    	}
}


int _write(int fd,char *ptr,int len){
	(void)fd;
	for(int i=0;i<len;++i){
		printchar(ptr[i]);
	}
	return len;
}
void print(char *buf){
	int len=0;
	while(buf[len++]!= '\0');
	_write(0,buf,len);
}
void printchar(uint8_t c){
	USART2->TDR =(uint16_t)c;
	while(!(USART2->ISR&(1<<6)));
}
void UartInit(uint32_t baud){
	/* GPIOA Set*/
	RCC->IOPENR |=(1<<0);
	RCC->APBENR1 |= (1<<17);

	GPIOA->MODER &= ~(3U << 2*2);
	GPIOA->MODER |=  (2<< 2*2) ;

	GPIOA->MODER &= ~(3U << 2*3);
	GPIOA->MODER |=  (2<< 2*3);

	GPIOA->AFR[0]  &= ~(0xFU<<4*2);
	GPIOA->AFR[0]  |=  (1<<4*2);

	GPIOA->AFR[0]  &= ~(0xFU<<4*3);
	GPIOA->AFR[0]  |=  (1<<4*3);

	USART2->CR1 =0;
	USART2->CR1 |= (1<<3);
	USART2->CR1 |=(1<<2);



	USART2->BRR = (uint16_t)(SystemCoreClock/baud);
	USART2->CR1 |=(1<<0);//USART enable

	//NVIC_SetPriority(USART2_IRQn,1);
	//NVIC_EnableIRQ(USART2_IRQn);
}


void Delay(volatile uint32_t s) {
    for(; s>0; s--);
}

