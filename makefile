maze: main.o Pathfinder.o node.o coord.o
	g++ -o maze main.o Pathfinder.o node.o coord.o

main: main.cpp
	g++ -o main.o main.cpp

node: node.cpp node.h
	g++ -o node.o node.cpp

coord: coord.cpp coord.h
	g++ -o coord.o coord.cpp
	
pathfinder: Pathfinder.cpp Pathfinder.h PathfinderInterface.h
	g++ -o Pathfinder.o Pathfinder.cpp
