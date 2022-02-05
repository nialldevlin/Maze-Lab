#include "Pathfinder.h"
#include "coord.h"
#include "node.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <set>
#include <algorithm>

using namespace std;

Pathfinder::Pathfinder() {
	maze = new vector<vector<vector<bool>>> (num_grids, vector<vector<bool>>(grid_size, vector<bool>(grid_size, 1)));
	curr_pos = new Coord();
	srand(time(NULL));
}

Pathfinder::~Pathfinder() {
	delete maze;
	delete curr_pos;
}

string Pathfinder::toString() const {
	string outstr = "";
	for (auto grid : *maze) {
		for (auto line : grid) {
			for (auto i : line) {
				outstr += i;
				outstr += " ";
			}
			outstr += "\n";
		}
		outstr += "\n";
	}
	return outstr;
}

void Pathfinder::createRandomMaze() {
	for (auto& grid : *maze) {
		for (auto line : grid) {
			for (auto i : line) {
				int random = rand();
				i = random % 2;
			}
		}
	}
	(*maze)[0][0][0] = 1;
	(*maze)[num_grids - 1][grid_size - 1][grid_size - 1] = 1;
}

bool Pathfinder::importMaze(string file_name) {
	ifstream ifs;
	ifs.open(file_name);
	if (!ifs.is_open()) {
		return false;
	}

	string line;
	vector<bool> vals;
	int ones = 0;
	int zeroes = 0;
	while (ifs >> line) {
		stringstream ss(line);
		bool val;
		while(ss >> val) {
			vals.push_back(val);
			if (val)
				zeroes++;
			else
				ones++;
		}
	}
	if (vals.size() < num_grids * grid_size * grid_size) {
		return false;
	}
	int index = 0;
	for (auto& grid : *maze) {
		for (auto line : grid) {
			for (auto i : line) {
				i = vals[index];
				index++;
			}
		}
	}
	return true;
}

vector<string> Pathfinder::solveMaze() {
	//A*
	Coord finalPos(num_grids - 1, grid_size - 1, grid_size - 1); //Goal position
	curr_pos.set(0, 0, 0);
	Node first(curr_pos); //Initialize first node to start
	float g_1 = g(first);	//Initialize cost functions for first node
	float h_1 = h(first);
	float f_1 = f(first);
	first.setg(g_1);
	first.seth(h_1);
	first.setf(f_1);
	to_visit.insert(first); //Add first node to list to visit

	Node current;
	while (to_visit.size() > 0) {
		//Find element on visit list with lowest f value
		current = std::min_element( to_visit.begin(), to_visit.end(),
                             []( const Node &a, const Node &b )
                             {
                                 return a.getf(); < b.getf();
                             } );

		to_visit.erase(current)
		visited.insert(current);

		if (current.getPos() == finalPos) {
			return 
		}

		//Expand visit list to all neighbors
		expandNode(current, &up);
		expandNode(current, &down);
		expandNode(current, &forward);
		expandNode(current, &backward);
		expandNode(current, &left);
		expandNode(current, &right);
	}

	return solved_string;
}

//Private functions
vector<string> Pathfinder::findPath(Node current) {
	vector<string> path;
	Node curr = current;
	while (curr != NULL) {
		path.push_back(current.getPos().str());
		curr = curr.getParent();
	}
	reverse(path.begin(), path.end());
	return path;
}

void Pathfinder::expandNode(Node n, bool (*direction)(Coord*)) {
	Node new_n = n;
	if (direction(new_n) && visited.find(new_n) == visited.end()) {
		new_n.setParent(n)
		float g = g(new_n);	//Initialize cost functions for node
		float h = h(new_n);
		float f = f(new_n);
		new_n.setg(g);
		new_n.seth(h);
		new_n.setf(f);
		to_visit.insert(new_n);
	}  
}

int Pathfinder::g(Node n) {
	if (n.getParent()) {
		return n.getParent().getg() + 1;
	}
	return 0;
}

int Pathfinder::h(Node n) {
	Coord finalPos(num_grids - 1, grid_size - 1, grid_size - 1);
	return n.getPos().getDist(finalPos);
}

int Pathfinder::f(Node n) {
	return g(n) + h(n);
}

bool Pathfinder::up(Coord * pos) {
	if (pos->getz() - 1 >= 0 && (*maze)[pos->getz() - 1][pos->gety()][pos->getx()] == 1) {
		pos->decz();
		return true;
	}
	return false;
}

bool Pathfinder::down(Coord * pos) {
	if (pos->getz() + 1 < num_grids && (*maze)[pos->getz() + 1][pos->gety()][pos->getx()] == 1) {
		pos->incz();
		return true;
	}
	return false;
}

bool Pathfinder::forward(Coord * pos) {
	if (pos->gety() - 1 >= 0 && (*maze)[pos->getz()][pos->gety() - 1][pos->getx()] == 1) {
		pos->decy();
		return true;
	}
	return false;
}

bool Pathfinder::backward(Coord * pos) {
	if (pos->gety() + 1 < grid_size && (*maze)[pos->getz()][pos->gety() + 1][pos->getx()] == 1) {
		pos->incy();
		return true;
	}
	return false;
}

bool Pathfinder::left(Coord * pos) {
	if (pos->getx() - 1 >= 0 && (*maze)[pos->getz()][pos->gety()][pos->getx() - 1] == 1) {
		pos->decx();
		return true;
	}
	return false;
}

bool Pathfinder::right(Coord * pos) {
	if (pos->getx() + 1 < 5 && (*maze)[pos->getz()][pos->gety()][pos->getx() + 1] == 1) {
		pos->incx();
		return true;
	}
	return false;
}
