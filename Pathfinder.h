#include "PathfinderInterface.h"
#include <vector>

using namespace std;

class Pathfinder: public PathfinderInterface {
private:
	const static short num_grids = 5;
	const static short grid_size = 5;
	vectorvector<vector<bool>>> maze;
	vector<string> solved;
	vector<int> curr_pos(3, 0);

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
