.PHONY: all test clean

all: linux-run-test linux-run-test-bin

linux-run-test: linux-run.h linux-run.cpp linux-run-test.cpp
	g++ linux-run.cpp linux-run-test.cpp -o linux-run-test

linux-run-test-bin: linux-run-test-bin.cpp
	g++ linux-run-test-bin.cpp -o linux-run-test-bin


test: linux-run-test linux-run-test-bin
	./linux-run-test

clean:
	rm linux-run-test linux-run-test-bin
