/*
Lab 3 Problem 03
Abdullah MEMİŞOĞLU 171024001
 */

#include "stm32g0xx.h"

#define LEDDELAY10    16000000
#define LEDDELAY5     8000000

void EXTI4_15_IRQHandler (void){
	GPIOA->ODR &= ~(1U << 6); //LED PA6
	EXTI->RPR1 |= (1U<<7);    //BUTTON PB7
	delay (LEDDELAY5);
}

void EXTI2_3_IRQHandler (void){
	GPIOA->ODR &= ~(1U << 4); //LED PA4
	EXTI->RPR1 |= (1U<<2);    // BUTTON PB2
	delay (LEDDELAY5);
}


int main(void) {

    /* Enable GPIOA and GPIOB clock */
    RCC->IOPENR |= (3U << 0);

    /* Setup PB2 as input */
    GPIOB->MODER &= ~(3U << 2*2);

    /*PB2 interrupt */
    EXTI->RTSR1 |= (1U<<2);
    EXTI->EXTICR[0] |= (1U<<8*2);
    EXTI->IMR1 |= (1U<<2);
    NVIC_SetPriority(EXTI2_3_IRQn,0); //
    NVIC_EnableIRQ(EXTI2_3_IRQn);

    /* Setup PB7 as input */
    GPIOB->MODER &= ~(3U << 2*7);

    /*PB7 interrupt */
    EXTI->RTSR1 |= (1U<<7);
    EXTI->EXTICR[1] |= (1U<<8*3);
    EXTI->IMR1 |= (1U<<7);
    NVIC_SetPriority(EXTI4_15_IRQn,1);
    NVIC_EnableIRQ(EXTI4_15_IRQn);

    /* Setup PA6 as output */
    GPIOA->MODER &= ~(3U << 2*6);
    GPIOA->MODER |= (1U << 2*6);

    /* Setup PA4 as output */
    GPIOA->MODER &= ~(3U << 2*4);
    GPIOA->MODER |= (1U << 2*4);





    while(1) {

    	GPIOA->ODR |= (1U << 6);
    	GPIOA->ODR |= (1U << 4);
    	}


    return 0;

}

void delay(volatile uint32_t s){
	for(; s>0 ; s--);
}
