#include "kernel.mem.h"
#include <stdint.h>

#define SECTOR_SIZE  0x2
#define SECTOR_COUNT 0x200 // multiples of 8
#define SECTOR_BASE  0xb9000
#define BITMAP_BASE  0xba000

volatile uint8_t* const bitmap = (volatile uint8_t* const)BITMAP_BASE;
volatile uint8_t* const memory = (volatile uint8_t* const)SECTOR_BASE;

void setBits(volatile uint8_t* ptr, uint8_t bits, uint8_t value);
uint8_t getBit(uint8_t value, uint8_t bit);
uint8_t translateTo8Bit(uint8_t value);

void clearMem(){
  for(uint32_t i = 0; i < SECTOR_COUNT / 8; i++) 
    *(bitmap + i) = 0;

  for(uint32_t i = 0; i < SECTOR_COUNT * SECTOR_SIZE; i++) 
    *(memory + i) = 0;
}

volatile void* memalloc(uint32_t size){
  uint32_t free_length = 0;
  uint32_t min_free_length = SECTOR_COUNT * SECTOR_SIZE;
  uint32_t index = 0;
  uint32_t i = 0;
  uint8_t free_space_found = 0;

  // best fit: searches for smallest gap which fits
  for(; i < SECTOR_COUNT; i++) {
    if(!(getBit(*(bitmap + i / 8), translateTo8Bit(i%8)))) free_length ++;
    else {
      if(free_length < min_free_length && free_length >= size) {
        min_free_length = free_length;
        index = i - free_length;
        free_space_found = 1;
      }

      free_length = 0;
    }
  }
  if(free_length < min_free_length && free_length >= size) {
    min_free_length = free_length;
    index = i - free_length;
    free_space_found = 1;
  }

  // return null pointer if no free space found
  if(!free_space_found) return 0;

  // allocate memory
  for(uint32_t i = index; i < index + size; i++)
    *(memory + i * SECTOR_SIZE) = 0x00;
  for(uint32_t i = index; i < index + size; i++)
    setBits(bitmap + i / 8, translateTo8Bit(i%8), 1);

  //return pointer
  return memory + index * SECTOR_SIZE;
}

void free(volatile void* ptr, uint32_t size){
  if(!(ptr && size)) return;
  for(uint32_t i = 0; i < size; i++) {
    uint32_t index = ((uint8_t*)ptr - memory) / SECTOR_SIZE;
    setBits(bitmap + (index + i) / 8, translateTo8Bit((index+i)%8), 0);
  }
}

void setBits(volatile uint8_t* ptr, uint8_t bits, uint8_t value) {
  *ptr = *ptr & ~bits;
  if(value) *ptr = *ptr | (0xff & bits);
}
uint8_t getBit(uint8_t value, uint8_t bit) {
  return value & bit;
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

