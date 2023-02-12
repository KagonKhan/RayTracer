#include "Point.h"


int main() {
	constexpr Point<float> p;
	constexpr Point<float> px{ 1.f, 0.f, 0.f };

	Vector<float> res{ p - px };

	std::cout << res;
	std::cout << std::endl;

	std::cout << px.abs();

	std::cout << "\n";
	std::cout << res.magnitude();
}