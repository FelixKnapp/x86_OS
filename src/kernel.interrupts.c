#include "kernel.interrupts.h"
#include "kernel.keyboard_driver.h"

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1

extern int8_t ioIn(unsigned short port);
extern void ioOut(unsigned short port, unsigned char data);
extern void loadIdt(struct idt_pointer* idtAddress);

struct idt_entry idt[IDT_SIZE];

void initIdt() {

  addKeyboardInterruptToIdt();

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

