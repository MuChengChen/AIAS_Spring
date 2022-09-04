#/usr/bin/make

# Makefile for RV32 cross compilation and emulation

PROG = sudoku

.PHONY: all, compile, dump, info, run, clean

all: run
compile: $(PROG).elf
dump: $(PROG).dump
info: $(PROG).info

clean:
	-@rm -rfv $(PROG).elf $(PROG).dump $(PROG).info

run: $(PROG).elf
	qemu-system-riscv32 -nographic -machine virt -bios none -kernel $<

$(PROG).elf: boot.S sudoku_2x2_asm.S sudoku_2x2_c.c main.c
	riscv32-unknown-elf-gcc -nostartfiles -Tvirt.lds -o $@ $^

%.dump: %.elf
	riscv32-unknown-elf-objdump -d $< > $@

%.info: %.elf
	riscv32-unknown-elf-readelf -h $< > $@
