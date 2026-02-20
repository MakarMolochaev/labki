BUILD_DIR = build
TARGET = program
CMAKE = cmake
MAKE = make

all: run

run:
	g++ main.cpp CComplexVector.cpp CCVTests.cpp -o program -O3
	./program

.PHONY: all run