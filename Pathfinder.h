#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "PathfinderInterface.h"
#include "coord.h"
#include "node.h"
#include <vector>
#include <set>

using namespace std;

class Pathfinder: public PathfinderInterface {
private:
	const static short num_grids = 5;
	const static short grid_size = 5;
	vector<vector<vector<bool>>> * maze;
	vector<Coord> solved;
	set<Node> visited; //Seen nodes
	set<Node> to_visit; //Nodes to visit
	Coord * curr_pos;
	
	bool up(Node * pos);
	bool down(Node * pos);
	bool forward(Node * pos);
	bool backward(Node * pos);
	bool left(Node * pos);
	bool right(Node * pos);

	float findG(Node n);
	float findH(Node n);
	float findF(Node n);

	void expandNode(Node n, bool (Pathfinder::*direction)(Node*));
	vector<string> findPath(Node current);

public:
	Pathfinder();
	~Pathfinder();
	string toString() const;
	void createRandomMaze();
	bool importMaze(string file_name);
	vector<string> solveMaze();
};

#endif