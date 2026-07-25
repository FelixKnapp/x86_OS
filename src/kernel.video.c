#include "kernel.video.h"
#include "kernel.mem.h"
#include <stdint.h>

#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80

uint16_t* const screenBuffer = (uint16_t*)0xb8000;
volatile uint8_t* terminal_fg_color;
volatile uint8_t* terminal_bg_color;
volatile uint8_t* printer_x;
volatile uint8_t* printer_y;

void initTerminal(){
  terminal_fg_color = memalloc(1);  *terminal_fg_color = WHITE;
  terminal_bg_color = memalloc(1);  *terminal_bg_color = BLACK;
  printer_x = memalloc(1);
  printer_y = memalloc(1);
}

uint8_t setTerminalColor(enum color fgColor, enum color bgColor){
  if(!(fgColor <= 15 && fgColor >= 0) && !(bgColor <= 15 && bgColor >= 0)) return 1;

  *terminal_fg_color = fgColor;
  *terminal_bg_color = bgColor;
  return 0;
}

enum color getTerminalFgColor(){
  return *terminal_fg_color;
}

enum color getTerminalBgColor(){
  return *terminal_bg_color;
}

uint8_t putCharAt(char x, char y, char Char, enum color fgColor, enum color bgColor) {
  if(x >= SCREEN_WIDTH) return 1;
  if(y >= SCREEN_HEIGHT) return 2;
  if(!(fgColor <= 15 && fgColor >= 0) && !(bgColor <= 15 && bgColor >= 0)) return 3;

  *(screenBuffer + x + y * SCREEN_WIDTH) = (uint16_t)Char | (uint16_t)(fgColor | bgColor << 4) << 8;
  return 0;
}

uint8_t printChar(char Char){
  putCharAt(*printer_x, *printer_y, Char, *terminal_fg_color, *terminal_bg_color);

  (*printer_x) ++;
  if(*printer_x >= SCREEN_WIDTH) {
    *printer_x = 0;
    (*printer_y) ++;
  }

  // WARN: no protection / scrolling if printer goes off screen

  return 0;
}

uint8_t setPrinter(uint8_t x, uint8_t y) {
  if(x >= SCREEN_WIDTH) return 1;
  if(y >= SCREEN_HEIGHT) return 0;

  *printer_x = x;
  *printer_y = y;
}

uint8_t getPrinterX() {
  return *printer_x;
}

uint8_t getPrinterY() {
  return *printer_y;
}

