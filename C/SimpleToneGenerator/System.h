/*
 * Lab 6 Problem
 * Abdullah MEMİŞOĞLU 171024001
 * Project2.h
 */
#ifndef PROJECT2_H
#define PROJECT2_H

#include "stm32g0xx.h"

int first_digit;
int second_digit;
int third_digit;
uint32_t check;



void SystemInitial();
void InitTimer();
void SpeakerInit(void);
void delay(volatile uint32_t);
void InitTimer2(void);


#endif //PROJECT2_H
