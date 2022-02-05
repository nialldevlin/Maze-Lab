#include "coord.h"

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

