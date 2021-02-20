#ifndef PROJECT2_H
#define PROJECT2_H

#include "stm32g0xx.h"

int TimerFlag;
int first_digit;
int second_digit;
int third_digit;
int InvalidFlag;


void SystemInitial();
void InitTimer();
void LedInit(void);
void delay(volatile uint32_t);
void KeypadInitForOutput(void);
void KeypadInitForInput(void);
void SetKeypad(void);
void ResetKeypad(void);
void Result(void);
void Floating(float res);


#endif //PROJECT2_H
