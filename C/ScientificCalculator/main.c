#include "stm32g0xx.h"
#include "Project2.h"
#include "SSD.h"
#include "Keypad.h"


int main(void) {

	SystemInitial();
	SetKeypad();
	GPIOA->ODR |=  (1U << 6); //Set decimal

    while(1) {

    }
    return 0;
}
