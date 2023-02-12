#include "Point.h"


int main() {
	constexpr Point<float> px{ 1.f, 2.f, 1.f };

	std::cout << px;
	std::cout << std::endl;
}