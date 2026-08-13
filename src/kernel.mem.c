#include "kernel.mem.h"
#include "kernel.utils.h"
#include <stdint.h>

#define SECTOR_SIZE  0x2
#define SECTOR_COUNT 0x8000 // multiples of 8
#define SECTOR_BASE  0x100000
#define BITMAP_BASE  0x110000

volatile uint8_t* const bitmap = (volatile uint8_t* const)BITMAP_BASE;
volatile uint8_t* const memory = (volatile uint8_t* const)SECTOR_BASE;

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
    if(!(getBit(*(bitmap + i / 8), i%8))) free_length ++;
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
    setBit(bitmap + i / 8, i%8, 1);

  //return pointer
  return memory + index * SECTOR_SIZE;
}

void free(volatile void* ptr, uint32_t size){
  if(!(ptr && size)) return;
  for(uint32_t i = 0; i < size; i++) {
    uint32_t index = ((uint8_t*)ptr - memory) / SECTOR_SIZE;
    setBit(bitmap + (index + i) / 8, (index+i)%8, 0);
  }
}

