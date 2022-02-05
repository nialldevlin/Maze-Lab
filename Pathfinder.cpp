#include "Pathfinder.h"
#include "coord.h"
#include "node.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>

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
	//maze[0][0][0] = 1;
	//maze[num_grids - 1][grid_size - 1][grid_size - 1] = 1;
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
	vector<int> final_pos{num_grids - 1, grid_size - 1, grid_size - 1};
	cout << (*maze)[curr_pos->getz() - 1][curr_pos->gety()][curr_pos->getx()][0] << endl;
	return solved;
}

/*
//Private functions
bool Pathfinder::up(Coord * pos) {
	if (pos->getz() - 1 >= 0 && *maze[pos->getz() - 1][pos->gety()][pos->getx()] == true) {
		pos->decz();
		return true;
	}
	return false;
}

bool Pathfinder::down(Coord * pos) {
	if (pos->getz() + 1 < num_grids && *maze[pos->getz() + 1][pos->gety()][pos->getx()] == true) {
		pos->incz();
		return true;
	}
	return false;
}

bool Pathfinder::forward(Coord * pos) {
	if (pos->gety() - 1 >= 0 && *maze[pos->getz()][pos->gety() - 1][pos->getx()] == true) {
		pos->decy();
		return true;
	}
	return false;
}

bool Pathfinder::backward(Coord * pos) {
	if (pos->gety() + 1 < grid_size && *maze[pos->getz()][pos->gety() + 1][pos->getx()] == true) {
		pos->incy();
		return true;
	}
	return false;
}

bool Pathfinder::left(Coord * pos) {
	if (pos->getx() - 1 >= 0 && *maze[pos->getz()][pos->gety()][pos->getx() - 1] == true) {
		pos->decx();
		return true;
	}
	return false;
}

bool Pathfinder::right(Coord * pos) {
	if (pos->getx() + 1 < 5 && *maze[pos->getz()][pos->gety()][pos->getx() + 1] == true) {
		pos->incx();
		return true;
	}
	return false;
}
*/