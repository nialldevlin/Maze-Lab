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

	void decx();
	void decy();
	void decz();

	void incx();
	void incy();
	void incz();

	int set(int x, int y, int z);
};

#endif
