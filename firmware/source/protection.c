#include "protection.h"
#include "stm8.h"

volatile uint8_t overload;

void initialiseProtection() {
	ADC1->CSR = 0x12; // Enable watchdog interrupt and set ADC channel to AIN2
	ADC1->CR1 = 0x03; // Enable continuous conversion and wake ADC
	ADC1->CR1 |= 0x01; // Enable ADC
}

void setCurrentLimit(uint8_t limit) {
	uint16_t threshold = ((uint16_t) (limit * ((uint8_t) 253))) / ((uint8_t) 56); // Threshold = I * 0.01 * 22.05 * (1024 / 5)

	ADC1->HTRL = threshold & 0x03;
	ADC1->HTRH = threshold >> 2;
}

void overCurrentLimit() __interrupt(22) {
	TIM2->CCER1 = 0x00; // Disable capture compare for dimmer
	ADC1->CSR &= 0xEF; // Disable watchdog interrupt
	overload = 0x01;
}