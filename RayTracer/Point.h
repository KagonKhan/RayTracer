#pragma once


#include "Vector.h"


#include <array>
#include <iostream>



// TODO: __m256d vectorize


template <typename T>
class Point {
private:
	std::array<T, 4> data;


public:
	constexpr Point() noexcept : data{ 0, 0, 0, 1 } { }
	constexpr Point(T x, T y, T z, T w = 1) noexcept : data{ x, y, z, w } { }

	constexpr friend std::ostream& operator<<(std::ostream& os, const Point& p) noexcept {
		os << "( " << p.data[0] << ", " << p.data[1] << ", " << p.data[2] << " )";
		return os;
	}

	constexpr Vector<T> operator- (Point<T> const& rhs) const noexcept {
		return { data[0] - rhs.data[0], data[1] - rhs.data[1], data[2] - rhs.data[2], data[3] - rhs.data[3] };
	}
	constexpr Vector<T> operator+ (Point<T> const& rhs) const noexcept {
		return { data[0] + rhs.data[0], data[1] + rhs.data[1], data[2] + rhs.data[2], data[3] + rhs.data[3] };
	}

    constexpr Point<T> operator +(Vector<T> const& rhs) const noexcept {
        return { data[0] + rhs.data[0], data[1] + rhs.data[1], data[2] + rhs.data[2], data[3] + rhs.data[3] };
    }
    constexpr Point<T> operator -(Vector<T> const& rhs) const noexcept {
        return { data[0] - rhs.data[0], data[1] - rhs.data[1], data[2] - rhs.data[2], data[3] - rhs.data[3] };
    }

    constexpr Point<T> operator -() const noexcept {
		return { -data[0], -data[1], -data[2], -data[3] };
    }

	constexpr auto operator<=>(Point<T> const&) const noexcept = default;

	constexpr Point<T> abs() const noexcept {
		return { std::abs(data[0]), std::abs(data[1]), std::abs(data[2]), std::abs(data[3]) };
	}
};

