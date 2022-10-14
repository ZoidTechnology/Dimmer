#ifndef ENCODER
#define ENCODER

#include <stdint.h>

extern volatile uint8_t buttonReleased;

void initialiseEncoder();
int8_t getEncoderDifference();
void releaseButton() __interrupt(5);

#endif