GCC= g++
FLAGS = -g -Wall
DEPS = player.o game.o


all: main



main: main.cpp $(DEPS)
	$(GCC) $(FLAGS) -o game.out main.cpp $(DEPS)


player.o: player.cpp player.h
	$(GCC) $(FLAGS) -c player.cpp

game.o: game.cpp game.h player.h 
	$(GCC) $(FLAGS) -c game.cpp

clean:
	rm player.o game.out game.o
