maze: main.o Pathfinder.o
	g++ -o maze main.o Pathfinder.o

node: node.cpp node.h
	g++ -o node.o node.cpp

coord: coord.cpp coord.h
	g++ -o coord.o coord.cpp

main: main.cpp
	g++ -o main.o main.cpp
	
pathfinder: Pathfinder.cpp Pathfinder.h PathfinderInterface.h
	g++ -o Pathfinder.o Pathfinder.cpp
