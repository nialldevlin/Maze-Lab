#ifndef PATHFINDER_H
#define PATHFINDER_H

#define NUM_GRIDS 5
#define GRID_SIZE 5

#include "PathfinderInterface.h"
#include "coord.h"
#include "node.h"
#include <vector>
#include <set>
#include <queue>

using namespace std;

class Pathfinder: public PathfinderInterface {
private:
	vector<vector<vector<bool>>> * maze;
	deque<Node> current_path;   //Current string of nodes
	vector<Node> bad_nodes;    //Nodes that don't lead anywhere
	const static Coord finalPos;
	const static Coord startPos;
    Node *current;

	bool up(Node * pos, set<Node> *n);
	bool down(Node * pos, set<Node> *n);
	bool forwd(Node * pos, set<Node> *n);
	bool backward(Node * pos, set<Node> *n);
	bool left(Node * pos, set<Node> *n);
	bool right(Node * pos, set<Node> *n);

	bool inPath(Coord n);
	bool badNode(Node n);
	vector<string> findPath();
	string toString(vector<vector<vector<short>>> m) const;
	string result();

	void clear();

public:
	Pathfinder();
	~Pathfinder();
	string toString() const;
	void createRandomMaze();
	bool importMaze(string file_name);
	vector<string> solveMaze();
};

#endif
