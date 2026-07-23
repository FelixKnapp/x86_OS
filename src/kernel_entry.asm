global _start

_start:

section .text
  [bits 32]
  [extern main]
  call main
  jmp $

