all: build/counter_4.o build/test_bench.o build/full_adder_1.o build/test_bench

build:
	mkdir -p build

build/counter_4.o: build counter_4.vhdl
	ghdl analyze --workdir=build -fsynopsys counter_4.vhdl

build/full_adder_1.o: build full_adder_1.vhdl
	ghdl analyze --workdir=build -fsynopsys full_adder_1.vhdl

build/test_bench.o: build test_bench.vhdl build/counter_4.o build/full_adder_1.o
	ghdl analyze --workdir=build -fsynopsys test_bench.vhdl

build/test_bench: build/counter_4.o build/full_adder_1.o build/test_bench.o
	ghdl elaborate --workdir=build -fsynopsys -o build/test_bench test_bench 

.PHONY: all clean

clean:
	rm -r build
