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
	vector<vector<vector<bool>>> maze(5, vector<vector<bool>>(grid_size, vector<bool>(grid_size, value)));
	vector<string> solved;
	Coord curr_pos;

	bool up(int *pos);
	bool down(int *pos);
	bool forward(int *pos);
	bool backward(int *pos);
	bool left(int *pos);
	bool right(int *pos);
public:
	Pathfinder();
	~Pathfinder();
	string toString() const;
	void createRandomMaze();
	bool importMaze(string file_name);
	vector<string> solveMaze();
};

#endif