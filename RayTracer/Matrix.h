#pragma once
#include "Point.h"
#include "Point.h"

#include <array>
#include <iostream>


// TODO: namespace Math with constants and free functions
// TODO: need copy ctors?

template <typename T, std::size_t Dimension>
class Matrix {
public:
	inline static constexpr std::size_t size{ Dimension * Dimension };
    inline static constexpr std::size_t dimension{ Dimension };

	std::array<T, size> data;

    // TODO: Convert to multi-dim sub operator when available
	inline static constexpr std::size_t mapIndex(const std::size_t row, const std::size_t col) {
		return dimension * row + col;
	}


    inline constexpr Matrix() noexcept : data{ } { }

    template <typename... Ts> 
    inline constexpr Matrix(Ts&&... ts) noexcept : data{ std::forward<Ts>(ts)... } {}
	
    inline constexpr friend std::ostream& operator<<(std::ostream& os, const Matrix& m) noexcept {
		for (std::size_t row = 0; row < dimension; ++row) {
			for (std::size_t col = 0; col < dimension; ++col) {
				os << m.data[mapIndex(row, col)] << (((col + 1) != dimension) ? ", " : "\n");
			}
		}
		return os;
	}

    constexpr Matrix<T, Dimension> operator *(Matrix<T, Dimension> const& rhs) const noexcept {
        // TODO: add a flag if a matrix is transposed?
        // Mayrhs.datae transposing will rhs.datae faster,
        // or mayrhs.datae just dispatch to different algorithms
        if constexpr (dimension == 4) {
            T v1  = data[mapIndex(0, 0)] * rhs.data[mapIndex(0, 0)] + data[mapIndex(0, 1)] * rhs.data[mapIndex(1, 0)] + data[mapIndex(0, 2)] * rhs.data[mapIndex(2, 0)] + data[mapIndex(0, 3)] * rhs.data[mapIndex(3, 0)];
            T v2 = data[mapIndex(0, 0)] * rhs.data[mapIndex(0, 1)] + data[mapIndex(0, 1)] * rhs.data[mapIndex(1, 1)] + data[mapIndex(0, 2)] * rhs.data[mapIndex(2, 1)] + data[mapIndex(0, 3)] * rhs.data[mapIndex(3, 1)];
            T v3 = data[mapIndex(0, 0)] * rhs.data[mapIndex(0, 2)] + data[mapIndex(0, 1)] * rhs.data[mapIndex(1, 2)] + data[mapIndex(0, 2)] * rhs.data[mapIndex(2, 2)] + data[mapIndex(0, 3)] * rhs.data[mapIndex(3, 2)];
            T v4 = data[mapIndex(0, 0)] * rhs.data[mapIndex(0, 3)] + data[mapIndex(0, 1)] * rhs.data[mapIndex(1, 3)] + data[mapIndex(0, 2)] * rhs.data[mapIndex(2, 3)] + data[mapIndex(0, 3)] * rhs.data[mapIndex(3, 3)];
            
            T v5 = data[mapIndex(1, 0)] * rhs.data[mapIndex(0, 0)] + data[mapIndex(1, 1)] * rhs.data[mapIndex(1, 0)] + data[mapIndex(1, 2)] * rhs.data[mapIndex(2, 0)] + data[mapIndex(1, 3)] * rhs.data[mapIndex(3, 0)];
            T v6 = data[mapIndex(1, 0)] * rhs.data[mapIndex(0, 1)] + data[mapIndex(1, 1)] * rhs.data[mapIndex(1, 1)] + data[mapIndex(1, 2)] * rhs.data[mapIndex(2, 1)] + data[mapIndex(1, 3)] * rhs.data[mapIndex(3, 1)];
            T v7 = data[mapIndex(1, 0)] * rhs.data[mapIndex(0, 2)] + data[mapIndex(1, 1)] * rhs.data[mapIndex(1, 2)] + data[mapIndex(1, 2)] * rhs.data[mapIndex(2, 2)] + data[mapIndex(1, 3)] * rhs.data[mapIndex(3, 2)];
            T v8 = data[mapIndex(1, 0)] * rhs.data[mapIndex(0, 3)] + data[mapIndex(1, 1)] * rhs.data[mapIndex(1, 3)] + data[mapIndex(1, 2)] * rhs.data[mapIndex(2, 3)] + data[mapIndex(1, 3)] * rhs.data[mapIndex(3, 3)];
            
            T v9 = data[mapIndex(2, 0)] * rhs.data[mapIndex(0, 0)] + data[mapIndex(2, 1)] * rhs.data[mapIndex(1, 0)] + data[mapIndex(2, 2)] * rhs.data[mapIndex(2, 0)] + data[mapIndex(2, 3)] * rhs.data[mapIndex(3, 0)];
            T v10 = data[mapIndex(2, 0)] * rhs.data[mapIndex(0, 1)] + data[mapIndex(2, 1)] * rhs.data[mapIndex(1, 1)] + data[mapIndex(2, 2)] * rhs.data[mapIndex(2, 1)] + data[mapIndex(2, 3)] * rhs.data[mapIndex(3, 1)];
            T v11 = data[mapIndex(2, 0)] * rhs.data[mapIndex(0, 2)] + data[mapIndex(2, 1)] * rhs.data[mapIndex(1, 2)] + data[mapIndex(2, 2)] * rhs.data[mapIndex(2, 2)] + data[mapIndex(2, 3)] * rhs.data[mapIndex(3, 2)];
            T v12 = data[mapIndex(2, 0)] * rhs.data[mapIndex(0, 3)] + data[mapIndex(2, 1)] * rhs.data[mapIndex(1, 3)] + data[mapIndex(2, 2)] * rhs.data[mapIndex(2, 3)] + data[mapIndex(2, 3)] * rhs.data[mapIndex(3, 3)];
           
            T v13 = data[mapIndex(3, 0)] * rhs.data[mapIndex(0, 0)] + data[mapIndex(3, 1)] * rhs.data[mapIndex(1, 0)] + data[mapIndex(3, 2)] * rhs.data[mapIndex(2, 0)] + data[mapIndex(3, 3)] * rhs.data[mapIndex(3, 0)];
            T v14 = data[mapIndex(3, 0)] * rhs.data[mapIndex(0, 1)] + data[mapIndex(3, 1)] * rhs.data[mapIndex(1, 1)] + data[mapIndex(3, 2)] * rhs.data[mapIndex(2, 1)] + data[mapIndex(3, 3)] * rhs.data[mapIndex(3, 1)];
            T v15 = data[mapIndex(3, 0)] * rhs.data[mapIndex(0, 2)] + data[mapIndex(3, 1)] * rhs.data[mapIndex(1, 2)] + data[mapIndex(3, 2)] * rhs.data[mapIndex(2, 2)] + data[mapIndex(3, 3)] * rhs.data[mapIndex(3, 2)];
            T v16 = data[mapIndex(3, 0)] * rhs.data[mapIndex(0, 3)] + data[mapIndex(3, 1)] * rhs.data[mapIndex(1, 3)] + data[mapIndex(3, 2)] * rhs.data[mapIndex(2, 3)] + data[mapIndex(3, 3)] * rhs.data[mapIndex(3, 3)];

            return { v1, v2, v3, v4,
                v5, v6, v7, v8,
                v9, v10, v11, v12,
                v13, v14, v15, v16 };
        }

        if constexpr (dimension == 3) {
            T v1 = data[mapIndex(0, 0)] * rhs.data[mapIndex(0, 0)] + data[mapIndex(0, 1)] * rhs.data[mapIndex(1, 0)] + data[mapIndex(0, 2)] * rhs.data[mapIndex(2, 0)];
            T v2 = data[mapIndex(0, 0)] * rhs.data[mapIndex(0, 1)] + data[mapIndex(0, 1)] * rhs.data[mapIndex(1, 1)] + data[mapIndex(0, 2)] * rhs.data[mapIndex(2, 1)];
            T v3 = data[mapIndex(0, 0)] * rhs.data[mapIndex(0, 2)] + data[mapIndex(0, 1)] * rhs.data[mapIndex(1, 2)] + data[mapIndex(0, 2)] * rhs.data[mapIndex(2, 2)];
            
            T v4 = data[mapIndex(1, 0)] * rhs.data[mapIndex(0, 0)] + data[mapIndex(1, 1)] * rhs.data[mapIndex(1, 0)] + data[mapIndex(1, 2)] * rhs.data[mapIndex(2, 0)];
            T v5 = data[mapIndex(1, 0)] * rhs.data[mapIndex(0, 1)] + data[mapIndex(1, 1)] * rhs.data[mapIndex(1, 1)] + data[mapIndex(1, 2)] * rhs.data[mapIndex(2, 1)];
            T v6 = data[mapIndex(1, 0)] * rhs.data[mapIndex(0, 2)] + data[mapIndex(1, 1)] * rhs.data[mapIndex(1, 2)] + data[mapIndex(1, 2)] * rhs.data[mapIndex(2, 2)];
            
            T v7 = data[mapIndex(2, 0)] * rhs.data[mapIndex(0, 0)] + data[mapIndex(2, 1)] * rhs.data[mapIndex(1, 0)] + data[mapIndex(2, 2)] * rhs.data[mapIndex(2, 0)];
            T v8 = data[mapIndex(2, 0)] * rhs.data[mapIndex(0, 1)] + data[mapIndex(2, 1)] * rhs.data[mapIndex(1, 1)] + data[mapIndex(2, 2)] * rhs.data[mapIndex(2, 1)];
            T v9 = data[mapIndex(2, 0)] * rhs.data[mapIndex(0, 2)] + data[mapIndex(2, 1)] * rhs.data[mapIndex(1, 2)] + data[mapIndex(2, 2)] * rhs.data[mapIndex(2, 2)];

            return { v1, v2, v3,
                     v4, v5, v6,
                     v7, v8, v9 };
        }

        if constexpr (dimension == 2) {
            T v1 = data[mapIndex(0, 0)] * rhs.data[mapIndex(0, 0)] + data[mapIndex(0, 1)] * rhs.data[mapIndex(1, 0)];
            T v2 = data[mapIndex(0, 0)] * rhs.data[mapIndex(0, 1)] + data[mapIndex(0, 1)] * rhs.data[mapIndex(1, 1)];
            
            T v3 = data[mapIndex(1, 0)] * rhs.data[mapIndex(0, 0)] + data[mapIndex(1, 1)] * rhs.data[mapIndex(1, 0)];
            T v4 = data[mapIndex(1, 0)] * rhs.data[mapIndex(0, 1)] + data[mapIndex(1, 1)] * rhs.data[mapIndex(1, 1)];

            return { v1, v2,
                     v3, v4 };
        }
    }

    template <typename X>
    inline constexpr Tuple<X> operator *(Tuple<X> const& rhs) const noexcept {
        X v1 = data[mapIndex(0, 0)] * rhs.data[0] + data[mapIndex(0, 1)] * rhs.data[1] + data[mapIndex(0, 2)] * rhs.data[2] + data[mapIndex(0, 3)] * rhs.data[3];
        X v2 = data[mapIndex(1, 0)] * rhs.data[0] + data[mapIndex(1, 1)] * rhs.data[1] + data[mapIndex(1, 2)] * rhs.data[2] + data[mapIndex(1, 3)] * rhs.data[3];
        X v3 = data[mapIndex(2, 0)] * rhs.data[0] + data[mapIndex(2, 1)] * rhs.data[1] + data[mapIndex(2, 2)] * rhs.data[2] + data[mapIndex(2, 3)] * rhs.data[3];
        X v4 = data[mapIndex(3, 0)] * rhs.data[0] + data[mapIndex(3, 1)] * rhs.data[1] + data[mapIndex(3, 2)] * rhs.data[2] + data[mapIndex(3, 3)] * rhs.data[3];

        return { v1, v2, v3, v4 };
    }
    inline constexpr Vector<T> operator *(Vector<T> const& rhs) const noexcept {
        return Vector<T>{*this * Tuple<T>{rhs}};
    }

    template <typename X>
    inline constexpr Point<X> operator *(Point<X> const& rhs) const noexcept {
        return Point<X>((*this* Tuple<X>{rhs}));
    }

    // TODO: optimize?
    inline constexpr Matrix<T, 4> Transposed() const noexcept {
        Matrix<T, Dimension> retVal;
        for (int row = 0; row < 4; row++)
            for (int col = 0; col < 4; col++)
                retVal.data[mapIndex(col, row)] = data[mapIndex(row, col)];

        return retVal;
    }

    inline constexpr Matrix<T, 4> Inversed() const noexcept {
        if constexpr (dimension == 4) {
            Matrix<T, Dimension> retVal{ 1.0, 0.0 ,0.0 ,0.0 ,0.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,1.0 };
            Matrix<T, Dimension> a = *this;
            
            for (int row = 0; row < 4; row++)
                for (int col = 0; col < 4; col++) {
                    if (row == col) continue;

                    double ratio = a.data[mapIndex(col, row)] / a.data[mapIndex(row, row)];
                    a.data[mapIndex(col, 0)] -= a.data[mapIndex(row, 0)] * ratio;
                    a.data[mapIndex(col, 1)] -= a.data[mapIndex(row, 1)] * ratio;
                    a.data[mapIndex(col, 2)] -= a.data[mapIndex(row, 2)] * ratio;
                    a.data[mapIndex(col, 3)] -= a.data[mapIndex(row, 3)] * ratio;

                    retVal.data[mapIndex(col, 0)] -= retVal.data[mapIndex(row, 0)] * ratio;
                    retVal.data[mapIndex(col, 1)] -= retVal.data[mapIndex(row, 1)] * ratio;
                    retVal.data[mapIndex(col, 2)] -= retVal.data[mapIndex(row, 2)] * ratio;
                    retVal.data[mapIndex(col, 3)] -= retVal.data[mapIndex(row, 3)] * ratio;

                }

            for (int row = 0; row < 4; row++) {
                double temp = 1 / a.data[mapIndex(row, row)];
                retVal.data[mapIndex(row, 0)] *= temp;
                retVal.data[mapIndex(row, 1)] *= temp;
                retVal.data[mapIndex(row, 2)] *= temp;
                retVal.data[mapIndex(row, 3)] *= temp;

            }

            return retVal;
        }
    }

    // TODO: Enable if dim 4
    inline constexpr Matrix<T, 4> Translated(double x, double y, double z) const noexcept {
        return Matrix<T, 4>{1.0, 0.0, 0.0, x,
                            0.0, 1.0, 0.0, y,
                            0.0, 0.0, 1.0, z,
                            0.0, 0.0, 0.0, 1.0} * *this;
    }
    inline constexpr Matrix<T, 4> Scaled(double x, double y, double z) const noexcept {
        return Matrix<T, 4>{x, 0.0, 0.0, 0.0,
                            0.0, y, 0.0, 0.0,
                            0.0, 0.0, z, 0.0,
                            0.0, 0.0, 0.0, 1.0} * *this;
    }
    inline constexpr Matrix<T, 4> Sheared(double Xy = 0, double Xz = 0, double Yx = 0, double Yz = 0, double Zx = 0, double Zy = 0) const noexcept {
        return Matrix<T, 4>{1.0,  Xy,  Xz, 0.0,
                            Yx, 1.0,  Yz, 0.0,
                            Zx,  Zy, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0} * *this;
    }
    inline constexpr Matrix<T, 4> RotatedX(double r) const noexcept {
        double c = std::cos(r), s = std::sin(r);

        return Matrix<T, 4>{1.0, 0.0, 0.0, 0.0,
                            0.0, c, -s, 0.0,
                            0.0, s, c, 0.0,
                            0.0, 0.0, 0.0, 1.0} * *this;
    }
    inline constexpr Matrix<T, 4> RotatedY(double r) const noexcept {
        double c = std::cos(r), s = std::sin(r);

        return Matrix<T, 4>{c, 0.0, s, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            -s, 0.0, c, 0.0,
                            0.0, 0.0, 0.0, 1.0} * *this;
    }
    inline constexpr Matrix<T, 4> RotatedZ(double r) const noexcept {
        double c = std::cos(r), s = std::sin(r);

        return Matrix<T, 4>{c, -s, 0.0, 0.0,
                            s, c, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0} * *this;
    }
};


template<typename T>
inline static constexpr Matrix<T, 4> I{ 1.0, 0.0, 0.0, 0.0,
                                        0.0, 1.0, 0.0, 0.0,
                                        0.0, 0.0, 1.0, 0.0,
                                        0.0, 0.0, 0.0, 1.0 };




template <typename T, std::size_t Dim>
inline constexpr bool operator==(Matrix<T, Dim> const& lhs, Matrix<T, Dim> const& rhs) {
    if (&lhs == &rhs) return true;

    for (std::size_t i{ 0 }; i < Matrix<T, Dim>::size; ++i) {
        if (std::abs(lhs.data[i] - rhs.data[i]) >= 5e-6) return false;
    }   

    return true;
}