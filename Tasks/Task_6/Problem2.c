/*
Lab 3 Problem 02
Abdullah MEMİŞOĞLU 171024001
 */

#include "stm32g0xx.h"

#define LEDDELAY    1600000

void EXTI4_15_IRQHandler (void){
	GPIOA->ODR &= ~(1U << 6);
	EXTI->RPR1 |= (1U<<7);
	delay (LEDDELAY);
}

int main(void) {

    /* Enable GPIOA and GPIOB clock */
    RCC->IOPENR |= (3U << 0);

    /* Setup PB7 as input */
    GPIOB->MODER &= ~(3U << 2*7);

    /* Setup PA6 as output */
    GPIOA->MODER &= ~(3U << 2*6);
    GPIOA->MODER |= (1U << 2*6);

    EXTI->RTSR1 |= (1U<<7);
    EXTI->EXTICR[1] |= (1U<<8*3);
    EXTI->IMR1 |= (1U<<7);
    NVIC_SetPriority(EXTI4_15_IRQn,0);
    NVIC_EnableIRQ(EXTI4_15_IRQn);

    while(1) {

    	GPIOA->ODR |= (1U << 6);
    	}


    return 0;

}

void delay(volatile uint32_t s){
	for(; s>0 ; s--);
}
