GCC=g++
FLAGS=-Wall
DEPS=kuhnpoker.cpp node.cpp node.h

all: node.o cfr.o
	$(GCC) $(FLAGS) kuhnpoker.cpp node.o cfr.o -o kuhnpoker

node.o: node.cpp node.h
	$(GCC) $(FLAGS) -c node.cpp

cfr.o: cfr.cpp cfr.h
	$(GCC) $(FLAGS) -c cfr.cpp

clean:
	rm kuhnpoker.o node.o utils.o cfr.o
