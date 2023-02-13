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


	   
		
		
		



	Matrix<double, 4> m{ -5.0, 2.0,  6.0, -8.0,
						  1.0, -5.0,  1.0,  8.0,
						  7.0,  7.0, -6.0, -7.0,
						  1.0, -3.0,  7.0,  4.0 };
	auto mI = m.Inversed();

	Matrix<double, 4> mIE{  0.21805,  0.45113,  0.24060, -0.04511,
						  -0.80827, -1.45677, -0.44361,  0.52068,
						  -0.07895, -0.22368, -0.05263,  0.19737,
						  -0.52256, -0.81391, -0.30075,  0.30639 };

	std::cout << "Expected:\n" << mIE << "\n Actual:\n" << mI;


	__m256d test;
}