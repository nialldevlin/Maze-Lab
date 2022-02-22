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
#include <cmath>

using namespace std;

const Coord Pathfinder::finalPos = Coord(NUM_GRIDS - 1, GRID_SIZE - 1, GRID_SIZE - 1);
const Coord Pathfinder::startPos = Coord(0, 0, 0);

Pathfinder::Pathfinder() {
	maze = new vector<vector<vector<bool>>> (NUM_GRIDS, vector<vector<bool>>(GRID_SIZE, vector<bool>(GRID_SIZE, 1)));
	srand(time(NULL));
	Node start(startPos);
    start.setg();
    start.seth(finalPos);
    start.setf();
    current_path.push_front(start);
}

Pathfinder::~Pathfinder() {
	if (maze)
		delete maze;
}

string Pathfinder::toString(vector<vector<vector<short>>> m) const {
	stringstream ss;
	string separator = "";
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[0].size(); j++) {
			for (int k = 0; k < m[0][0].size(); k++) {
				ss << separator << m[i][j][k];
				separator = " ";
			}
			separator = "";
			ss << endl;
		}
		ss << "\n";
	}
	string outstr = ss.str();
	outstr.pop_back();
	return outstr;
}

string Pathfinder::result() {
    vector<vector<vector<bool>>> m = *maze;
	stringstream ss;
	string separator = "";
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[0].size(); j++) {
			for (int k = 0; k < m[0][0].size(); k++) {
                int value;
                if (inPath(Coord(i, j, k))) {
                    ss << separator << 'x';
                } else {
                    ss << separator << m[i][j][k];
                }
                separator = " ";
			}
			separator = "";
			ss << endl;
		}
		ss << endl;
	}
	string outstr = ss.str();
	outstr.pop_back();
	return outstr;
}

string Pathfinder::toString() const {
	stringstream ss;
	string separator = "";
	for (int i = 0; i < (*maze).size(); i++) {
		for (int j = 0; j < (*maze)[0].size(); j++) {
			for (int k = 0; k < (*maze)[0][0].size(); k++) {
				ss << separator << (*maze)[i][j][k];
				separator = " ";
			}
			separator = "";
			ss << endl;
		}
		ss << "\n";
	}
	string outstr = ss.str();
	outstr.pop_back();
	return outstr;
}

void Pathfinder::createRandomMaze() {
    clear();
	for (int i = 0; i < (*maze).size(); i++) {
		for (int j = 0; j < (*maze)[0].size(); j++) {
			for (int k = 0; k < (*maze)[0].size(); k++) {
				(*maze)[i][j][k] = rand() % 2;
			}
		}
	}
	(*maze)[0][0][0] = 1;
	(*maze)[NUM_GRIDS - 1][GRID_SIZE - 1][GRID_SIZE - 1] = 1;
}

bool Pathfinder::importMaze(string file_name) {
	ifstream ifs;
	ifs.open(file_name);
	cout << file_name << endl;
	if (!ifs.is_open()) {

		return false;
	}
	string line;
	vector<bool> vals;

	int ones = 0;
	int zeroes = 0;
	while (ifs >> line) {
		stringstream ss(line);
		string v;
		while(ss >> v) {
            bool val;
            if (v == "0") {
                val = 0;
            } else if (v == "1") {
                val = 1;
            } else {
                return false;
            }
            vals.push_back(val);
			if (val)
				zeroes++;
			else
				ones++;

		}
	}
	if (vals.size() != NUM_GRIDS * GRID_SIZE * GRID_SIZE) return false;
	/*cout << abs(zeroes - ones) << endl;
	if (abs(zeroes - ones) > 100) {
        return false;
	}*/
	clear();
	int index = 0;
	for (int i = 0; i < (*maze).size(); i++) {
		for (int j = 0; j < (*maze)[0].size(); j++) {
			for (int k = 0; k < (*maze)[0].size(); k++) {
				(*maze)[i][j][k] = vals[index];
				index++;
			}
		}
	}
	if ((*maze)[0][0][0] == 0 || (*maze)[NUM_GRIDS - 1][GRID_SIZE - 1][GRID_SIZE - 1] == 0) return false;
	return true;
}

vector<string> Pathfinder::solveMaze() {
    if (current_path.empty()) {
        vector<string> out;
        return out;
    }
    current = &current_path.front();
    Coord currPos = current->getPos();
    if (currPos == finalPos) {
        return findPath();
    }

    set<Node> neighbors;
    //Create Node for each neighbor
    up(current, &neighbors);
    down(current, &neighbors);
    forwd(current, &neighbors);
    backward(current, &neighbors);
    left(current, &neighbors);
    right(current, &neighbors);

    if (neighbors.empty()) {

        //Reached end of branch
        Node n = *current;
        bad_nodes.push_back(n);
        current = current->getParent();
        current_path.pop_front();
        return solveMaze();
    }
    //Get option with lowest F
    Node next = *neighbors.begin();
    current_path.push_front(next);
    return solveMaze();
}

//Private functions
vector<string> Pathfinder::findPath() {
    //cout << toString() << endl << result() << endl;
    vector<string> out_path;
    while (!current_path.empty()) {
        string o = current_path.back().getPos().str();
        out_path.push_back(o);
        current_path.pop_back();
    }
	return out_path;
}

bool Pathfinder::up(Node * pos, set<Node> *n) {
    //Copy Node
    Node out = *pos;
    //Move down
    Coord c = out.getPos();
    int newz = c.getz() - 1;
    c.setz(newz);
    //Set new position
    out.setPos(c);
    //Check if in bounds and not already on the path and not a wall and not a bad Node
	if ( c.getz() >= 0 &&
         maze->at(c.getz()).at(c.gety()).at(c.getx()) &&
         !inPath(c) && !badNode(out) ) {
        //Set parent to previous Node
        out.setParent(pos);
        //Set heuristic functions
        out.setg();
        out.seth(finalPos);
        out.setf();
        //Add to neighbors list
        n->insert(out);
        return true;
	}
	//Return false if not added
	return false;
}

bool Pathfinder::down(Node * pos, set<Node> *n) {
    //Copy Node
    Node out = *pos;
    //Move down
    Coord c = out.getPos();
    int newz = c.getz() + 1;
    c.setz(newz);
    //Set new position
    out.setPos(c);
    //Check if in bounds and not already on the path and not a wall and not a bad Node
	if ( c.getz() < NUM_GRIDS &&
         maze->at(c.getz()).at(c.gety()).at(c.getx()) &&
         !inPath(c) && !badNode(out) ) {
        //Set parent to previous Node
        out.setParent(pos);
        //Set heuristic functions
        out.setg();
        out.seth(finalPos);
        out.setf();
        //Add to neighbors list
        n->insert(out);
        return true;
    }
	//Return false if not added
	return false;
}

bool Pathfinder::forwd(Node * pos, set<Node> *n) {
    //Copy Node
    Node out = *pos;
    //Move down
    Coord c = out.getPos();
    int newy = c.gety() - 1;
    c.sety(newy);
    //Set new position
    out.setPos(c);
    //Check if in bounds and not already on the path and not a wall and not a bad Node
	if ( c.gety() >= 0 &&
         maze->at(c.getz()).at(c.gety()).at(c.getx()) &&
         !inPath(c) && !badNode(out) ) {
        //Set parent to previous Node
        out.setParent(pos);
        //Set heuristic functions
        out.setg();
        out.seth(finalPos);
        out.setf();
        //Add to neighbors list
        n->insert(out);
        return true;
	}
	//Return false if not added
	return false;
}

bool Pathfinder::backward(Node * pos, set<Node> *n) {
    //Copy Node
    Node out = *pos;
    //Move down
    Coord c = out.getPos();
    int newy = c.gety() + 1;
    c.sety(newy);
    //Set new position
    out.setPos(c);
    //Check if in bounds and not already on the path and not a wall and not a bad Node
	if ( c.gety() < GRID_SIZE &&
         maze->at(c.getz()).at(c.gety()).at(c.getx()) &&
         !inPath(c) && !badNode(out) ) {
        //Set parent to previous Node
        out.setParent(pos);
        //Set heuristic functions
        out.setg();
        out.seth(finalPos);
        out.setf();
        //Add to neighbors list
        n->insert(out);
        return true;
	}
	//Return false if not added
	return false;
}

bool Pathfinder::left(Node * pos, set<Node> *n) {
    //Copy Node
    Node out = *pos;
    //Move down
    Coord c = out.getPos();
    int newx = c.getx() - 1;
    c.setx(newx);
    //Set new position
    out.setPos(c);
    //Check if in bounds and not already on the path and not a wall and not a bad Node
	if ( c.getx() >= 0 &&
         maze->at(c.getz()).at(c.gety()).at(c.getx()) &&
         !inPath(c) && !badNode(out) ) {
        //Set parent to previous Node
        out.setParent(pos);
        //Set heuristic functions
        out.setg();
        out.seth(finalPos);
        out.setf();
        //Add to neighbors list
        n->insert(out);
        return true;
	}
	//Return false if not added
	return false;
}

bool Pathfinder::right(Node * pos, set<Node> *n) {
    //Copy Node
    Node out = *pos;
    //Move down
    Coord c = out.getPos();
    int newx = c.getx() + 1;
    c.setx(newx);
    //Set new position
    out.setPos(c);
    //Check if in bounds and not already on the path and not a wall and not a bad Node
	if ( c.getx() < GRID_SIZE &&
         maze->at(c.getz()).at(c.gety()).at(c.getx()) &&
         !inPath(c) && !badNode(out) ) {
        //Set heuristic functions
        out.setg();
        out.seth(finalPos);
        out.setf();
        //Add to neighbors list
        n->insert(out);
        return true;
	}
	//Return false if not added
	return false;
}

bool Pathfinder::inPath(Coord n) {
    for (auto i : current_path) {
        if (n == i.getPos()) {
            return true;
        }
    }
    return false;
}

bool Pathfinder::badNode(Node n) {
    if (find(bad_nodes.begin(), bad_nodes.end(), n) != bad_nodes.end()) {
        return true;
    }
    return false;
}

void Pathfinder::clear() {
    delete maze;
    maze = new vector<vector<vector<bool>>> (NUM_GRIDS, vector<vector<bool>>(GRID_SIZE, vector<bool>(GRID_SIZE, 1)));
    current_path.clear();
    bad_nodes.clear();
	Node start(startPos);
    start.setg();
    start.seth(finalPos);
    start.setf();
    current_path.push_front(start);
}
