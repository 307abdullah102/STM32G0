#include "stm32g0xx.h"
#include "Keypad.h"
#include "Project2.h"
#include "SSD.h"

int i = 0;
int c = 0;
int InputsFromKeypad[50];
int flagSSD = 4;
int PrintFlag = 0;
int array_size = 0;

/*
 * interrupts are set depending on the input pins of the keypad. When any button is pressed,
 *  the relevant interrup was entered and the outputs were set-reset to learn which button
 *  the input came from.
 *
 *  In this section, the inputsFromKeypad array is filled. When the # key is pressed
 *  from the keypad, the Result () function will be activated.
 */
void EXTI0_1_IRQHandler (){ //c1
	++PrintFlag;
	TimerFlag = 0;
	ResetKeypad();
	if((EXTI->RPR1>>0)&1){ //To find out if the interrupt is from Px0 or Px1.
		GPIOA->ODR |=(1<<11); // 	KEYPAD button control for number 2 - 2nd column
		if((GPIOB->IDR>>0)&1){
			if(i <= 3){
			InputsFromKeypad[i] = 10;
			flagSSD = flagSSD - 1;
			i = i+1;
			++array_size;
			}
			else if(i > 3){
			InputsFromKeypad[array_size] = 10;
			++array_size;
			}
			delay(250000);


				//i = 10;//A
				}

		else{
			GPIOA->ODR &=  ~(1U <<11); // 	KEYPAD button control for number 5
			GPIOA->ODR |=(1<<7);
			if((GPIOB->IDR>>0)&1){
				//i = 11;//B
				if(i <= 3){
				InputsFromKeypad[i] = 11;
				flagSSD = flagSSD - 1;
				i = i+1;
				++array_size;
				}
				else if(i > 3){
				InputsFromKeypad[array_size] = 11;
				++array_size;
				}
				delay(250000);

					}

			else {					// 	KEYPAD button control for number 8
				GPIOA->ODR &=  ~(1U <<7);
				GPIOA->ODR |=(1<<9);
				if((GPIOB->IDR>>0)&1){
					//i = 12;//C
					if(i <= 3){
					InputsFromKeypad[i] = 12;
					flagSSD = flagSSD - 1;
					i = i+1;
					++array_size;
					}
					else if(i > 3){
					InputsFromKeypad[array_size] = 12;
					++array_size;
					}
					delay(250000);

						}

				else{				// 	KEYPAD button control for number 0
					GPIOA->ODR &=  ~(1U <<9);
					GPIOA->ODR |=(1<<10);
					if((GPIOB->IDR>>0)&1){
						//i = 13;//D
						if(i <= 3){
						InputsFromKeypad[i] = 13;
						flagSSD = flagSSD - 1;
						i = i+1;
						++array_size;
						}
						else if(i > 3){
						InputsFromKeypad[array_size] = 13;
						++array_size;
						}
						delay(250000);


					}

				}

			}

		}
		EXTI->RPR1 |=(1<<0);
	}


	else{
		GPIOA->ODR |=(1<<11);
		if((GPIOB->IDR>>1)&1){			// 	KEYPAD button control for number 4
			//i = 1;
			if(i <= 3){
			InputsFromKeypad[i] = 1;
			flagSSD = flagSSD - 1;
			i = i+1;
			++array_size;
			}
			else if(i > 3){
			InputsFromKeypad[array_size] = 1;
			++array_size;
			}
			delay(250000);

		}
		else{						// 	KEYPAD button control for number 4
			GPIOA->ODR &=  ~(1U <<11);
			GPIOA->ODR |=(1<<7);
			if((GPIOB->IDR>>1)&1){
				//i = 4;
				if(i <= 3){
				InputsFromKeypad[i] = 4;
				flagSSD = flagSSD - 1;
				i = i+1;
				++array_size;
				}
				else if(i > 3){
				InputsFromKeypad[array_size] = 4;
				++array_size;
				}
				delay(250000);

					}

			else {						// 	KEYPAD button control for number 7
				GPIOA->ODR &=  ~(1U <<7);
				GPIOA->ODR |=(1<<9);
				if((GPIOB->IDR>>1)&1){
					//i = 7;
					if(i <= 3){
					InputsFromKeypad[i] = 7;
					flagSSD = flagSSD - 1;
					i = i+1;
					++array_size;
					}
					else if(i > 3){
					InputsFromKeypad[array_size] = 7;
					++array_size;
					}
					delay(250000);


				}
				else{
					GPIOA->ODR &=  ~(1U <<9);
					GPIOA->ODR |=(1<<10);
					if((GPIOB->IDR>>1)&1){
						//i = 14; //  *  		* = 14;
						if(i <= 3){
						InputsFromKeypad[i] = 14;
						flagSSD = flagSSD - 1;
						i = i+1;
						++array_size;
						}
						else if(i > 3){
						InputsFromKeypad[array_size] = 14;
						++array_size;
						}
						delay(250000);

					}

				}

			}

		}
	        EXTI->RPR1 |=(1<<1);
	    }

	SetKeypad();

}
void EXTI4_15_IRQHandler (){
	++PrintFlag;
	TimerFlag = 0;
	ResetKeypad();

	GPIOA->ODR |=(1<<11);
	if((GPIOA->IDR>>12)&1){
		//i = 3;
		if(i <= 3){
		InputsFromKeypad[i] = 3;
		flagSSD = flagSSD - 1;
		i = i+1;
		++array_size;
		}
		else if(i > 3){
		InputsFromKeypad[array_size] = 3;
		++array_size;
		}
		delay(250000);
	}
	else{
		GPIOA->ODR &=  ~(1U <<11);
		GPIOA->ODR |=(1<<7);
		if((GPIOA->IDR>>12)&1){
			//i = 6;
			if(i <= 3){
			InputsFromKeypad[i] = 6;
			flagSSD = flagSSD - 1;
			i = i+1;
			++array_size;
			}
			else if(i > 3){
			InputsFromKeypad[array_size] = 6;
			++array_size;
			}
			delay(250000);
		}
		else {
			GPIOA->ODR &=  ~(1U <<7);
			GPIOA->ODR |=(1<<9);
			if((GPIOA->IDR>>12)&1){
				//i = 9;
				if(i <= 3){
				InputsFromKeypad[i] = 9;
				flagSSD = flagSSD - 1;
				i = i+1;
				++array_size;
				}
				else if(i > 3){
				InputsFromKeypad[array_size] = 9;
				++array_size;
				}
				delay(250000);
			}
			else{
				GPIOA->ODR &=  ~(1U <<9);
				GPIOA->ODR |=(1<<10);
				if((GPIOA->IDR>>12)&1){
					//i = 15;//			# = 15
					if(i <= 3){
					InputsFromKeypad[i] = 15;
					flagSSD = flagSSD - 1;
					i = i+1;
					++array_size;
					}
					else if(i > 3){
					InputsFromKeypad[array_size] = 15;
					++array_size;
					}
					delay(250000);
					Result();

				}

			}

		}

	}

	SetKeypad();
	EXTI->RPR1 |=(1<<12);
}
void EXTI2_3_IRQHandler (){
	++PrintFlag;
	TimerFlag = 0;
	ResetKeypad();
	if((EXTI->RPR1>>2)&1){ // 	KEYPAD button control for number 2 - 2nd column
		GPIOA->ODR |=(1<<11);
		if((GPIOB->IDR>>2)&1){
				//i = 2;
			if(i <= 3){
			InputsFromKeypad[i] = 2;
			flagSSD = flagSSD - 1;
			i = i+1;
			++array_size;
			}
			else if(i > 3){
			InputsFromKeypad[array_size] = 2;
			++array_size;
			}
			delay(250000);

				}

		else{
			GPIOA->ODR &=  ~(1U <<11); // 	KEYPAD button control for number 5
			GPIOA->ODR |=(1<<7);
			if((GPIOB->IDR>>2)&1){
				//i = 5 ;
				if(i <= 3){
				InputsFromKeypad[i] = 5;
				flagSSD = flagSSD - 1;
				i = i+1;
				++array_size;
				}
				else if(i > 3){
				InputsFromKeypad[array_size] = 5;
				++array_size;
				}
				delay(250000);

					}

			else {					// 	KEYPAD button control for number 8
				GPIOA->ODR &=  ~(1U <<7);
				GPIOA->ODR |=(1<<9);
				if((GPIOB->IDR>>2)&1){
					//i = 8;
					if(i <= 3){
					InputsFromKeypad[i] = 8;
					flagSSD = flagSSD - 1;
					i = i+1;
					++array_size;
					}
					else if(i > 3){
					InputsFromKeypad[array_size] = 8;
					++array_size;
					}
					delay(250000);

						}

				else{				// 	KEYPAD button control for number 0
					GPIOA->ODR &=  ~(1U <<9);
					GPIOA->ODR |=(1<<10);
					if((GPIOB->IDR>>2)&1){
						//i = 0;
						if(i <= 3){
						InputsFromKeypad[i] = 0;
						flagSSD = flagSSD - 1;
						i = i+1;
						++array_size;
						}
						else if(i > 3){
						InputsFromKeypad[array_size] = 0;
						++array_size;
						}
						delay(250000);


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
