#pragma once
#include <array>
#include <iostream>


template <typename T>
class Vector {
private:
	std::array<T, 4> data;


public:
	constexpr Vector() noexcept : data{ 0, 0, 0, 0 } { }
	constexpr Vector(T x, T y, T z, T w = 0) noexcept : data{ x, y, z, w } { }

	constexpr friend std::ostream& operator<<(std::ostream& os, const Vector& v) noexcept {
		os << "( " << v.data[0] << ", " << v.data[1] << ", " << v.data[2] << " )";
		return os;
	}

    constexpr Vector<T> operator +(Vector<T> const& rhs) const noexcept {
        return { data[0] + rhs.data[0], data[1] + rhs.data[1], data[2] + rhs.data[2], data[3] + rhs.data[3] };
    }
    constexpr Vector<T> operator -(Vector<T> const& rhs) const noexcept {
        return { data[0] - rhs.data[0], data[1] - rhs.data[1], data[2] - rhs.data[2], data[3] - rhs.data[3] };
    }

    constexpr Vector<T> operator -() const noexcept {
        return { -data[0], -data[1], -data[2], -data[3] };
    }

    constexpr Vector<T> operator *(T scalar) const noexcept {
        return { data[0] * scalar, data[1] * scalar, data[2] * scalar, data[3] * scalar };
    }
    constexpr Vector<T> operator /(T scalar) const noexcept {
        scalar = 1 / scalar;
        return { data[0] * scalar, data[1] * scalar, data[2] * scalar, data[3] * scalar };
    }

    constexpr auto operator<=>(Vector<T> const&) const noexcept = default;

    constexpr Vector<T> abs() const noexcept {
        return { std::abs(data[0]), std::abs(data[1]), std::abs(data[2]), std::abs(data[3]) };
    }

    constexpr T magnitude() const noexcept {
        return std::sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3]);
    }
    constexpr Vector normalized() const noexcept {
        return *this / magnitude();
    }

    constexpr double dot(Vector<T> const& b) const noexcept {
        return data[0] * b[0] + data[1] * b[1] + data[2] * b[2] + data[3] * b[3];
    }
    constexpr Vector<T> cross(Vector<T> const& b) const noexcept {
        return {
            data[1] * b[2] - data[2] * b[1],
            data[2] * b[0] - data[0] * b[2],
            data[0] * b[1] - data[1] * b[0]
        };
    }

    constexpr Vector<T> reflect(Vector<T> const& norm) const noexcept {
        return *this - norm * (2 * dot(norm));
    }
};