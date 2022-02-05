#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "PathfinderInterface.h"
#include "coord.h"
#include "node.h"
#include <vector>

using namespace std;

class Pathfinder: public PathfinderInterface {
private:
	const static short num_grids = 5;
	const static short grid_size = 5;
	vector<vector<vector<bool>>> * maze;
	vector<string> solved;
	Coord * curr_pos;
	
	bool up(Coord * pos);
	bool down(Coord * pos);
	bool forward(Coord * pos);
	bool backward(Coord * pos);
	bool left(Coord * pos);
	bool right(Coord * pos);
public:
	Pathfinder();
	~Pathfinder();
	string toString() const;
	void createRandomMaze();
	bool importMaze(string file_name);
	vector<string> solveMaze();
};

#endif