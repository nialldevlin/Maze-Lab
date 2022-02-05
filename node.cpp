#include "node.h"

Node::Node() {
	position = new Coord();
	cost_g = 0;
	cost_f = 0;
	cost_h = 0;
}

Node::Node(Coord pos, Node * parent) {
	*position = pos;
	parent_node = parent;
	cost_g = 0;
	cost_f = 0;
	cost_h = 0;
}

Node::~Node(){
	delete position;
	delete parent_node;
}

Node * Node::getParent() {
	return parent_node;
}

void Node::setParent(Node * parent) {
	parent_node = parent;
}

int Node::getGCost() {
	return cost_g;
}

int Node::getHCost() {
	return cost_h;
}

int Node::getFCost() {
	return cost_f;
}

void Node::setGCost(int g) {
	cost_g = g;
}

void Node::setHCost(int h) {
	cost_h = h;
}

void Node::setFCost(int f) {
	cost_f = f;
}

Coord Node::getPos() {
	return *position;
}

void Node::setPos(Coord pos) {
	*position = pos;
}