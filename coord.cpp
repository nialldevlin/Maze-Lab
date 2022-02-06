#include "coord.h"
#include <string>
#include <cmath>

Coord::Coord() {
	x = 0;
	y = 0;
	z = 0;
}

Coord::Coord(int xx, int yy, int zz) {
	x = xx;
	y = yy;
	z = zz;
}

int Coord::getx() {
	return x;
}

int Coord::gety() {
	return y;
}

int Coord::getz() {
	return z;
}

void Coord::setx(int xx) {
	x = xx;
	if ( x < 0 ) {
		x = 0;
	}
}

void Coord::sety(int yy) {
	y = yy;
	if ( y < 0 ) {
		y = 0;
	}
}

void Coord::setz(int zz) {
	z = zz;
	if ( z < 0 ) {
		z = 0;
	}
}

void Coord::set(int xx, int yy, int zz) {
	x = xx;
	y = yy;
	z = zz;
	if ( x < 0 ) {
		x = 0;
	}
	if ( y < 0 ) {
		y = 0;
	}
	if ( z < 0 ) {
		z = 0;
	}
}

void Coord::decx() {
	x--;
	if ( x < 0 ) {
		x = 0;
	}
}

void Coord::decy() {
	y--;
	if ( y < 0 ) {
		y = 0;
	}
}

void Coord::decz() {
	z--;
	if ( z < 0 ) {
		z = 0;
	}
}

void Coord::incx() {
	x++;
}

void Coord::incy() {
	y++;
}

void Coord::incz() {
	z++;
}

float Coord::getDist(Coord other) {
	int xdiff = x - other.getx();
	int ydiff = y - other.gety();
	int zdiff = z - other.getz();
	return sqrt(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);
}

std::string Coord::str() {
	std::string out = "(";
	out.append(x);
	out.append(", ");
	out.append(y);
	out.append(", ");
	out.append(z);
	out.append(")");
	return out;
}

bool operator== (const Coord& c1, const Coord& c2) {
    return (c1.x == c2.x &&
            c1.y == c2.y &&
            c1.z == c2.z);
}

bool operator!= (const Coord& c1, const Coord& c2) {
    return (c1.x != c2.x ||
            c1.y != c2.y ||
            c1.z != c2.z);
}