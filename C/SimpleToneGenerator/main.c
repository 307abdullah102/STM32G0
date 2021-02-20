/*
 * Lab6 Problem 1
 * Abdullah MEMİŞOĞLU 171024001
 * main.c
 */
#include "stm32g0xx.h"
#include "SSD.h"
#include "Keypad.h"
#include "System.h"


int main(void) {

	SystemInitial();
	SetKeypad();


    while(1) {

    }
    return 0;
}
