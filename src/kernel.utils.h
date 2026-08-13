#ifndef _KERNEL_UTILS_H_
#define _KERNEL_UTILS_H_

#include <stdint.h>

void setBit(volatile uint8_t* ptr, uint8_t bit, uint8_t value);

void setBits(volatile uint8_t* ptr, uint8_t bits, uint8_t value);

uint8_t getBit(uint8_t value, uint8_t bit);

#endif

