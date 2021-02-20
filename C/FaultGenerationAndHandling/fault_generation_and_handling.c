/*
Lab 3 Problem 01
Abdullah MEMİŞOĞLU 171024001
 */

#include "stm32g0xx.h"
#include <stdio.h>

volatile uint32_t LEDDELAY;
int a = 0;
int x;

void HardFault_Handler (void){
	delay(LEDDELAY);
	NVIC_SystemReset(); // System Reset
	Reset_Handler();

}

int main(void) {

    /* Activate GPIOA and GPIOB */
    RCC->IOPENR |= (3U << 0);

    /* Arange PB7 as input */
    GPIOB->MODER &= ~(3U << 2*7);

    /* Arange PA6 as output */
    GPIOA->MODER &= ~(3U << 2*6);
    GPIOA->MODER |= (1U << 2*6);

    /* Arange PA1 as output */
    GPIOA->MODER &= ~(3U << 2*1);
    GPIOA->MODER |= (1U << 2*1);


    while(1) {
    	++a; //Random number generator.

    	GPIOA->ODR &= ~(1U << 6); //Turn off the LED in PA6.
    	GPIOA->ODR &= ~(1U << 1); //Turn off the LED in PA1.



    	if(a%2 == 0){
    		if((GPIOB->IDR >> 7) & 1){

    		GPIOA->ODR |= (1U << 6);//Light up the LED in PA6.
    		LEDDELAY = 16000000;
    		__asm("ldr r4, =0x81000000");
    		__asm("ldr r2,[r4]");



    		}

    	}

    	else {
    		if((GPIOB->IDR>>7) & 1){

    	    GPIOA->ODR |= (1U << 1);//Light up the LED in PA1.
    		LEDDELAY = 16000000;
    		x = *(int*)0xFFFFFF;




    		}
    	}

    }
    return 0;

}

void delay(volatile uint32_t s){
	for(; s>0 ; s--);
}


