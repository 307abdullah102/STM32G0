
#include "stm32g0xx.h"
#include "SSD.h"
#include "Project2.h"

int thousand,hundred,ten,one;
int val=0;
int val2=0;
int val3=0;

/* SSD FUNCTIONS */

/*
 * SSD Initialization
 */
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

    /* Arange PA6 as output */
    GPIOA->MODER &= ~(3U << 2*6);
    GPIOA->MODER |= (1U << 2*6);

    /* Arange PB3 as output */
    GPIOB->MODER &= ~(3U << 2*3);
    GPIOB->MODER |= (1U << 2*3);

    /* Arange PB4 as output */
    GPIOB->MODER &= ~(3U << 2*4);
    GPIOB->MODER |= (1U << 2*4);

    /* Arange PB5 as output */
    GPIOB->MODER &= ~(3U << 2*5);
    GPIOB->MODER |= (1U << 2*5);

    /* Arange PB11 as output */
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
/*
 * Clear SSD
 */
void ClearSSD(void){
	GPIOB->ODR |= (1U<<3);
	GPIOB->ODR |= (1U<<4);
	GPIOB->ODR |= (1U<<5);
	GPIOB->ODR |= (1U<<6);
	GPIOB->ODR |= (1U<<7);
	GPIOB->ODR |= (1U<<8);
	GPIOB->ODR |= (1U<<9);
}

/*
 *
 * Input from the keypad is kept in the array named InputsFromKeypad.
 * FlagSSD is a variable in which 4 digits are filled in SSD and the new input is not written on the SSD.
 *
 *
 * In the DigitCheck function, x correspond to FlagSSD  y corresponds to InputsFromKeypad and i = i.
 *
 *
 * If there is only 1 input from the keypad, the flagSSD will be 3 and by entering case 3,
 * it will print a number at the 4th digit, 1 more input will be entered, flagSSD will be 2
 * and data will be entered into digit3 and digit4. and so on
 */
void DigitCheck(int x, int* y, int i){

	switch (x){

	case 0:
		delay(100);
		SetDigit1();
		DisplayCheck(*(y+(i-4)));
		delay(100);
		SetDigit2();
		DisplayCheck(*(y+(i-3)));
		delay(100);
		SetDigit3();
		DisplayCheck(*(y+(i-2)));
		delay(100);
		SetDigit4();
		DisplayCheck(*(y+i-1));
		break;

	case 1:
		delay(100);
		SetDigit2();
		DisplayCheck(*(y+(i-3)));
		delay(100);
		SetDigit3();
		DisplayCheck(*(y+(i-2)));
		delay(100);
		SetDigit4();
		DisplayCheck(*(y+i-1));
		break;

	case 2:
		delay(100);
		SetDigit3();
		DisplayCheck(*(y+(i-2)));
		delay(100);
		SetDigit4();
		DisplayCheck(*(y+i-1));
		break;

	case 3:
		SetDigit4();
		delay(100);
		DisplayCheck(*(y+i-1));
		delay(100);
		break;


	default:
		break;
	}
}

/*
 * Written function to print numbers or figures stored in the array to SSD
 */
void DisplayCheck(int x){
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
	case 10:
		PrintMinus();
		break;
	case 11:
		PrintMinus();
		break;
	case 12:
		PrintMinus();
		break;
	case 13:
		PrintMinus();
		break;
	case 14:
		PrintMinus();
		break;
	case 15:
		PrintEqual();
		break;

	default:
		break;
	}
}
/*
 * Setting SSD Digits
 */
void SetDigit1 (void){
	GPIOA->ODR |= (1U << 0);//PA0
	GPIOA->ODR &=  ~(1U << 1);
	GPIOA->ODR &=  ~(1U << 4);
	GPIOA->ODR &=  ~(1U << 5);
}
void SetDigit2 (void){
	GPIOA->ODR |= (1U << 1);
	GPIOA->ODR &=  ~(1U << 0);
	GPIOA->ODR &=  ~(1U << 4);
	GPIOA->ODR &=  ~(1U << 5);
}
void SetDigit3 (void){
	GPIOA->ODR |= (1U << 4);
	GPIOA->ODR &=  ~(1U << 1);
	GPIOA->ODR &=  ~(1U << 0);
	GPIOA->ODR &=  ~(1U << 5);
}
void SetDigit4 (void){
	GPIOA->ODR |= (1U << 5);
	GPIOA->ODR &=  ~(1U << 1);
	GPIOA->ODR &=  ~(1U << 4);
	GPIOA->ODR &=  ~(1U << 0);
}

/*
 * SSD Number and Shape Printings
 */
void PrintOne(void){
	// B=C=0, A=D=E=F=G=1
	GPIOB->ODR = 0x3C8;	//PB3-6-7-8-9 0011_1100_1000
	//GPIOB->ODR |= (1<<3);
	//GPIOB->ODR |= (1<<6);
	//GPIOB->ODR |= (1<<7);
	//GPIOB->ODR |= (1<<8);
	//GPIOB->ODR |= (1<<9);
}

void PrintTwo(void){
	 // A=B=G=E=D=0, C=F=1
	GPIOB->ODR = 0x120; // PB5-8  0001_0010_0000
	//GPIOB->ODR |= (1<<5);
	//GPIOB->ODR |= (1<<8);

}

void PrintThree(void){
	// A=B=G=C=D=0, E=F=1
	GPIOB->ODR = 0x180; // PB7-8  0001_1000_0000
	//GPIOB->ODR |= (1<<7);
	//GPIOB->ODR |= (1<<8);
}

void PrintFour(void){
	// F=B=G=C=0 A=D=E=1
	GPIOB->ODR = 0xC8; // PB3-6-7 0000_1100_1000
	//GPIOB->ODR |= (1<<3);
	//GPIOB->ODR |= (1<<6);
	//GPIOB->ODR |= (1<<7);
	}

void PrintFive(void){
	//A=F=G=C=D=0 B=E=1
	GPIOB->ODR = 0x90; // PB4-7 0000_1001_0000
	//GPIOB->ODR |= (1<<4);
	//GPIOB->ODR |= (1<<7);
}

void PrintSix(void){
	//A=F=G=C=E=D=0 B=1
	GPIOB->ODR = 0x10; // PB4 0000_0001_0000
	//GPIOB->ODR |= (1<<4);
}

void PrintSeven(void){
	//A=B=C=0 D=E=F=G=1
	GPIOB->ODR = 0x3C0; // PB6-7-8-9 0011_1100_0000
	//GPIOB->ODR |= (1<<6);
	//GPIOB->ODR |= (1<<7);
	//GPIOB->ODR |= (1<<8);
	//GPIOB->ODR |= (1<<9);
}

void PrintEight(void){
	//A=B=C=D=E=F=G=0
	GPIOB->ODR = 0x0; // All of them

}

void PrintNine(void){
	//A=B=C=D=F=G=0 E=1
	GPIOB->ODR = 0x80; // PB7 0000_1000_0000
	//GPIOB->ODR |= (1<<7);
}

void PrintZero(void){
	//A=B=C=D=E=F=0 G=1
	GPIOB->ODR = 0x200; // PB9 0010_0000_0000_0000
	//GPIOB->ODR |= (1<<9);
}
void PrintMinus(void){
	//A=B=C=G=E=F=1 G=0
	GPIOB->ODR = 0x1F8;	// PB6 0000_0001_0000_1000
}
void PrintEqual(void){
	// G=D=0, A=B=E=C=F=1
	GPIOB->ODR = 0x1B8;	//PB3-4-5-7-9 0001_1011_1000
}
void PrintL(void){
	// F=E=D=0, A=B=C=G=1 //PB 3-4-5-8 0010_0011_1000
	GPIOB->ODR = 0x238;
}
void PrintF(void){

	// B=C=D=1 //PB 4-5-6 0000_0111_0000
	GPIOB->ODR = 0x70;
}
void Printu(void){
	// E=C=D=0, A=B=F=G=1 //PB 3-4-5-8 0011_0001_1000
	GPIOB->ODR = 0x318;
}
void Printn(void){
	// E=C=G=0, A=B=D=F=1 //PB 3-4-5-8 0001_0101_1000
	GPIOB->ODR = 0x158;
}
/*
 * Shape to print in case of Overflow
 */
void PrintOverflow(void){
	for(int i = 0; i<1500; i++){

    SetDigit1();
    PrintZero();
    delay(100);


    SetDigit2();
    Printu();
    delay(100);


    SetDigit3();
    PrintF();
    delay(100);


    SetDigit4();
    PrintL();
    delay(100);


	}
}
/*
 * Shape to print in case of Invalid
 */
void PrintInvalid(void){
	for(int i = 0; i<1500; i++){

    SetDigit1();
    PrintOne();
    delay(100);


    SetDigit2();
    Printn();
    delay(100);


    SetDigit3();
    Printu();
    delay(100);


    SetDigit4();
    PrintZero();
    delay(100);


	}
}
/*
 *
 * It is the function where the incoming number is thousands-hundreds-tens-ones.
 * The steps are explained with examples.
 *
 * Depending on how many digits the number is, the number of digits after "," is determined.
 * Such as 3 digits after "," if the number is single digit, and 2 digits after ","
 * if it has double digits.
 */
void FindNumberPlaces(int SSD_num){

	val = SSD_num%1000; // SSD_num = 3250 , val = 250
	val = SSD_num - val;// val = 3000;
	thousand = val/1000; // thousand = 3; val = 3000;
	delay(150);
//	SetDigit1();
//	DisplayCheck(thousand);
//	delay(150);

	val = SSD_num - val; // val = 250
	val2 = val%100;  // val 2 = 50
	val2 = val - val2; // val2 = 200
	hundred = val2 / 100; // hundred = 2; val 2 = 200 val = 250
//	SetDigit2();
//	DisplayCheck(hundred);
//	delay(150);

	val = (val - val2); // val = 50
	ten = val/10; // ten = 5
//	SetDigit3();
//	DisplayCheck(ten);
//	delay(150);

	one = val - ten*10;
//	SetDigit4();
//	DisplayCheck(one);
//	delay(150);

	if(thousand !=0){

			GPIOA->ODR |=  (1U << 6);
			SetDigit1();
			DisplayCheck(thousand);
			delay(150);


			GPIOA->ODR |=  (1U << 6);
			SetDigit2();
			DisplayCheck(hundred);
			delay(150);


			GPIOA->ODR |=  (1U << 6);
			SetDigit3();
			DisplayCheck(ten);
			delay(150);


			GPIOA->ODR &=  ~(1U << 6);
			SetDigit4();
			DisplayCheck(one);
			delay(150);



		}
	else{
		if(hundred != 0){
				GPIOA->ODR |=  (1U << 6);
				SetDigit1();
				DisplayCheck(hundred);
				delay(150);


				GPIOA->ODR |=  (1U << 6);
				SetDigit2();
				DisplayCheck(ten);
				delay(150);


				GPIOA->ODR &=  ~(1U << 6);
				SetDigit3();
				DisplayCheck(one);
				delay(150);


				GPIOA->ODR |=  (1U << 6);
				SetDigit4();
				DisplayCheck(first_digit);
				delay(150);

		}
		else{
			if(ten != 0){
					GPIOA->ODR |=  (1U << 6);
					SetDigit1();
					DisplayCheck(ten);
					delay(150);


					GPIOA->ODR &=  ~(1U << 6);
					SetDigit2();
					DisplayCheck(one);
					delay(150);


					GPIOA->ODR |=  (1U << 6);
					SetDigit3();
					DisplayCheck(first_digit);
					delay(150);


					GPIOA->ODR |=  (1U << 6);
					SetDigit4();
					DisplayCheck(second_digit);
					delay(150);


				}
			else{
					GPIOA->ODR &=  ~(1U << 6);
					SetDigit1();
					DisplayCheck(one);
					delay(150);


					GPIOA->ODR |=  (1U << 6);
					SetDigit2();
					DisplayCheck(first_digit);
					delay(150);

					GPIOA->ODR |=  (1U << 6);
					SetDigit3();
					DisplayCheck(second_digit);
					delay(150);

					GPIOA->ODR |=  (1U << 6);
					SetDigit4();
					DisplayCheck(third_digit);
					delay(150);

			}
		}

		}



}
/*
 * My ID number for default SSD screen.
 */
void PrintMyNumber(void){
	for(int i = 0; i<1500; i++){

    SetDigit1();
    PrintOne();
    delay(100);


    SetDigit2();
    PrintSeven();
    delay(100);


    SetDigit3();
    PrintZero();
    delay(100);


    SetDigit4();
    PrintOne();
    delay(100);


	}
}
