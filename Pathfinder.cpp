#include "Pathfinder.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

Pathfinder::Pathfinder() {
	maze = new vector(num_grids, vector<std::vector<bool>> (grid_size, vector<bool>(grid_size, 1)));
	srand(time(NULL));
}

Pathfinder::~Pathfinder() {
	delete maze;
}

string Pathfinder::toString() const {
	string outstr = "";
	for (int i = 0; i < num_grids; i++) {
		for (int j = 0; j < grid_size; j++) {
			for (int k = 0; k < grid_size; k++) {
				outstr += maze[i][j][k];
				outstr += " ";
			}
			outstr += "\n";
		}
		outstr += "\n";
	}
	return outstr;
}

void Pathfinder::createRandomMaze() {
	for (int i = 0; i < num_grids; i++) {
		for (int j = 0; j < grid_size; j++) {
			for (int k = 0; k < grid_size; k++) {
				int random = rand();
				maze[i][j][k] = random % 2;
			}
		}
	}
	maze[0][0][0] = 1;
	maze[num_grids - 1][grid_size - 1][grid_size - 1] = 1;
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
	for (int i = 0; i < num_grids; i++) {
		for (int j = 0; j < grid_size; j++) {
			for (int k = 0; k < grid_size; k++) {
				maze[i][j][k] == vals[index];
				index++;
			}
		}
	}
	return true;
}

vector<string> Pathfinder::solveMaze() {
	vector<int> final_pos{num_grids - 1, grid_size - 1, grid_size - 1};
	
	if (curr_pos == final_pos) {
		return solved;
	}
}

//Private functions
bool Pathfinder::up(int *pos) {
	if ( pos[0] - 1 >= 0 && pos[0] - 1 < num_grids && maze[pos[0] - 1][pos[1]][pos[2]] == 1) {
		pos[0]--;
		return true;
	}
	return false;
}

bool Pathfinder::down(int *pos) {
	if ( pos[0] + 1 >= 0 && pos[0] + 1 < num_grids && maze[pos[0] + 1][pos[1]][pos[2]] == 1) {
		pos[0]++;
		return true;
	}
	return false;
}

bool Pathfinder::forward(int *pos) {
	if ( pos[1] - 1 >= 0 && pos[1] - 1 < num_grids && maze[pos[0]][pos[1] - 1][pos[2]] == 1) {
		pos[1]--;
		return true;
	}
	return false;
}

bool Pathfinder::backward(int *pos) {
	if ( pos[1] + 1 >= 0 && pos[1] + 1 < num_grids && maze[pos[0]][pos[1] + 1][pos[2]] == 1) {
		pos[1]++;
		return true;
	}
	return false;
}

bool Pathfinder::left(int *pos) {
	if ( pos[2] - 1 >= 0 && pos[2] - 1 < num_grids && maze[pos[0]][pos[1]][pos[2] - 1] == 1) {
		pos[2]--;
		return true;
	}
	return false;
}

bool Pathfinder::right(int *pos) {
	if ( pos[2] + 1 >= 0 && pos[2] + 1 < num_grids && maze[pos[0]][pos[1]][pos[2] + 1] == 1) {
		pos[2]++;
		return true;
	}
	return false;
}
