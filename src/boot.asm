[org 0x7c00]
KERNEL equ 0x1000
SECTORS equ 0x4
CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start

; safe boot disk
mov [BOOT_DISK], dl

; setup segments
xor ax, ax
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

; setup args for reading sector
mov bx, KERNEL        ; destination
mov ax, 0x0
mov es, ax            ; destination offset
mov ah, 0x02          ; idk, I guess means read or smht
mov al, SECTORS       ; how many sector
mov ch, 0x0           ; cylinder
mov cl, 0x2           ; sector
mov dh, 0x0           ; head
mov dl, [BOOT_DISK]   ; disk

; read
int 0x13

; check if smth went wrong
jc disk_error
cmp al, dl
jz disk_error

; text mode
mov ah, 0x0
mov al, 0x3
int 0x10

; switch to 32bit mode (ProtectedMode)
cli
lgdt [GDT_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax

; far jump
jmp CODE_SEG:start_pm

jmp $

BOOT_DISK: db 0

GDT_start:
    GDT_null: ; 16b 0x00
        dd 0x0
        dd 0x0

    GDT_code:
        dw 0xffff ; limit (first 16 bits)
        dw 0x0 ; base (24 bit)
        db 0x0
        db 0b10011010 ; pres, priv, type, type flags
        db 0b11001111 ; other flags, limt (last 4 bits)
        db 0x0

    GDT_data:
        dw 0xffff ; limit (first 16 bits)
        dw 0x0 ; base (24 bit)
        db 0x0
        db 0b10010010 ; pres, priv, type, type flags
        db 0b11001111 ; other flags, limt (last 4 bits)
        db 0x0

GDT_end:

GDT_descriptor:
    dw GDT_end - GDT_start - 1  ; size
    dd GDT_start                ; pointer / location

disk_error:
  mov ah, 0x0e
  mov al, 'D'
  int 0x10
  mov al, 'i'
  int 0x10
  mov al, 's'
  int 0x10
  mov al, 'k'
  int 0x10
  mov al, ' '
  int 0x10
  mov al, 'e'
  int 0x10
  mov al, 'r'
  int 0x10
  mov al, 'r'
  int 0x10
  mov al, 'o'
  int 0x10
  mov al, 'r'
  int 0x10
  mov al, '!'
  jmp $

[bits 32]
start_pm:
  ; setup segments
  mov ax, DATA_SEG
  mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
  ; 32 bit stack base pointer
	mov ebp, 0x90000
  mov esp, ebp

  ; jump to kernel
  jmp KERNEL

  jmp $

times 510-($-$$) db 0
dw 0xaa55

