.PHONY: build run all dirs boot link

SRC_KERNEL_MODULES := $(wildcard src/kernel.*.c)
O_KERNEL_MODULES := $(patsubst src/%.c,temp/%.o,$(SRC_KERNEL_MODULES))

build: dirs boot $(O_KERNEL_MODULES) link

dirs:
	@mkdir -p temp build

boot:
	@nasm "src/boot.asm" -f bin -o "temp/boot.bin"
	@nasm "src/kernel_entry.asm" -f elf -o "temp/kernel_entry.o"

temp/%.o: src/%.c
	@i386-elf-gcc -ffreestanding -m32 -g -c $< -o $@

link:
	@i386-elf-ld -o "temp/full_kernel.bin" -Ttext 0x1000 "temp/kernel_entry.o" $(O_KERNEL_MODULES) --oformat binary
	@cat "temp/boot.bin" "temp/full_kernel.bin" >"build/OS.bin"

run:
	@qemu-system-x86_64 -hda "build/OS.bin" -m 128M

all: build run
