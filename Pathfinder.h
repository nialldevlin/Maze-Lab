#include "PathfinderInterface.h"

class Pathfinder: public PathfinderInterface {
private:
	const static short num_grids = 5;
	const static short grid_size = 5;
	bool maze[num_grids][grid_size][grid_size];
	bool maze_gen = false;

	bool up(int *pos);
	bool down(int *pos);
	bool forward(int *pos);
	bool backward(int *pos);
	bool left(int *pos);
	bool right(int *pos);
public:
	Pathfinder();
	~Pathfinder(){}
	string toString() const;
	void createRandomMaze();
	bool importMaze(string file_name);
	vector<string> solveMaze();
};
