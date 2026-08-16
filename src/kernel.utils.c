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

uint8_t doesArrayContainByte(int8_t* array, uint32_t size, int8_t target) {
  if(!array || !size) return 0;

  for(uint32_t i = 0; i < size; i ++)
    if(*(array + i) == target) 
      return 1;
  
  return 0;
}

uint8_t appendByteToArray(int8_t* array, uint32_t size, int8_t byte) {
  if(!array || !size || !byte) return 1; 

  for(uint32_t i = 0; i < size; i ++) {
    if(!*(array + i)) {
      *(array + i) = byte;
      return  0;
    }
  }
  return 2;
}

uint32_t getIndexOfByteFromArray(int8_t* array, uint32_t size, int8_t byte) {
  if(!array || !size) return 0; 

  for(uint32_t i = 0; i < size; i ++)
    if(*(array + i) == byte)
      return  i;
  return 0;
}

