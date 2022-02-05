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
}

void Coord::sety(int yy) {
	y = yy;
}

void Coord::setz(int zz) {
	z = zz;
}

int Coord::set(int xx, int yy, int zz) {
	x = xx;
	y = yy;
	z = zz;
}