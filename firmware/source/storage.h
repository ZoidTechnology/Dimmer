#ifndef STORAGE
#define STORAGE

#include <stdint.h>

uint8_t readStorage(uint8_t *brightness, uint8_t *currentLimit);
void writeStorage(uint8_t brightness, uint8_t currentLimit);

#endif