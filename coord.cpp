#include "coord.h"
#include <string>
#include <cmath>
#include <sstream>
#include <iostream>

using namespace std;

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
}

void Coord::sety(int yy) {
	y = yy;
}

void Coord::setz(int zz) {
	z = zz;
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

bool Coord::inBounds(Coord start, Coord finish) {
    return  x >= start.getx() && x <= finish.getx() &&
            y >= start.gety() && y <= finish.gety() &&
            z >= start.getz() && z <= finish.getz();
}

string Coord::str() {
	stringstream out;
	out << "(";
	out << x;
	out << ", ";
	out << y;
	out << ", ";
	out << z;
	out << ")";
	return out.str();
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
