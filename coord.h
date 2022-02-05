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

	int setx();
	int sety();
	int setz();

	int set(int x, int y, int z);
}