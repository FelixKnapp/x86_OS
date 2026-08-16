#include "kernel.video.h"
#include "kernel.mem.h"
#include "kernel.interrupts.h"
#include "kernel.keyboard_driver.h"
#include "kernel.utils.h"

void init();
extern void enableInterrupts();

extern void main() {
  init();

  setTerminalColor(LIGHT_BROWN, BLACK);
  printChar('x');
  printChar('8');
  printChar('6');

  char past_last_key_pressed = 0;

  setTerminalColor(LIGHT_GREEN, GREY);
  setPrinter(0, 2);

  while(1) {
    if(past_last_key_pressed != last_key_pressed) {
      if(last_key_pressed && last_key_pressed >= 32 && last_key_pressed <= 126)
        if((doesArrayContainByte(pressed_keys, KEY_PRESSED_ARRAY_SIZE, 0xC1) || doesArrayContainByte(pressed_keys, KEY_PRESSED_ARRAY_SIZE, 0xC2)) && last_key_pressed >= 97 && last_key_pressed <= 122)
          printChar(last_key_pressed - 32);
        else
          printChar(last_key_pressed);

      if(last_key_pressed == '\n')
        setPrinter(0, getPrinterY() + 1);

      past_last_key_pressed = last_key_pressed;
    }
  }

  return;
}

void init(){
  clearMem();
  initTerminal();
  initIdt();
  initKeyboard();
  enableInterrupts();
}

