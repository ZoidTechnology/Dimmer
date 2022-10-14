#ifndef DISPLAY
#define DISPLAY

#include <stdint.h>

extern volatile uint8_t displayData[2];

void initialiseDisplay();
void setDisplayBrightness(uint8_t brightness);
void displayNumber(uint8_t number, uint8_t point);
void updateDisplay() __interrupt(23);

#endif