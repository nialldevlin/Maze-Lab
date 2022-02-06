#include "node.h"
#include <cmath>

Node::Node() {
	position = new Coord();
	parent_node = nullptr;
	cost_g = 0.0;
	cost_h = 0.0;
	cost_f = 0.0;
}

Node::Node(Coord * pos) {
	position = pos;
	parent_node = nullptr;
	cost_g = 0.0;
	cost_f = 0.0;
	cost_h = 0.0;
}

Node::Node(Coord * pos, Node parent) {
	position = pos;
	parent_node = &parent;
	cost_g = 0.0;
	cost_f = 0.0;
	cost_h = 0.0;
}

Node::~Node(){
	if (position)
		delete position;
	if (parent_node)
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

void Node::setg() {
	if (parent_node != nullptr) {
		cost_g = parent_node->getg() + 1.0;
	} else {
		cost_g = 0.0;
	}
}

void Node::seth(Coord finalpos) {
	cost_h = position->getDist(finalPos);
}

void Node::setf() {
	cost_f = cost_g + cost_h;
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