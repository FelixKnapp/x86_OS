#include "kernel.video.h"
#include "kernel.mem.h"

void init();

extern void main() {
  init();
  printChar('H');
  printChar('e');
  printChar('l');
  setTerminalColor(BLACK, WHITE);
  printChar('l');
  printChar('o');
  printChar('!');

  setPrinter(0, 2);

  for(int i = 0; i < 100; i++){
    setTerminalColor(i%16, (i+1)%16);
    printChar('a');
    printChar('s');
    printChar('d');
    printChar('f');
  }

  volatile uint8_t* test = memalloc(256);

  setTerminalColor(WHITE, BLACK);
  if(test) printChar('X');
  else printChar('O');

  volatile uint8_t* test2 = memalloc(256);

  if(test2) printChar('X');
  else printChar('O');

  volatile uint8_t* test3 = memalloc(256);

  if(test3) printChar('X');
  else printChar('O');

  free(test, 256);

  volatile uint8_t* test4 = memalloc(256);

  if(test4) printChar('X');
  else printChar('O');

  free(test2, 256);
  free(test3, 256);
  free(test4, 256);

  volatile uint8_t* terminalColor = memalloc(1);

  *terminalColor = getTerminalFgColor();

  setTerminalColor(BLUE, WHITE);
  setPrinter(0, getPrinterY() + 1);
  printChar(*terminalColor + 65);

  return;
}

void init(){
  clearMem();
  initTerminal();
}

