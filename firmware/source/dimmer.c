#include "dimmer.h"
#include "stm8.h"

void initialiseDimmer() {
	TIM2->PSCR = 0x02; // Set prescaler

	TIM2->ARRH = 0x05; // Set auto reload high
	TIM2->ARRL = 0xAA; // Set auto reload low

	TIM2->CCMR1 = 0x60; // Set capture compare mode to PWM
	TIM2->CCER1 = 0x01; // Enable capture compare

	TIM2->CR1 = 0x01; // Enable timer
}

void setDimmerBrightness(uint8_t brightness) {
	uint16_t corrected = brightness * brightness;
	corrected /= 32;
	corrected += brightness;
	
	TIM2->CCR1H = corrected >> 8;
	TIM2->CCR1L = corrected;
}