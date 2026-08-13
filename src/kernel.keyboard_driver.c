#include "kernel.keyboard_driver.h"
#include "keymap.h"
#include "kernel.interrupts.h"
#include "kernel.video.h" // NOTE: TEMPORARY
#include <stdint.h>

extern void keyboardHandler();
extern int8_t ioIn(uint16_t port);
extern void ioOut(uint16_t port, uint8_t data);

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
  uint8_t status = ioIn(KEYBOARD_STATUS_PORT);

  if(status & 0x1) {
    int8_t scancode = ioIn(KEYBOARD_DATA_PORT);
    setTerminalColor(WHITE, BLACK);
    if(!(scancode & 0x80)) {
      if(scancode < 128 && scancode != 0)
        printChar(kbd_US[scancode]); // NOTE: Temporary, add real driver here (should tell os what key was pressed and what is currently pressed), also no current implementation for special keys like alt, host, arrow keys, etc.
    }
  }

  ioOut(PIC1_COMMAND_PORT, 0x20);
}

void addKeyboardInterruptToIdt(){
  uint32_t offset = (uint32_t)keyboardHandler;
  idt[0x21].offsetLower = offset & 0x0000ffff;
  idt[0x21].offsetUpper = (offset & 0xffff0000) >> 16;
  idt[0x21].selector = CODE_SEGMENT_OFFSET;
  idt[0x21].zero = 0x0;
  idt[0x21].typeAttribute = IDT_INTERRUPT_GATE;
}

