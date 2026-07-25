#ifndef _KERNEL_MEM_H_
#define _KERNEL_MEM_H_

#include <stdint.h>

void free(volatile void* ptr, uint32_t size);

volatile void* memalloc(uint32_t size);

void clearMem();

#endif

