#include "encoder.h"
#include "stm8.h"

#define CENTRE 0x80

volatile uint8_t buttonReleased;

void initialiseEncoder() {
	EXTI->CR1 = 0x10; // Set interrupt sensitivity as rising edge for port C

	TIM1->ARRH = 0x00; // Set auto reload high
	TIM1->ARRL = 0xFF; // Set auto reload low

	TIM1->CNTRL = CENTRE;

	TIM1->SMCR = 0x02; // Set mode to encoder

	TIM1->CR1 = 0x01; // Enable timer
}

int8_t getEncoderDifference() {
	int8_t difference = -(TIM1->CNTRL - CENTRE);
	TIM1->CNTRL = CENTRE;
	return difference;
}

void releaseButton() __interrupt(5) {
	buttonReleased = 0x01;
}