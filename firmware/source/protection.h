#ifndef PROTECTION
#define PROTECTION

#include <stdint.h>

extern volatile uint8_t overload;

void initialiseProtection();
void setCurrentLimit(uint8_t limit);
void overCurrentLimit() __interrupt(22);

#endif