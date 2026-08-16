#ifndef _KERNEL_KEYBOARD_DRIVER_H_
#define _KERNEL_KEYBOARD_DRIVER_H_

#include <stdint.h>

#define KEY_PRESSED_ARRAY_SIZE 32

extern int8_t* pressed_keys;
extern int8_t last_key_pressed;

void initKeyboard();

void handleKeyboardInterrupt();

void addKeyboardInterruptToIdt();

#endif

