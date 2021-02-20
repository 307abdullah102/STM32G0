/*
 * Lab7 Problem 2
 * Abdullah MEMİŞOĞLU 171024001
 * main.c
 */

#include "stm32g0xx.h"
#include <stdio.h>
#include "Problem2.h"
#include "SSD.h"

int main(void) {

	System_Init();

    while(1) {

    	Delay(500);
    	int x = ADC_DR();
    	printf("  %d  ", x);
    }

    return 0;
}


