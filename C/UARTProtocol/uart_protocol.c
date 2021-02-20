/*
Lab 5 Problem 01
Abdullah MEMİŞOĞLU 171024001
 */

#include "stm32g0xx.h"


void UartInit(uint32_t baud);
void PrintChar(uint8_t c);
uint8_t uart_rx(void);
void uart_tx (uint8_t data);

int main(void) {

UartInit(9600);


	while(1){
	uart_tx(uart_rx());
	}


    return 0;

}

/*
void USART2_IRQHandler(void){
	USART2-> TDR = (uint16_t)c;

	PrintChar(data);
}
*/
uint8_t prev_data = 0;
void PrintChar(uint8_t c){
	USART2-> TDR = (uint16_t)c;
	prev_data = c;
	while (!(USART2 -> ISR & (1U << 6)));

}


uint8_t uart_rx(void){
	uint8_t data = (uint8_t)USART2 -> RDR;

	return data;
}
void uart_tx (uint8_t data){
	//USART2-> TDR = (uint16_t)data;

	/*
	 * An if block has been added that compares the previous data with
	 *  the previous value to preventan input from the keyboard from being
	 *  pressed continuously until a new input.
	 *  With this block, when a letter is entered, the next input is expected
	 *  instead of printing that letter continuously
	 */


	if(prev_data != data)
	PrintChar(data);


}

/*
 * PA2 and PA3 are connected to the Virtual COM port
 * USART2 module
 */
void UartInit(uint32_t baud){
	//Enable GPIOA
	RCC->IOPENR |= (1U << 0);
	RCC->APBENR1 |= (1U << 17);

	//Setup PA3 as Alternate Function (AF1)
	GPIOA-> MODER &= ~(3U << 2*2);
	GPIOA-> MODER |=  (2U << 2*2);

	// Chose AF1
	GPIOA-> AFR[0] &= ~(0xFU << 4*2);
	GPIOA-> AFR[0] |=  (1U << 4*2);

	//Setup PA3 as Alternate Function (AF1)
	GPIOA-> MODER &= ~(3U << 2*3);
	GPIOA-> MODER |=  (2U << 2*3);

	// Chose AF1
	GPIOA-> AFR[0] &= ~(0xFU << 4*3);
	GPIOA-> AFR[0] |=  (1U << 4*3);

	USART2 -> CR1 = 0;
	USART2 -> CR1 |= (1U << 3); // Transmitter
	USART2 -> CR1 |= (1U << 2); // Receiver

	USART2 -> CR1 |= (1U << 5);

	USART2 -> BRR = (uint16_t)(SystemCoreClock / baud);

	USART2 -> CR1 |= (1U << 0); // Usart Enable

	//NVIC_SetPriority(USART2_IRQn, 1);
	//NVIC_EnableIRQ(USART2_IRQn);

}
