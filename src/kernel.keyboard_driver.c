#include "kernel.keyboard_driver.h"
#include "keymap.h"
#include "kernel.interrupts.h"
#include "kernel.video.h" // NOTE: TEMPORARY

extern void keyboardHandler();
extern int8_t ioIn(unsigned short port);
extern void ioOut(unsigned short port, unsigned char data);

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

void initKeyboard() {
  // unmask keyboard Interrypt
  ioOut(PIC1_DATA_PORT, 0b11111101);
}

void handleKeyboardInterrupt(){
  unsigned char status = ioIn(KEYBOARD_STATUS_PORT);

  if(status & 0x1) {
    char scancode = ioIn(KEYBOARD_DATA_PORT);
    setTerminalColor(WHITE, BLACK);
    if(!(scancode & 0x80)) {
      if(scancode < 128 && scancode != 0)
        printChar(kbd_US[scancode]); // NOTE: Temporary, add real driver here (should tell os what key was pressed and what is currently pressed), also no current implementation for special keys like alt, host, arrow keys, etc.
    }
  }

  ioOut(PIC1_COMMAND_PORT, 0x20);
}

void addKeyboardInterruptToIdt(){
  unsigned int offset = (unsigned int)keyboardHandler;
  idt[0x21].offsetLower = offset & 0x0000ffff;
  idt[0x21].offsetUpper = (offset & 0xffff0000) >> 16;
  idt[0x21].selector = CODE_SEGMENT_OFFSET;
  idt[0x21].zero = 0x0;
  idt[0x21].typeAttribute = IDT_INTERRUPT_GATE;
}

