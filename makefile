maze: main.o Pathfinder.o
	g++ -o maze main.o Pathfinder.o

main: main.cpp
	g++ -o main.o main.cpp
	
pathfinder: Pathfinder.cpp Pathfinder.h PathfinderInterface.h
	g++ -o Pathfinder.o Pathfinder.cpp
