#ifndef NODE_H
#define NODE_H

#include "coord.h"

class Node{
private:
	Node * parent_node;
	Coord position;
	float cost_g;
	float cost_h;
	float cost_f;

public:
	Node();
	Node(Coord pos);
	Node(Coord pos, Node parent);
	~Node();

	Node * getParent();
	void setParent(Node * parent);

	float getg();
	float geth();
	float getf();

	void setg();
	void seth(Coord finalpos);
	void setf();

	Coord getPos();
	void setPos(Coord pos);

	friend bool operator< (const Node& n1, const Node& n2);
	friend bool operator== (const Node& n1, const Node& n2);
};

#endif
