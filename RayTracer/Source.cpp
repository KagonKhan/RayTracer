#include "Point.h"
#include "Matrix.h"

#include <intrin.h>
#include <chrono>

int main() {
	//constexpr Point<float> p;
	//constexpr Point<float> px{ 1.f, 0.f, 0.f };

	//Vector<float> res{ p - px };

	//std::cout << res;
	//std::cout << std::endl;

	//std::cout << px.abs();

	//std::cout << "\n";
	//std::cout << res.magnitude();


	   
		
		
		//3.2 seconds pure
		// 16ms constexpr
	auto t1 = std::chrono::high_resolution_clock::now();

	for (unsigned long long i = 0; i < 4'000'000'000; ++i) {
		constexpr Matrix<double, 4> m{ -5.0, 2.0,  6.0, -8.0,
							  1.0, -5.0,  1.0,  8.0,
							  7.0,  7.0, -6.0, -7.0,
							  1.0, -3.0,  7.0,  4.0 };
		constexpr auto mI = m.Inversed();

		constexpr Matrix<double, 4> mIE{ 0.21805,  0.45113,  0.24060, -0.04511,
							  -0.80827, -1.45677, -0.44361,  0.52068,
							  -0.07895, -0.22368, -0.05263,  0.19737,
							  -0.52256, -0.81391, -0.30075,  0.30639 };

		constexpr auto I = m * mI;
		if (I == mI) {
			std::cout << "lol. Lmao even.";
		}
	}


	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

}