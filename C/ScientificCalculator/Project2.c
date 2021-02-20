#include "stm32g0xx.h"
#include "Project2.h"
#include "SSD.h"
#include "Keypad.h"
#include "math.h"

/*
 * System Functions and Variables in here.
 */

int process_flag = 0;
int first_number = 0;
int second_number = 0;
int counter = 0;
int result_flag = 0;
float result = 0;
int TimerFlag = 0;
int InvalidFlag = 0;
float fl = 0;// temporary value for processing
int x = 0; // temporary value for processing
int x1 = 0; // temporary value for processing
int first_digit;
int second_digit;
int third_digit;


/*If there is still no input at the end of 10 seconds, a 10000 loop is set up with
 * a 1ms timer to print the ID.
 *
 *	The PrintFlag will light up with the first input, and the ID will be turned off
	 *	 and the incoming input will be lit.
	 *
	 *
 *	InvalidFlag is set to be 1 in cases such as x / 0 or sqrt (negative).
	 *	 This flag is used to burn InuD shape on SSD.
	 *
	 *
 *	By performing overflow control, if overflow occurs, 0uFL shape is printed on SSD.
 */
void TIM3_IRQHandler(){
	++TimerFlag;

	if(PrintFlag == 0){
		PrintMyNumber();
	}
	else{
		if(TimerFlag >= 10000){
			PrintMyNumber();
		}
		else{
	if(result_flag == 1){

		if(InvalidFlag == 1){
			PrintInvalid();
		}
		else{
		if(result < 9999 && result > -999){

		Floating(result);
		FindNumberPlaces((int)result);
		}
		else{
			PrintOverflow();
		}
			}
		}

	else if(result_flag == 0)
		DigitCheck(flagSSD, InputsFromKeypad, i);

	}
	}
	TIM3->SR &=  ~(1U<<0);

}
/*
 * Initialization for all system.
 */
void SystemInitial(){

	SSDInit();
    KeypadInitForOutput();
    KeypadInitForInput();
	InitTimer();

}

void InitTimer(){

		RCC->APBENR1 |=(1U<<1);
		TIM3->CR1=0;
		TIM3->CR1 |=(1<<7);
		TIM3->CNT =0;
		TIM3->PSC=1;
		TIM3->ARR=(16000);
		TIM3->DIER |=(1<<0);
		TIM3->CCMR1 |=(1<<3);

		TIM3->CR1 |= (1<<0);

		NVIC_SetPriority(TIM3_IRQn,3);
		NVIC_EnableIRQ(TIM3_IRQn);

}

/*
 *
 *	In the floating function,
 *	 the digits of the result number after "," are stored in variables
 *	  first_digit, second_digit, third_digit.
 */
void Floating(float res){
	fl = res - (int)res; // res = 66.35 -- fl = 0.352
	x = fl*1000;  //x = 352
	x1 = x%100; //x1 = 52
	first_digit = (x-x1)/100; //f_d = 3
	x = x1%10;					// x = 2
	second_digit = (x1-x)/10; //52-2=50 s_d = 5
	third_digit = x;

}
/*
 *
 *	With the control of the values ​​in the array, what operation will be done (log ln + - sin etc.)
 *	or the first number, the second number determination operations are performed. These operations
 *  are done and kept in the result variable.
 */
void Result(void){


	for(int a = 0; a<array_size; a++){
		 if(InputsFromKeypad[a] == 14){

		 	 if(InputsFromKeypad[a+1] == 14){
		 	 	    if(InputsFromKeypad[a+2] == 10){
						process_flag = 9; //sin
						counter = a;
						break;
		 	 	   }
		 	 	    else if(InputsFromKeypad[a+2] == 11){
							process_flag = 10; //cos
							counter = a;
							break;
						}
		 	 	    else if(InputsFromKeypad[a+2] == 12){
							process_flag = 11; //tan
							counter = a;
							break;
						}
		 	 	    else if(InputsFromKeypad[a+2] == 13){
							process_flag = 12; //cot
							counter = a;
							break;
						}
		 	 	    else if(InputsFromKeypad[a+2] == 14){
							process_flag = 13; //pi
							counter = a;
							break;
						}

				}

		 	 	   else if(InputsFromKeypad[a+1] == 10){
						process_flag = 5; //log
						counter = a;
						break;
					}
					else if(InputsFromKeypad[a+1] == 11){
						process_flag = 6; //ln
						counter = a ;
						break;
					}
					else if(InputsFromKeypad[a+1] == 12){
						process_flag = 7; //sqrt
						counter = a;
						break;
					}
					else if(InputsFromKeypad[a+1] == 13){
						process_flag = 8; //x^2
						counter = a;
						break;
					}

				}

		else if(InputsFromKeypad[a] == 10){
			process_flag = 1; //ADD
			counter = a;

		}
		else if(InputsFromKeypad[a] == 11){
			process_flag = 2; //Sub
			counter = a;

		}
		else if(InputsFromKeypad[a] == 12){
			process_flag = 3; //Multip
			counter = a;

		}
		else if(InputsFromKeypad[a] == 13){
			process_flag = 4; //Divid
			counter = a;

		}


	}
	//FINDING NUMBERS
	for (int b = 0; b<counter; b++){
		first_number += pow(10,b)*InputsFromKeypad[counter-b-1];

	}
	for (int b = counter+1; b<array_size-1 ; b++){
		second_number += pow(10,(b-counter-1))*InputsFromKeypad[array_size + counter - b - 1];

	}


	//PROCESS
	if(process_flag == 1){
		result = (float)(first_number + second_number);
	}
	else if(process_flag == 2){
		result = (float)(first_number - second_number);
	}
	else if(process_flag == 3){
		result = (float)(first_number * second_number);
	}
	else if(process_flag == 4){
		if(second_number == 0){			// x/0 invalid
			InvalidFlag = 1;
		}
		result = (float)first_number / second_number;
	}
	else if(process_flag == 5){
		result = log10((float)first_number);
	}
	else if(process_flag == 6){
		result = log((float)first_number);
	}
	else if(process_flag == 7){
		if(first_number < 0){		//sqrt(negative) Invalid
			InvalidFlag = 1;
		}
		result = sqrt((float)first_number);
	}
	else if(process_flag == 8){
		result = pow((float)first_number,2);
	}
	else if(process_flag == 9){
		result = sin((first_number*3.14)/180);
	}
	else if(process_flag == 10){
		result = cos((first_number*3.14)/180);
	}
	else if(process_flag == 11){
		if((first_number - 90) % 180 == 0){   // tan 90 - 270 ... vs Invalid
			InvalidFlag = 1;
		}
		result = tan((first_number*3.14)/180);
	}
	else if(process_flag == 12){
		if((first_number) % 180 == 0){  // COT 180-360 vs Invalid
			InvalidFlag = 1;
		}
		result = (1/tan((first_number*3.14)/180)); //pi
	}
	else if(process_flag == 13){
		result = (float)3.141; //pi
	}

	result_flag = 1;



}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}

