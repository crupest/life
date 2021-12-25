build/cpu.o: build
	ghdl analyze --std=08 --workdir=build -fsynopsys cpu.vhdl

all: build/test_bench

build:
	mkdir -p build

build/adder_1.o: build adder_1.vhdl
	ghdl analyze --std=08 --workdir=build -fsynopsys adder_1.vhdl

build/adder_8.o: build adder_8.vhdl
	ghdl analyze --std=08 --workdir=build -fsynopsys adder_8.vhdl

build/adder_32.o: build adder_32.vhdl
	ghdl analyze --std=08 --workdir=build -fsynopsys adder_32.vhdl

build/alu.o: build alu.vhdl
	ghdl analyze --std=08 --workdir=build -fsynopsys alu.vhdl

build/counter_4.o: build counter_4.vhdl
	ghdl analyze --std=08 --workdir=build -fsynopsys counter_4.vhdl

build/full_adder_1.o: build full_adder_1.vhdl
	ghdl analyze --std=08 --workdir=build -fsynopsys full_adder_1.vhdl

build/multiplexer_1_2.o: build multiplexer_1_2.vhdl
	ghdl analyze --std=08 --workdir=build -fsynopsys multiplexer_1_2.vhdl

build/multiplexer_8_2.o: build multiplexer_8_2.vhdl
	ghdl analyze --std=08 --workdir=build -fsynopsys multiplexer_8_2.vhdl

build/multiplexer_32_2.o: build multiplexer_32_2.vhdl
	ghdl analyze --std=08 --workdir=build -fsynopsys multiplexer_32_2.vhdl

build/shift_32.o: build shift_32.vhdl
	ghdl analyze --std=08 --workdir=build -fsynopsys shift_32.vhdl

build/test_bench.o: build test_bench.vhdl build/counter_4.o build/full_adder_1.o build/multiplexer_1_2.o build/multiplexer_8_2.o build/multiplexer_32_2.o build/adder_1.o build/adder_8.o build/adder_32.o build/shift_32.o build/alu.o
	ghdl analyze --std=08 --workdir=build -fsynopsys test_bench.vhdl

build/test_bench: build/test_bench.o
	ghdl elaborate --std=08 --workdir=build -fsynopsys -o build/test_bench test_bench 

.PHONY: all clean

clean:
	rm -r build
