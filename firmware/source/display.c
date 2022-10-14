#include "display.h"
#include "stm8.h"

const uint8_t DIGITS[] = {0x7E, 0x0C, 0xB6, 0x9E, 0xCC, 0xDA, 0xFA, 0x0E, 0xFE, 0xDE};

volatile uint8_t displayBrightness;
volatile uint8_t displayData[2];
uint8_t displayState;
uint8_t displayDigit;

void initialiseDisplay() {
	TIM4->PSCR = 0x06; // Set prescaler to divide clock by 64
	TIM4->IER = 0x01; // Enable interrupt
	TIM4->CR1 = 0x01; // Enable timer
}

void setDisplayBrightness(uint8_t brightness) {
	uint16_t corrected = brightness * brightness;
	displayBrightness = corrected / ((uint8_t) 0xFF);
}

void displayNumber(uint8_t number, uint8_t point) {
	uint8_t right = number % ((uint8_t) 10);
	uint8_t left = ((uint8_t) (number - right)) / ((uint8_t) 10);

	if (point || number > 9) {
		displayData[0] = DIGITS[left] | point;
	} else {
		displayData[0] = 0x00;
	}

	displayData[1] = DIGITS[right];
}

void updateDisplay() __interrupt(23) {
	if (displayState) {
		GPIOA->ODR |= 0x06; // Disable digits
		TIM4->CNTR = displayBrightness;
	} else {
		uint8_t data = displayData[displayDigit];

		GPIOA->ODR |= 0x08; // Disable segments
		GPIOB->ODR |= 0x30;
		GPIOD->ODR |= 0x7C;

		GPIOD->ODR &= ~((data & 0x01) << 5);
		data >>= 1;
		GPIOB->ODR &= ~((data & 0x01) << 5);
		data >>= 1;
		GPIOB->ODR &= ~((data & 0x01) << 4);
		data >>= 1;
		GPIOD->ODR &= ~((data & 0x01) << 6);
		data >>= 1;
		GPIOD->ODR &= ~((data & 0x01) << 2);
		data >>= 1;
		GPIOD->ODR &= ~((data & 0x01) << 3);
		data >>= 1;
		GPIOA->ODR &= ~((data & 0x01) << 3);
		data >>= 1;
		GPIOD->ODR &= ~((data & 0x01) << 4);

		if (displayData[displayDigit]) {
			GPIOA->ODR &= ~(0x04 >> displayDigit); // Enable active digit
		}

		displayDigit = !displayDigit;

		TIM4->CNTR = 0xFF - displayBrightness;
	}

	displayState = !displayState;

	TIM4->SR1 = 0x00; // Clear interrupt
}