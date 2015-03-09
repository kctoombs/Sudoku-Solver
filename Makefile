# Makefile for CS 24 Project 1
#     Done: you do not need to change or submit it

# Usage:
#     Either "make" - compile/link gridtester
#     Or "make sudokusolver" - compile/link solver
#     Or "make clean" - remove all .o and executables

gridtester: gridtester.o gridio.o sudokugrid.o
	g++ -Wall -o gridtester gridtester.o gridio.o sudokugrid.o

sudokusolver: sudokusolver.o gridio.o sudokugrid.o
	g++ -Wall -o sudokusolver sudokusolver.o gridio.o sudokugrid.o

gridio.o: gridio.cpp
	g++ -Wall -c gridio.cpp

gridtester.o: gridtester.cpp
	g++ -Wall -c gridtester.cpp

sudokugrid.o: sudokugrid.cpp
	g++ -Wall -c sudokugrid.cpp

sudokusolver.o: sudokusolver.cpp
	g++ -Wall -c sudokusolver.cpp

clean:
	rm -f gridtester.o gridio.o sudokugrid.o sudokusolver.o
	rm -f gridtester
	rm -f sudokusolver
