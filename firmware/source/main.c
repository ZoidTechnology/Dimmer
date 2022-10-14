#include "stm8.h"
#include "protection.h"
#include "dimmer.h"
#include "encoder.h"
#include "display.h"
#include "storage.h"

#define BUTTON_TIMEOUT 0x0200
#define DISPLAY_TIMEOUT 0x0200
#define DISPLAY_STANDBY_BRIGHTNESS 0x40
#define DISPLAY_ACTIVE_BRIGHTNESS 0xC0

void delay(uint16_t delay) {
	while (delay--) {
		__asm__("nop");
	}
}

uint8_t clamp(uint8_t value, int8_t difference) {
	if (difference > 0 && ((uint8_t) (difference + value)) > 99) {
		return 99;
	}

	if (difference < 0 && ((uint8_t) (-difference)) > value) {
		return 0;
	}

	return value + difference;
}

void main() {
	CLK->CKDIVR = 0x00; // Disable clock prescaler

	GPIOA->ODR = 0x06; // Disable display
	GPIOA->DDR = 0x0E; // Set A1-A3 as output
	GPIOA->CR1 = 0x08; // Set A3 as push-pull

	GPIOB->DDR = 0x30; // Set B4 and B5 as output
	GPIOB->CR1 = 0x30; // Set B4 and B5 as push-pull

	GPIOC->DDR = 0x20; // Set C5 as output
	GPIOC->CR1 = 0xE8; // Set C5 as push-pull and enable pullup for C3, C6 and C7
	GPIOC->CR2 = 0x08; // Enable interrupt for C3

	GPIOD->DDR = 0x7C; // Set D2-D6 as output
	GPIOD->CR1 = 0x7C; // Set D2-D6 as push-pull

	delay(0x8000); // Wait for button debounce circuit to stabilise

	initialiseEncoder();

	__asm__("halt"); // Enable interrupts and wait for interrupt

	buttonReleased = 0;

	initialiseProtection();
	initialiseDimmer();
	initialiseDisplay();

	uint8_t brightness;
	uint8_t currentLimit;

	if (readStorage(&brightness, &currentLimit)) {
		brightness = 50;
		currentLimit = 99;
	}

	setCurrentLimit(currentLimit);

	uint8_t state = 0;
	uint8_t acceleration = 0;
	uint16_t buttonTimeout = 0;
	uint8_t currentBrightness = 0;
	uint8_t targetBrightness = 0;
	uint16_t displayTimeout = 0;
	uint8_t displayCurrentBrightness = 0;
	uint8_t displayTargetBrightness = DISPLAY_STANDBY_BRIGHTNESS;

	while(1) {
		delay(0x1000);

		if (displayTargetBrightness > displayCurrentBrightness) {
			displayCurrentBrightness++;
		}

		if (displayTargetBrightness < displayCurrentBrightness) {
			displayCurrentBrightness--;
		}

		setDisplayBrightness(displayCurrentBrightness);

		if (overload) {
			displayData[0] = 0x7F;
			displayData[1] = 0x71;

			displayTargetBrightness = DISPLAY_ACTIVE_BRIGHTNESS;

			continue;
		}

		int8_t encoderDifference = getEncoderDifference();

		if (encoderDifference < 0) {
			acceleration -= encoderDifference * 16;
		} else {
			acceleration += encoderDifference * 16;
		}

		if (acceleration > 64) {
			acceleration = 64;
		}

		encoderDifference *= acceleration / 16;

		if (acceleration > 0) {
			acceleration--;
		}

		switch (state) {
			case 0:
				if (encoderDifference) {
					brightness = clamp(brightness, encoderDifference);
					displayTimeout = DISPLAY_TIMEOUT;
				}

				displayNumber(brightness, 0);
				targetBrightness = (brightness + 1) << 1;

				if (displayTimeout) {
					displayTargetBrightness = DISPLAY_ACTIVE_BRIGHTNESS;
					displayTimeout--;
				} else {
					displayTargetBrightness = DISPLAY_STANDBY_BRIGHTNESS;
				}

				if ((GPIOC->IDR & 0x08) == 0) {
					if (buttonTimeout < BUTTON_TIMEOUT) {
						buttonTimeout++;
					} else {
						displayTargetBrightness = DISPLAY_ACTIVE_BRIGHTNESS;
						state = 1;
					}
				}

				if (buttonReleased) {
					targetBrightness = 0;
					displayTargetBrightness = 0;
					state = 2;
				}

				break;
			case 1:
				currentLimit = clamp(currentLimit, encoderDifference);

				displayNumber(currentLimit, 1);

				if (buttonReleased) {
					if (buttonTimeout == 0) {
						setCurrentLimit(currentLimit);
						displayTimeout = DISPLAY_TIMEOUT;
						state = 0;
					}

					buttonReleased = 0;
					buttonTimeout = 0;
				}

				break;
			case 2:
				if (displayCurrentBrightness == 0) {
					displayData[0] = 0x00;
					displayData[1] = 0x00;

					if (currentBrightness == 0) {
						writeStorage(brightness, currentLimit);
						WWDG->CR = 0x80; // Enable window watchdog to trigger reset
					}
				}
		}

		if (targetBrightness > currentBrightness) {
			currentBrightness++;
		}

		if (targetBrightness < currentBrightness) {
			currentBrightness--;
		}

		setDimmerBrightness(currentBrightness);
	}
}