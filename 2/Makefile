TARGET = program

all: run

build:
	g++ main.cpp CComplexVector.cpp CComplexVector0.cpp CComplexVector1.cpp CCVFactory.cpp CCVTests.cpp -o program -O3 -march=native -fopenmp -ffast-math

run: build
	clear
	@./program

test: build
	clear
	@./program --test

OMP: build
	clear
	@./program --OMPtest

.PHONY: all run build test
