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

.PHONY: clean
clean:
	@echo [info] remove the generated file......
	rm -f ./obj/emulator


