SHELL = /bin/sh
FLAGS = -Wall
CC = g++

all: TwoPipesTwoChildren TwoPipesThreeChildren dynpipe

TwoPipesTwoChildren: TwoPipesTwoChildren.cpp
	$(CC) $(FLAGS) -g -o $@ TwoPipesTwoChildren.cpp

TwoPipesThreeChildren: TwoPipesThreeChildren.cpp
	$(CC) $(FLAGS) -g -o $@ TwoPipesThreeChildren.cpp

dynpipe: DynPipe.cpp
	$(CC) $(FLAGS) -g -o $@ DynPipe.cpp

clean:
	rm TwoPipesTwoChildren TwoPipesThreeChildren dynpipe
