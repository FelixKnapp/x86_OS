#ifndef _KERNEL_VIDEO_H_
#define _KERNEL_VIDEO_H_

#include <stdint.h>

enum color {
  BLACK = 0,
  BLUE = 1,
  GREEN = 2,
  CYAN = 3,
  RED = 4,
  MAGENTA = 5,
  BROWN = 6,
  LIGHT_GREY = 7,
  GREY = 8,
  LIGHT_BLUE = 9,
  LIGHT_GREEN = 10,
  LIGHT_CYAN = 11,
  LIGHT_RED = 12,
  LIGHT_MAGENTA = 13,
  LIGHT_BROWN = 14,
  WHITE = 15,
};

void initTerminal();

uint8_t setTerminalColor(enum color fgColor, enum color bgColor);

enum color getTerminalFgColor();

enum color getTerminalBgColor();

uint8_t putCharAt(char x, char y, char Char, enum color fgColor, enum color bgColor);

uint8_t printChar(char Char);

uint8_t setPrinter(uint8_t x, uint8_t y);

uint8_t getPrinterX();

uint8_t getPrinterY();

#endif
