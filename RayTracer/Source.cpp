#include "Vector.h"

int main() {
	Point p1(3, 2, 1);
	Point p2(5, 6, 7);
	Vector expected(-2, -4, -6);


	std::cout << "E: " << expected << " vs A: " << (p1 - p2);


}
