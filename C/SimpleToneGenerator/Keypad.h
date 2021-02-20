/*
 * Lab6 Problem 1
 * Abdullah MEMİŞOĞLU 171024001
 * Keypad.h
 */
#ifndef KEYPAD_H
#define KEYPAD_H

#include "stm32g0xx.h"

uint32_t check ;

/*KEYPAD Functions */
void KeypadInitForOutput(void);
void KeypadInitForInput(void);
void SetKeypad(void);
void ResetKeypad(void);



#endif //KEYPAD_H
