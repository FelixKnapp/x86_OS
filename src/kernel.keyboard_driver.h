#ifndef _KERNEL_KEYBOARD_DRIVER_H_
#define _KERNEL_KEYBOARD_DRIVER_H_

#include <stdint.h>

extern char key_pressed;
extern uint8_t key_flags; // bit 0 = shift, bit 1 = strg, bit 2 = host, bit 4 = alt

void update();

void initKeyboard();

void handleKeyboardInterrupt();

void addKeyboardInterruptToIdt();

#endif

