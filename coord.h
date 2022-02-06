#ifndef COORD_H
#define COORD_H

class Coord {
private:
	int x;
	int y;
	int z;

public:
	Coord();
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

	std::string str();

	friend bool operator== (const Coord& c1, const Coord& c2);
	friend bool operator!= (const Coord& c1, const Coord& c2);
};

#endif
