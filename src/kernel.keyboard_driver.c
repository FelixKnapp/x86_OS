#include "kernel.keyboard_driver.h"
#include "keymap.h"
#include "kernel.interrupts.h"
#include "kernel.mem.h"
#include "kernel.utils.h"
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

#define KEY_PRESSED_ARRAY_SIZE 32

int8_t* pressed_keys;
int8_t last_key_pressed;

void initKeyboard() {
  // unmask keyboard Interrypt
  ioOut(PIC1_DATA_PORT, 0b11111101);

  // setup keys
  pressed_keys = (int8_t*)memalloc(KEY_PRESSED_ARRAY_SIZE);
}

void handleKeyboardInterrupt(){
  uint8_t status = ioIn(KEYBOARD_STATUS_PORT);

  if(status & 0x1) {
    uint8_t scancode = ioIn(KEYBOARD_DATA_PORT);

    if(scancode < 0x80){
      if(!doesArrayContainByte(pressed_keys, KEY_PRESSED_ARRAY_SIZE, kbd_US[scancode])) {
        appendByteToArray(pressed_keys, KEY_PRESSED_ARRAY_SIZE, kbd_US[scancode]);
        last_key_pressed = kbd_US[scancode];
      }

    }else{
      scancode -= 0x80;

      if(doesArrayContainByte(pressed_keys, KEY_PRESSED_ARRAY_SIZE, kbd_US[scancode]))
        *(pressed_keys + getIndexOfByteFromArray(pressed_keys, KEY_PRESSED_ARRAY_SIZE, kbd_US[scancode])) = 0;
    
      if(kbd_US[scancode] == last_key_pressed) 
        last_key_pressed = 0;
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

