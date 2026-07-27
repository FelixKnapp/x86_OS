#include "kernel.video.h"
#include "kernel.mem.h"
#include "kernel.interrupts.h"
#include "kernel.keyboard_driver.h"

void init();
extern void enableInterrupts();

extern void main() {
  init();

  setTerminalColor(LIGHT_BROWN, BLACK);
  printChar('x');
  printChar('8');
  printChar('6');

  while(1);

  return;
}

void init(){
  clearMem();
  initTerminal();
  initIdt();
  initKeyboard();
  enableInterrupts();
}

