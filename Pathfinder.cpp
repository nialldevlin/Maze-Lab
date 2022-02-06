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
	srand(time(NULL));
}

Pathfinder::~Pathfinder() {
	if (maze)
		delete maze;
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
				cout << "random maze" << endl;
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
	Node current; //Initialize current node to start
	current.setg(); //Initialize cost functions
	current.seth(finalPos);
	current.setf();
	to_visit.insert(current); //Add first node to list to visit

	int MAX_ITER = num_grids * grid_size * grid_size;
	int iter = 0;
	while (to_visit.size() > 0) {
		iter += 1;
		//Find element on visit list with lowest f value
		current = *to_visit.begin();

		to_visit.erase(current);
		visited.insert(current);
		if (*(current.getPos()) == finalPos) {
			return findPath(current);
		}

		if (iter > MAX_ITER) {
			return vector<string>();
		}

		//Expand visit list to all neighbors
		cout << "1" << endl;
		expandNode(current, &Pathfinder::up);
		cout << "2" << endl;
		expandNode(current, &Pathfinder::down);
		cout << "3" << endl;
		expandNode(current, &Pathfinder::forward);
		cout << "4" << endl;
		expandNode(current, &Pathfinder::backward);
		cout << "5" << endl;
		expandNode(current, &Pathfinder::left);
		cout << "6" << endl;
		expandNode(current, &Pathfinder::right);
		cout << "7" << endl;
	}
	return vector<string>;
}

//Private functions
vector<string> Pathfinder::findPath(Node current) {
	vector<string> path;
	Node * curr = &current;
	while (curr != nullptr) {
		path.push_back(curr->getPos()->str());
		curr = curr->getParent();
	}
	reverse(path.begin(), path.end());
	return path;
}

void Pathfinder::expandNode(Node n, bool (Pathfinder::*direction)(Node*)) {
	Coord finalPos(num_grids - 1, grid_size - 1, grid_size - 1); //Goal position
	Node new_n = n;
	cout << "here0" << endl;
	bool works = (this->*direction)(&new_n);
	cout << "here1" << endl;
	bool not_found = (visited.find(new_n) == visited.end());
	cout << "here2" << endl;
	if (works && not_found) {
		cout << "here3" << endl;
		new_n.setParent(n);
		new_n.setg();
		new_n.seth(finalPos);
		new_n.setf();
		to_visit.insert(new_n);
		cout << "here4" << endl;
	}
}

bool Pathfinder::up(Node * pos) {
	if (pos->getPos()->getz() - 1 >= 0 && (*maze)[pos->getPos()->getz() - 1][pos->getPos()->gety()][pos->getPos()->getx()] == 1) {
		pos->getPos()->decz();
		return true;
	}
	return false;
}

bool Pathfinder::down(Node * pos) {
	if (pos->getPos()->getz() + 1 < num_grids && (*maze)[pos->getPos()->getz() + 1][pos->getPos()->gety()][pos->getPos()->getx()] == 1) {
		pos->getPos()->incz();
		return true;
	}
	return false;
}

bool Pathfinder::forward(Node * pos) {
	if (pos->getPos()->gety() - 1 >= 0 && (*maze)[pos->getPos()->getz()][pos->getPos()->gety() - 1][pos->getPos()->getx()] == 1) {
		pos->getPos()->decy();
		return true;
	}
	return false;
}

bool Pathfinder::backward(Node * pos) {
	if (pos->getPos()->gety() + 1 < grid_size && (*maze)[pos->getPos()->getz()][pos->getPos()->gety() + 1][pos->getPos()->getx()] == 1) {
		pos->getPos()->incy();
		return true;
	}
	return false;
}

bool Pathfinder::left(Node * pos) {
	if (pos->getPos()->getx() - 1 >= 0 && (*maze)[pos->getPos()->getz()][pos->getPos()->gety()][pos->getPos()->getx() - 1] == 1) {
		pos->getPos()->decx();
		return true;
	}
	return false;
}

bool Pathfinder::right(Node * pos) {
	if (pos->getPos()->getx() + 1 < 5 && (*maze)[pos->getPos()->getz()][pos->getPos()->gety()][pos->getPos()->getx() + 1] == 1) {
		pos->getPos()->incx();
		return true;
	}
	return false;
}