#include "node.h"
#include <cmath> 

Node::Node() {
	position = new Coord();
	parent_node = nullptr;
	cost_g = 0.0;
	cost_h = 0.0;
	cost_f = 0.0;
}

Node::Node(Coord pos) {
	*position = pos;
	parent_node = nullptr;
	cost_g = 0.0;
	cost_f = 0.0;
	cost_h = 0.0;
}

Node::Node(Coord pos, Node parent) {
	*position = pos;
	parent_node = &parent;
	cost_g = 0.0;
	cost_f = 0.0;
	cost_h = 0.0;
}

Node::~Node(){
	delete position;
	delete parent_node;
}

Node * Node::getParent() {
	return parent_node;
}

void Node::setParent(Node parent) {
	parent_node = &parent;
}

int Node::getg() {
	return cost_g;
}

int Node::geth() {
	return cost_h;
}

int Node::getf() {
	return cost_f;
}

void Node::setg(int g) {
	cost_g = g;
}

void Node::seth(int h) {
	cost_h = h;
}

void Node::setf(int f) {
	cost_f = f;
}

Coord * Node::getPos() {
	return position;
}

void Node::setPos(Coord pos) {
	*position = pos;
}

bool operator< (const Node& n1, const Node& n2) {
    return n1.cost_f < n2.cost_f;
}

bool operator== (const Node& n1, const Node& n2) {
    return (abs(n1.cost_f - n1.cost_f) < 0.01);
}

bool operator!= (const Node& n1, const Node& n2) {
    return (abs(n1.cost_f - n1.cost_f) >= 0.01);
}