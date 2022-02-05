#ifndef NODE_H
#define NODE_H

#include "coord.h"

class Node{
private:
	Node * parent_node;
	Coord * position;
	float cost_g;
	float cost_h;
	float cost_f;

public:
	Node();
	Node(Coord pos);
	Node(Coord pos, Node parent);
	~Node();

	Node * getParent();
	void setParent(Node parent);

	int getg();
	int geth();
	int getf();

	void setg(int g);
	void seth(int h);
	void setf(int f);

	Coord getPos();
	void setPos(Coord pos);
};

#endif
