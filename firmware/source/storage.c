#include "storage.h"
#include "stm8.h"

#define EEPROM ((uint8_t *) 0x4000)

uint8_t calculateChecksum(uint8_t length) {
	uint8_t checksum = 0xFF;

	for (uint8_t i = 0; i < length; i++) {
		checksum ^= EEPROM[i];
	}

	return checksum;
}

uint8_t readStorage(uint8_t *brightness, uint8_t *currentLimit) {
	*brightness = EEPROM[0];
	*currentLimit = EEPROM[1];

	return calculateChecksum(3);
}

void writeStorage(uint8_t brightness, uint8_t currentLimit) {
	FLASH->DUKR = 0xAE; // Write hardware key 1
	FLASH->DUKR = 0x56; // Write hardware key 2 to disable EEPROM write protection

	while (!(FLASH->IAPSR & 0x08)); // Wait for EEPROM write protection to be disabled

	EEPROM[0] = brightness;
	EEPROM[1] = currentLimit;
	EEPROM[2] = calculateChecksum(2);

	FLASH->IAPSR &= 0xF7; // Enable EEPROM write protection
}