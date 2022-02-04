#include "Pathfinder.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>

Pathfinder::Pathfinder() {
	for (auto &i : maze) {
		for (auto &j : i) {
			for (auto &k : j) {
				k = 1;
			}
		}
	}
	srand(time(null));
}

string Pathfinder::toString() const {
	string outstr = "";
	for (auto i : maze) {
		for (auto j : i) {
			for (auto k : j) {
				outstr += k;
				outstr += " ";
			}
			outstr += "\n";
		}
		outstr += "\n";
	}
	return outstr;
}

void Pathfinder::createRandomMaze() {
	for (auto &i : maze) {
		for (auto &j : i) {
			for (auto &k : j) {
				int random = rand();
				k = random % 2;
			}
		}
	}
	k[0][0][0] = 1;
	k[num_grids - 1][grid_size - 1][grid_size - 1] = 1;
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
				ones++
		}
	}
	if (vals.size() < num_grids * grid_size * grid_size) {
		return false;
	}
	int index = 0;
	for (int i = 0; i < num_grids; i++) {
		for (int j = 0; j < grid_size; j++) {
			for (int k = 0; k < grid_size; k++) {
				maze[i][j][k] == vals[index];
				index++;
			}
		}
	}
	return True;
}

vector<string> Pathfinder::solveMaze() {
	vector<string> solved;
	return solved;
}
