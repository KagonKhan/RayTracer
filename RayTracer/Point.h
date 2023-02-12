#pragma once
#include <array>
#include <iostream>


template <typename T>
struct Point {
private:
	std::array<T, 4> data;


public:
	constexpr Point() noexcept : data{ 0,0,0,0 } { }
	constexpr Point(T x, T y, T z, T w = 0) noexcept : data{ x, y, z, w } { }

	constexpr friend std::ostream& operator<<(std::ostream& os, const Point& p) noexcept {
		os << "( " << p.data[0] << ", " << p.data[1] << ", " << p.data[2] << " )";
		return os;
	}
};