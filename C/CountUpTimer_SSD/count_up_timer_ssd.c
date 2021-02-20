/*
Lab 4 Problem 03
Abdullah MEMİŞOĞLU 171024001
 */

#include "stm32g0xx.h"
int global_counter = 0;
int SSDnum = 0;


/* LED Functions */
void LedInit(void);
void LedSet(void);
void LedClear(void);
void LedToggle(void);


/* System Function */
void SystemInitial(void);
void delay(volatile uint32_t s);

/* Button Functions */
void ButtonInit(void);
int ButtonRead(void);

/* SSD Functions */
void SetDigit1 (void);
void SetDigit2 (void);
void SetDigit3 (void);
void SetDigit4 (void);
void PrintOne(void);
void PrintTwo(void);
void PrintThree(void);
void PrintFour(void);
void PrintFive(void);
void PrintSix(void);
void PrintSeven(void);
void PrintEight(void);
void PrintNine(void);
void PrintZero(void);
void PrintFullZeros(void);


void InitTimer(void);
void FindNumberPlaces(int);
void LedControl (int);



int main(void) {


	SystemInitial();
	InitTimer();
	PrintFullZeros();


    while(1){


    }

    return 0;

}

void InitTimer(void){

	RCC->APBENR1 |= (1U<<1);


	TIM3->CR1 = 0;
	TIM3->CR1 |= (1<<7);
	TIM3->CNT = 0;

	TIM3->PSC = 999;
	TIM3->ARR = 16000;

	TIM3->DIER |= (1<<0);
	TIM3->CR1 |= (1<<0);

	NVIC_SetPriority(TIM3_IRQn,0);
	NVIC_EnableIRQ(TIM3_IRQn);


}
void TIM3_IRQHandler (){
	TIM3->SR &= ~(1U << 0);

	if((SSDnum > 0) || ButtonRead()){
		for(int i = 0; i<1000 ; i++){
			SSDnum ++;

			if(SSDnum == 9999){
				SSDnum = 0;

				break;
			}
			FindNumberPlaces(SSDnum);
		}
	}
	else{

		for(int i=0; i<50; i++){
		PrintFullZeros();
		for(int j=0; j<100; j++){
		LedSet();
		}

		}

	}

}

void FindNumberPlaces(int SSD_num){

	int thousand,hundred,ten,one;

	for(int i = 0; i<2; i++){
	thousand = SSD_num/1000;
	delay(150);
	SetDigit1();
	LedControl(thousand);
	delay(150);

	hundred = (SSD_num - thousand*1000)/100;
	SetDigit2();
	LedControl(hundred);
	delay(150);

	ten = (SSD_num - thousand*1000 - hundred*100)/10;
	SetDigit3();
	LedControl(ten);
	delay(150);

	one = (SSD_num - thousand*1000 - hundred*100 - ten*10);
	SetDigit4();
	LedControl(one);
	delay(150);

	}
}

/* SSD FUNCTIONS */

void SetDigit1 (void){
	GPIOA->ODR = (1U << 0); //PA0
}
void SetDigit2 (void){
	GPIOA->ODR = (1U << 1);
}
void SetDigit3 (void){
	GPIOA->ODR = (1U << 4);
}
void SetDigit4 (void){
	GPIOA->ODR = (1U << 5);
}
void PrintOne(void){
	// B=C=0, A=D=E=F=G=1
	GPIOB->ODR = 0x3C8;	//PB3-6-7-8-9 0011_1100_1000
}

void PrintTwo(void){
	 // A=B=G=E=D=0, C=F=1
	GPIOB->ODR = 0x120; // PB5-8  0001_0010_0000
}

void PrintThree(void){
	// A=B=G=C=D=0, E=F=1
	GPIOB->ODR = 0x180; // PB7-8  0001_1000_0000
}

void PrintFour(void){
	// F=B=G=C=0 A=D=E=1
	GPIOB->ODR = 0xC8; // PB3-6-7 0000_1100_1000
}

void PrintFive(void){
	//A=F=G=C=D=0 B=E=1
	GPIOB->ODR = 0x90; // PB4-7 0000_1001_0000
}

void PrintSix(void){
	//A=F=G=C=E=D=0 B=1
	GPIOB->ODR = 0x10; // PB4 0000_0001_0000
}

void PrintSeven(void){
	//A=B=C=0 D=E=F=G=1
	GPIOB->ODR = 0x3C0; // PB6-7-8-9 0011_1100_0000
}

void PrintEight(void){
	//A=B=C=D=E=F=G=0
	GPIOB->ODR = 0x0; // All of them
}

void PrintNine(void){
	//A=B=C=D=F=G=0 E=1
	GPIOB->ODR = 0x80; // PB7 0000_1000_0000
}

void PrintZero(void){
	//A=B=C=D=E=F=0 G=1
	GPIOB->ODR = 0x200; // PB9 0010_0000_0000_0000
}
void PrintFullZeros(void){
	for(int i = 0; i<100; i++){


    SetDigit1();
    PrintZero();
    delay(100);

    SetDigit2();
    PrintZero();
    delay(100);

    SetDigit3();
    PrintZero();
    delay(100);

    SetDigit4();
    PrintZero();
    delay(100);


	}
}

void delay(volatile uint32_t s){
	for(; s>0 ; s--);
}

void LedControl (int x){

	switch (x){

	case 0:
		PrintZero();
		break;
	case 1:
		PrintOne();
		break;
	case 2:
		PrintTwo();
		break;
	case 3:
		PrintThree();
		break;
	case 4:
		PrintFour();
		break;
	case 5:
		PrintFive();
		break;
	case 6:
		PrintSix();
		break;
	case 7:
		PrintSeven();
		break;
	case 8:
		PrintEight();
		break;
	case 9:
		PrintNine();
		break;
	default:
		break;
	}


}
void LedInit(void){
	/* Activate GPIOA and GPIOB */
    RCC->IOPENR |= (3U << 0);

    /* Arange PA6 as output */
    GPIOA->MODER &= ~(3U << 2*6);
    GPIOA->MODER |= (1U << 2*6);

    /* Clear PA6 */
	//GPIOA->ODR |= ~(1U << 6);

}
void ButtonInit(void){
	/* Activate GPIOA and GPIOB */
	 RCC->IOPENR |= (3U << 0);
    /* Arange PB0 as input */
    GPIOA->MODER &= ~(3U << 2*7);
}
int ButtonRead(void){
	int x = ((GPIOA->IDR >> 7) & 0x01);

	if(x) return 1;
	else return 0;


}
void LedSet(void){

	GPIOA->ODR |= (1U << 6);

}
void LedClear(void){
    /* Clear PA6 */
    GPIOA->BRR |= (1U << 6);
}


void SSDInit(void){
	RCC->IOPENR |= (3U << 0);

    /* Arange PA0 as output */
    GPIOA->MODER &= ~(3U << 2*0);
    GPIOA->MODER |= (1U << 2*0);

    /* Arange PA1 as output */
    GPIOA->MODER &= ~(3U << 2*1);
    GPIOA->MODER |= (1U << 2*1);

    /* Arange PA4 as output */
    GPIOA->MODER &= ~(3U << 2*4);
    GPIOA->MODER |= (1U << 2*4);

    /* Arange PA5 as output */
    GPIOA->MODER &= ~(3U << 2*5);
    GPIOA->MODER |= (1U << 2*5);

    /* Arange PB3 as output */
    GPIOB->MODER &= ~(3U << 2*3);
    GPIOB->MODER |= (1U << 2*3);

    /* Arange PB4 as output */
    GPIOB->MODER &= ~(3U << 2*4);
    GPIOB->MODER |= (1U << 2*4);

    /* Arange PB5 as output */
    GPIOB->MODER &= ~(3U << 2*5);
    GPIOB->MODER |= (1U << 2*5);

    /* Arange PB6 as output */
    GPIOB->MODER &= ~(3U << 2*6);
    GPIOB->MODER |= (1U << 2*6);

    /* Arange PB7 as output */
    GPIOB->MODER &= ~(3U << 2*7);
    GPIOB->MODER |= (1U << 2*7);

    /* Arange PB8 as output */
    GPIOB->MODER &= ~(3U << 2*8);
    GPIOB->MODER |= (1U << 2*8);

    /* Arange PB9 as output */
    GPIOB->MODER &= ~(3U << 2*9);
    GPIOB->MODER |= (1U << 2*9);


}


void SystemInitial(){
	SSDInit();
	ButtonInit();
	LedInit();

}








