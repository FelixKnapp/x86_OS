#include "kernel.utils.h"

uint8_t translateTo8Bit(uint8_t value);

void setBit(volatile uint8_t* ptr, uint8_t bit, uint8_t value) {
  bit = translateTo8Bit(bit);

  *ptr = *ptr & ~bit;
  if(value) *ptr = *ptr | (0xff & bit);
}

void setBits(volatile uint8_t* ptr, uint8_t bits, uint8_t value) {
  *ptr = *ptr & ~bits;
  if(value) *ptr = *ptr | (0xff & bits);
}

uint8_t getBit(uint8_t value, uint8_t bit) {
  return value & translateTo8Bit(bit);
}

uint8_t translateTo8Bit(uint8_t value) {
  switch (value) {
    case 0:
      return 0b00000001;
    case 1:
      return 0b00000010;
    case 2:
      return 0b00000100;
    case 3:
      return 0b00001000;
    case 4:
      return 0b00010000;
    case 5:
      return 0b00100000;
    case 6:
      return 0b01000000;
    case 7:
      return 0b10000000;
  }
  return 0;
}

