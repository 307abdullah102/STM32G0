/*
Lab 4 Problem 02
Abdullah MEMİŞOĞLU 171024001
 */

#include "stm32g0xx.h"
int global_b = 9;

void Delay_ms(uint32_t time);
void LedInit(void);
void LedSet(void);
void LedClear(void);
void LedToggle(void);

void SystemInital();

void ButtonInit(void);
int ButtonRead(void);
void InitTimer(int);

int main(void) {

	SystemInital();


	while(1){

		if(ButtonRead()){
			global_b --;
			delay(3149888);

			if(global_b == 0){
				global_b = 9;
			}
			switch(global_b){

						case 0:
							InitTimer(1000);
							break;
						case 1:
							InitTimer(2000);
							break;
						case 2:
							InitTimer(3000);
							break;
						case 3:
							InitTimer(4000);
							break;
						case 4:
							InitTimer(5000);
							break;
						case 5:
							InitTimer(6000);
							break;
						case 6:
							InitTimer(7000);
							break;
						case 7:
							InitTimer(8000);
							break;
						case 8:
							InitTimer(9000);
							break;
						case 9:
							InitTimer(9999);
							break;
						default:
							break;
		}

		}




		//LedSet();
		//Delay_ms(1000);
		//LedClear();
		//LedToggle();
		//Delay_ms(1000);
	}

    //SysTick_Config(1000);

    /* Arange PA1 as output */
    //GPIOA->MODER &= ~(3U << 2*1);
    //GPIOA->MODER |= (1U << 2*1);

    return 0;

}
void InitTimer(int x ){

	RCC->APBENR1 |= (1U<<1);


	TIM3->CR1 = 0;
	TIM3->CR1 |= (1<<7);
	TIM3->CNT = 0;

	TIM3->PSC = x;
	TIM3->ARR = 16000;

	TIM3->DIER |= (1<<0);
	TIM3->CR1 |= (1<<0);

	NVIC_SetPriority(TIM3_IRQn,0);
	NVIC_EnableIRQ(TIM3_IRQn);


}
void TIM3_IRQHandler (){
	LedToggle();
	TIM3->SR &= ~(1U << 0);


}
void SystemInital(){
	LedInit();
	ButtonInit();

}

void delay(volatile uint32_t s){
	for(; s>0 ; s--);
}


void LedInit(void){
	/* Activate GPIOA and GPIOB */
    RCC->IOPENR |= (3U << 0);

    /* Arange PA6 as output */
    GPIOA->MODER &= ~(3U << 2*6);
    GPIOA->MODER |= (1U << 2*6);

    /* Clear PA6 */
    GPIOA->BRR |= (1U << 6);

}
void LedSet(void){

	GPIOA->ODR |= (1U << 6);

}
void LedClear(void){
    /* Clear PA6 */
    GPIOA->BRR |= (1U << 6);
}
void LedToggle(void){

GPIOA->ODR ^= (1U << 6);
}

void ButtonInit(void){
	/* Activate GPIOA and GPIOB */
	 RCC->IOPENR |= (3U << 0);
    /* Arange PB7 as input */
    GPIOB->MODER &= ~(3U << 2*7);
}
int ButtonRead(void){
	int x = ((GPIOB->IDR >> 7) & 0x01);

	if(x) return 1;
	else return 0;


}

