#include "Point.h"
#include "Matrix.h"

#include <intrin.h>

int main() {
	//constexpr Point<float> p;
	//constexpr Point<float> px{ 1.f, 0.f, 0.f };

	//Vector<float> res{ p - px };

	//std::cout << res;
	//std::cout << std::endl;

	//std::cout << px.abs();

	//std::cout << "\n";
	//std::cout << res.magnitude();


	Matrix<float, 4> m4;
	Matrix<float, 3> m3{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
	constexpr Matrix<float, 2> m2{1.f,2.f,3.f,4.f};

	std::cout << m4 << "\n\n" << m3 << "\n\n" << m2 << "\n";

	__m256d test;
}