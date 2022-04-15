CC = g++
OPT := -std=c++11 -g
SRC := $(shell find . -maxdepth 1 -name "*.cpp" )
TGT := ./obj/emulator
PROGRAM := ./src/main/resource/program.asm

.default: all

all: $(TGT)

$(TGT): $(SRC)
	mkdir -p obj
	$(CC) -o $@ $^ $(OPT)

tt: translate test

test:
	@echo [info] start the CPU test.......
	mill chiselModule.test.runMain aias_lab7.Hw1.topTest -tbn verilator

.PHONY: translate
translate:
	@echo [info] first execute $(PROGRAM) by emulator
	@echo [info] then translate $(PROGRAM) to the machine code
	@./obj/emulator $(PROGRAM)

migrate:
	@bash migrate.sh

validate:
	@./obj/emulator ./src/main/resource/Hw1_inst.asm
	@diff -q ./src/main/resource/Hw1_m_code.hex ./src/main/resource/m_code.hex
	@diff -s ./src/main/resource/Hw1_m_code.hex ./src/main/resource/m_code.hex

.PHONY: clean
clean:
	@echo [info] remove the generated file......
	rm -f ./obj/emulator


