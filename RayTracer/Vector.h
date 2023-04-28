#pragma once
#include <array>
#include <iostream>
#include <type_traits>


template < template <typename...> class base, typename derived>
struct is_base_of_template_impl
{
    template<typename... Ts>
    static constexpr std::true_type  test(const base<Ts...>*);
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<derived*>()));
};

template < template <typename...> class base, typename derived>
using is_base_of_template = typename is_base_of_template_impl<base, derived>::type;


template <typename T> 
struct Tuple {
    std::array<T, 4> data{};

    constexpr Tuple(T x, T y, T z, T w) noexcept : data{ x, y, z, w } { }

    constexpr auto operator<=>(Tuple<T> const&) const noexcept = default;

    constexpr T const& operator[](int index) const { return data[index]; }


    constexpr Tuple<T> operator +(Tuple<T> const& rhs) const noexcept {
        return { data[0] + rhs.data[0], data[1] + rhs.data[1], data[2] + rhs.data[2], data[3] + rhs.data[3] };
    }
    constexpr Tuple<T> operator -(Tuple<T> const& rhs) const noexcept {
        return { data[0] - rhs.data[0], data[1] - rhs.data[1], data[2] - rhs.data[2], data[3] - rhs.data[3] };
    }
    constexpr Tuple<T> operator -() const noexcept {
        return { -data[0], -data[1], -data[2], -data[3] };
    }

    template <typename S>
    constexpr Tuple<std::common_type_t<T, S>> operator *(S scalar) const noexcept {
        return { data[0] * scalar, data[1] * scalar, data[2] * scalar, data[3] * scalar };
    }
    template <typename S>
    constexpr Tuple<std::common_type_t<T, S>> operator /(S scalar) const noexcept {
        return { data[0] / scalar, data[1] / scalar, data[2] / scalar, data[3] / scalar };
    }

    constexpr Tuple<T> abs() const noexcept {
        return { std::abs(data[0]), std::abs(data[1]), std::abs(data[2]), std::abs(data[3]) };
    }
};

template <typename T>
struct Vector : public Tuple<T> {
	constexpr Vector(T x, T y, T z, T w = 0) noexcept : Tuple<T>( x, y, z, w ) { }
	constexpr Vector(Tuple<T> t) noexcept : Tuple<T>( t ) { }

    using Tuple<T>::data;

    constexpr T magnitude() const noexcept {
        return std::sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3]);
    }
    constexpr Vector normalized() const noexcept {
        return *this / magnitude();
    }

    constexpr auto dot(Vector<T> const& b) const noexcept {
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


template <typename T>
struct Point : Tuple<T> {
    using Tuple<T>::data;

    constexpr Point() noexcept : Tuple<T>(0, 0, 0, 1) { }
    constexpr Point(T x, T y, T z, T w = 1) noexcept : Tuple<T>( x, y, z, w ) { }

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
};

template <typename T>
concept TupleLike = is_base_of_template<Tuple, T>::value;

template<TupleLike T>
constexpr std::ostream& operator<<(std::ostream& os, const T& t) noexcept {
    os << "( " << t.data[0] << ", " << t.data[1] << ", " << t.data[2] << ", " << t.data[3] << " )";
    return os;
}