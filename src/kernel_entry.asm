global _start
global loadIdt
global keyboardHandler
global ioIn
global ioOut
global enableInterrupts
extern handleKeyboardInterrupt

_start:

section .text
  [bits 32]
  [extern main]
  call main
  jmp $

loadIdt:
  mov edx, [esp + 4]
  lidt [edx]
  ret

enableInterrupts:
  sti
  ret

keyboardHandler:
  pushad
  cld
  call handleKeyboardInterrupt
  popad
  iretd

ioIn:
  mov edx, [esp + 4]
  mov eax, 0x0
  in al, dx
  ret

ioOut:
  mov edx, [esp + 4]
  mov eax, [esp + 8]
  out dx, al
  ret

