main: main.cpp PathfinderInterface.h
	g++ -o main main.cpp

maze: maze.cpp maze.h PathfinderInterface.h
	g++ -o maze.o maze.cpp
