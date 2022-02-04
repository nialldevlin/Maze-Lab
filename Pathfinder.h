#include "PathfinderInterface.h"

class Pathfinder: public PathfinderInterface {
private:
	const static short num_grids = 5;
	const static short grid_size = 5;
	bool maze[num_grids][grid_size][grid_size];
	bool maze_gen = false;
public:
	Pathfinder();
	~Pathfinder(){}
	string toString() const;
	void createRandomMaze();
	bool importMaze(string file_name);
	vector<string> solveMaze();
};
