/*
 * Lab7 Problem 1
 * Abdullah MEMİŞOĞLU 171024001
 * Problem1.h
 */
#ifndef PROBLEM1_H_
#define PROBLEM1_H_


void System_Init();
void InitTimer2();
void InitTimer();
void ADCInit();
void LEDInit();
void Delay(volatile uint32_t);
uint16_t ADC_DR();



#endif /* PROBLEM1_H_ */
