/*
 * Lab6 Problem1
 * Abdullah MEMİŞOĞLU 171024001
 * SSD.h
 */
#ifndef SSD_H
#define SSD_H

#include "stm32g0xx.h"
/* SSD Functions */
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
void FindNumberPlaces(int);


#endif //SSD_H
