#include "Vector.h"

bool cmp(auto x, auto y) {
	return (
		x[0] == y[0] &&
		x[1] == y[1] &&
		x[2] == y[2] &&
		x[3] == y[3]
		);
}

int main() {
	Color c1(1.0, 0.2, 0.4);
	Color c2(0.9, 1.0, 0.1);
	auto res = c1 * c2;
	Color expected(0.9, 0.2, 0.04);

	auto subbed = Color(res - expected);
	

	std::cout <<"c1 * c2 = " << res;
	std::cout <<"\nexpected= " << expected;
	std::cout << "\ndiff: " << (res == Color(0.9, 0.2, 0.04));
	std::cout << "\nstd::epsilon: " << std::numeric_limits<double>::epsilon();
}
