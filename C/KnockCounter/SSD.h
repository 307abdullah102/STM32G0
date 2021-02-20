/*
 * Project 2
 * Abdullah MEMİŞOĞLU 171024001
 * SSD.h
 */
#ifndef SSD_H
#define SSD_H

#include "stm32g0xx.h"
/* SSD Functions */
void DigitCheck(int, int*, int);
void DisplayCheck(int);

void SSDInit(void);
void ClearSSD(void);
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
void PrintMyNumber(void);
void PrintMinus(void);
void PrintEqual(void);
void Printu(void);
void PrintF(void);
void PrintL(void);
void PrintInvalid(void);
void PrintOverflow(void);
void FindNumberPlaces(int);


#endif //SSD_H
