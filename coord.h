#ifndef COORD_H
#define COORD_H

#include <string>

class Coord {
private:
	int x = 0;
	int y = 0;
	int z = 0;

public:
	Coord(){}
	Coord(int x, int y, int z);
	~Coord(){};

	int getx();
	int gety();
	int getz();

	void setx(int xx);
	void sety(int yy);
	void setz(int zz);

	void set(int x, int y, int z);

	void decx();
	void decy();
	void decz();

	void incx();
	void incy();
	void incz();

	float getDist(Coord other);
	bool inBounds(Coord start, Coord finish);

	std::string str();

	friend bool operator== (const Coord& c1, const Coord& c2);
	friend bool operator!= (const Coord& c1, const Coord& c2);
};

#endif
