/*
 * Lab7 Problem 2
 * Abdullah MEMİŞOĞLU 171024001
 * Problem2.h
 */
#ifndef PROBLEM2_H_
#define PROBLEM2_H_


void System_Init();
void InitTimer2();
void InitTimer();
void ADCInit();
void LEDInit();
void UartInit();
void printchar(uint8_t);
void print(char*);
void Delay(volatile uint32_t);
uint16_t ADC_DR();



#endif /* PROBLEM2_H_ */
