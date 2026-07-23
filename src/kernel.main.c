#include <stdint.h>

extern void main() {
  *(volatile uint16_t*)0xb8000 = (unsigned char)'A' | (0x1a << 8); // print 'A' in color as test
  return;
}
