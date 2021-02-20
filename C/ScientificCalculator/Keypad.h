#ifndef KEYPAD_H
#define KEYPAD_H

#include "stm32g0xx.h"
int i;
int c;
int InputsFromKeypad[50];
int flagSSD;
int PrintFlag;
int array_size;

/*KEYPAD Functions */
void KeypadInitForOutput(void);
void KeypadInitForInput(void);
void SetKeypad(void);
void ResetKeypad(void);


#endif //KEYPAD_H
