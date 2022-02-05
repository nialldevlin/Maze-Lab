#ifndef NODE_H
#define NODE_H

#include "coord.h"

class Node{
private:
	Node * parent_node;
	Coord position;
	int cost_g;
	int cost_h;
	int cost_f;


public:
	Node();
	Node(Coord pos, Node * parent);
	~Node(){}

	Node * getParent();
	void setParent(Node * parent);

	int getGCost();
	int getHCost();
	int getFCost();

	void setGCost();
	void setHCost();
	void setFCost();

	Coord getPos();
	void setPos(Coord pos);

};

#endif
