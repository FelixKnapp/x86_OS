#ifndef _KERNEL_INTERRUPTS_H_
#define _KERNEL_INTERRUPTS_H_

#include <stdint.h>
#define IDT_SIZE 256
#define CODE_SEGMENT_OFFSET 0x8
#define IDT_INTERRUPT_GATE 0x8e

struct idt_pointer {
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));

struct idt_entry {
  unsigned short offsetLower;
  unsigned short selector;
  unsigned char zero;
  unsigned char typeAttribute;
  unsigned short offsetUpper;
} __attribute__((packed));

extern struct idt_entry idt[IDT_SIZE];

void initIdt();

#endif

