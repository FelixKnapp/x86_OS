#ifndef _KERNEL_KEYBOARD_DRIVER_H_
#define _KERNEL_KEYBOARD_DRIVER_H_

void initKeyboard();

void handleKeyboardInterrupt();

void addKeyboardInterruptToIdt();

#endif

