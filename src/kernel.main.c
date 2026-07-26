#include "kernel.video.h"
#include "kernel.mem.h"

void init();
void initIdt();
void initKeyboard();
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

#define IDT_SIZE 256
#define CODE_SEGMENT_OFFSET 0x8
#define IDT_INTERRUPT_GATE 0x8e
#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#include "keymap.h"

struct idt_pointer {
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));

extern void keyboardHandler();
extern int8_t ioIn(unsigned short port);
extern void ioOut(unsigned short port, unsigned char data);
extern void loadIdt(struct idt_pointer* idtAddress);

struct idt_entry {
  unsigned short offsetLower;
  unsigned short selector;
  unsigned char zero;
  unsigned char typeAttribute;
  unsigned short offsetUpper;
} __attribute__((packed));

struct idt_entry idt[IDT_SIZE];

void initIdt() {
  // add Keyboard IDT Entry to IDT Table
  unsigned int offset = (unsigned int)keyboardHandler;
  idt[0x21].offsetLower = offset & 0x0000ffff;
  idt[0x21].offsetUpper = (offset & 0xffff0000) >> 16;
  idt[0x21].selector = CODE_SEGMENT_OFFSET;
  idt[0x21].zero = 0x0;
  idt[0x21].typeAttribute = IDT_INTERRUPT_GATE;

  // send ICW(Initialization Command Words)
  ioOut(PIC1_COMMAND_PORT, 0x11);
  ioOut(PIC2_COMMAND_PORT, 0x11);
  ioOut(PIC1_DATA_PORT, 0x20);
  ioOut(PIC2_DATA_PORT, 0x28);
  ioOut(PIC1_DATA_PORT, 0x0);
  ioOut(PIC2_DATA_PORT, 0x0);
  ioOut(PIC1_DATA_PORT, 0x1);
  ioOut(PIC2_DATA_PORT, 0x1);

  // mask out all interrupts
  ioOut(PIC1_DATA_PORT, 0xff);
  ioOut(PIC2_DATA_PORT, 0xff);
  
  // create IDT pointer to IDT Table
  struct idt_pointer idtPointer;
  idtPointer.limit = 64 * IDT_SIZE - 1;
  idtPointer.base = (unsigned int)&idt;
  loadIdt(&idtPointer);
}

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
        printChar(kbd_US[scancode]);
    }
  }

  ioOut(PIC1_COMMAND_PORT, 0x20);
}

