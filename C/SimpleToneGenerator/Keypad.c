/*
 * Lab6 Problem1
 * Abdullah MEMİŞOĞLU 171024001
 * keypad.c
 */
#include "stm32g0xx.h"
#include "Keypad.h"
#include "SSD.h"
#include "System.h"

uint32_t check ;

void EXTI0_1_IRQHandler (){ //c1

	ResetKeypad();
	if((EXTI->RPR1>>0)&1){ //To find out if the interrupt is from Px0 or Px1.
		GPIOA->ODR |=(1<<11); // 	A
		if((GPIOB->IDR>>0)&1){

			check = 3000;

				}

		else{
			GPIOA->ODR &=  ~(1U <<11); // 	B
			GPIOA->ODR |=(1<<7);
			if((GPIOB->IDR>>0)&1){
				check = 5000;

					}

			else {					// 	C
				GPIOA->ODR &=  ~(1U <<7);
				GPIOA->ODR |=(1<<9);
				if((GPIOB->IDR>>0)&1){
					check = 7000;

						}

				else{				// 	D
					GPIOA->ODR &=  ~(1U <<9);
					GPIOA->ODR |=(1<<10);
					if((GPIOB->IDR>>0)&1){
						check = 9000;


					}

				}

			}

		}
		EXTI->RPR1 |=(1<<0);
	}


	else{
		GPIOA->ODR |=(1<<11);
		if((GPIOB->IDR>>1)&1){			// 	1
			check = 4000;
		}
		else{						// 	KEYPAD button control for number 4
			GPIOA->ODR &=  ~(1U <<11);
			GPIOA->ODR |=(1<<7);
			if((GPIOB->IDR>>1)&1){

				check = 5200;

					}

			else {						// 	KEYPAD button control for number 7
				GPIOA->ODR &=  ~(1U <<7);
				GPIOA->ODR |=(1<<9);
				if((GPIOB->IDR>>1)&1){
					check = 6400;


				}
				else{
					GPIOA->ODR &=  ~(1U <<9); // *
					GPIOA->ODR |=(1<<10);
					if((GPIOB->IDR>>1)&1){
						check = 0;
					}

				}

			}

		}
	        EXTI->RPR1 |=(1<<1);
	    }

	SetKeypad();

}
void EXTI4_15_IRQHandler (){

	ResetKeypad();

	GPIOA->ODR |=(1<<11);
	if((GPIOA->IDR>>12)&1){   //3
		check = 4800;
	}
	else{
		GPIOA->ODR &=  ~(1U <<11);   //6
		GPIOA->ODR |=(1<<7);
		if((GPIOA->IDR>>12)&1){
			check = 6000;
		}
		else {
			GPIOA->ODR &=  ~(1U <<7);
			GPIOA->ODR |=(1<<9);
			if((GPIOA->IDR>>12)&1){
				check = 7200;              ///9
			}
			else{
				GPIOA->ODR &=  ~(1U <<9);
				GPIOA->ODR |=(1<<10);
				if((GPIOA->IDR>>12)&1){
					check = 0;         //#

				}

			}

		}

	}

	SetKeypad();
	EXTI->RPR1 |=(1<<12);
}
void EXTI2_3_IRQHandler (){

	ResetKeypad();
	if((EXTI->RPR1>>2)&1){ // 	KEYPAD button control for number 2 - 2nd column
		GPIOA->ODR |=(1<<11);
		if((GPIOB->IDR>>2)&1){
			check = 4400;

				}

		else{
			GPIOA->ODR &=  ~(1U <<11); // 	KEYPAD button control for number 5
			GPIOA->ODR |=(1<<7);
			if((GPIOB->IDR>>2)&1){
				check = 5600;

					}

			else {					// 	KEYPAD button control for number 8
				GPIOA->ODR &=  ~(1U <<7);
				GPIOA->ODR |=(1<<9);
				if((GPIOB->IDR>>2)&1){
					check = 6800;

						}

				else{				// 	KEYPAD button control for number 0
					GPIOA->ODR &=  ~(1U <<9);
					GPIOA->ODR |=(1<<10);
					if((GPIOB->IDR>>2)&1){
						check = 0;


					}

				}

			}

		}

	}
	EXTI->RPR1 |=(1<<2);
	SetKeypad();//
	/*
	 * Keypad Input-Output Initilization and Set-Reset Functions
	 */
}
void KeypadInitForOutput(){
	 RCC->IOPENR |= (3U << 0);

	 GPIOA->MODER &=  ~(3U<<2*11); //PA6 as output  R1
	 GPIOA->MODER |=  (1 <<2*11);


	 GPIOA->MODER &=  ~(3U <<2*7); //PA7  as output R2
	 GPIOA->MODER |=  (1 << 2*7);

	 GPIOA->MODER &=  ~(3U <<2*9); //PA9  as output R3
	 GPIOA->MODER |=  (1 << 2*9);

	 GPIOA->MODER &=  ~(3U <<2*10); //PA10  as output R4
	 GPIOA->MODER |=  (1 << 2*10);
}
void SetKeypad(){
	GPIOA->ODR |= (1<<11);  //R1 set
	GPIOA->ODR |= (1<<7);  //R2 set
	GPIOA->ODR |= (1<<9);  //R3 set
	GPIOA->ODR |= (1<<10);  //R4 set

}
void ResetKeypad(){
	GPIOA->ODR &=  ~(1U <<11); //R1 reset
	GPIOA->ODR &=  ~(1U <<7); //R2 reset
	GPIOA->ODR &=  ~(1U <<9); //R3 reset
	GPIOA->ODR &=  ~(1U <<10);  //R4 reset
}

void KeypadInitForInput(){
		RCC->IOPENR |= (3U << 0);

		GPIOB->MODER &= ~(3U << 2*1);// PB1 as input C1
		GPIOB->PUPDR |= (2U << 2*1); //Use of Pull ups to prevent bouncing

		GPIOB->MODER &= ~(3U << 2*2);// PB2 as input C2
		GPIOB->PUPDR |= (2U << 2*2); //Use of Pull ups to prevent bouncing

		GPIOA->MODER &= ~(3U << 2*12); // PA12 as input C3
		GPIOA->PUPDR |= (2U << 2*12); //Use of Pull ups to prevent bouncing

		GPIOB->MODER &= ~(3U << 2*0); // PB0 as input C4
		GPIOB->PUPDR |= (2U << 2*0); //Use of Pull ups to prevent bouncing


	    EXTI->RTSR1 |=(1U<<0);		// PB0 as interrupt
	    EXTI->EXTICR[0] |= (1U<<8*0);
	    EXTI->IMR1 |=(1<<0);
	    NVIC_SetPriority(EXTI0_1_IRQn,1);
	    NVIC_EnableIRQ(EXTI0_1_IRQn);


	    EXTI->RTSR1 |=(1U<<2); // PB2 as interrupt
	    EXTI->EXTICR[0] |= (1U<<8*2);
 	    EXTI->IMR1 |=(1<<2);
 	    NVIC_SetPriority(EXTI2_3_IRQn,0);
 	   	 NVIC_EnableIRQ(EXTI2_3_IRQn);


	    EXTI->RTSR1 |=(1U<<12);// PA12 as interrupt
	   // EXTI->EXTICR[3] |= (1U<<8*0);
	    EXTI->IMR1 |=(1<<12);
	    NVIC_SetPriority(EXTI4_15_IRQn,2);
	     NVIC_EnableIRQ(EXTI4_15_IRQn);



	    EXTI->RTSR1 |=(1U<<1); // PB1 as interrupt
	    EXTI->EXTICR[0] |= (1U<<8*1);
	    EXTI->IMR1 |=(1<<1);

}
