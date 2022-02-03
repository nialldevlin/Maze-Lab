#include "PathfinderInterface.h"

class Maze: public PathfinderInterface {
private:
	short num_grids = 5;
	short grid_size = 5;
	bool maze[num_grids][grid_size][grid_size];
	bool maze_gen = false;
public:
	Maze();
	virtual ~Maze();
	string toString() const;
	void createRandomMaze();
	bool importMaze(string file_name);
	vector<string> solveMaze();
}